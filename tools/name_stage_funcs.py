#!/usr/bin/env python3
"""
Names a stage's functions after what calls them.

splat named the stages' functions by address (func_800A67B0). This names
each one by the place a table or a call gives it, and nothing else:

    stageEvents[k].start, .end        startEvent<id>, endEvent<id>  (the event's id)
    FIELDSTG_scriptCommands[k]        createCommand<id>, handleCommand<id>
      .create, .handle                  (the command's id, for the stage's functions)
    the update a function gives       update<Task>, and create<Task> for the function
      createTask(WithId)                that creates it (the task's struct, without
                                        Stage; not for StageTask or Task)
    the update of a StageTask or Task  updateEvent<id>, updateCommand<id>
      that an event's start or a
      command's create function creates

A few functions no table or call names have names given by reading their
code (GIVEN). An event's or a command's name comes before the name of the
task it creates.
A function that two tables (or two calls) name differently, two functions given one name,
a name the stage already has (or includes from src/stages/common), and a
function only one version of a stage has keep their address names. The names
go into the C, both versions' config/<version>/stages/<stage>.txt and, for a
function FIELDSTG links against, its WSTAGnnn_ name in include/stages.h and
src/fieldstg/ (and docs/) (then `make regenerate` each version). Only splat's names
(func_XXXXXXXX) are renamed, so it can be run again at any time:

    tools/name_stage_funcs.py [wstag200 ...]
"""
import argparse
import re
import sys

from name_stage_data import (
    CONFIG, ROOT, SRC, VERSIONS, definitions, elf_addresses, preprocess, stage_list, target, update_symbols,
)

AUTO = re.compile(r"^func_([0-9A-F]{8})$")
FUNCTION = re.compile(r"^(?:static\s+)?[\w\s\*]+?\b(\w+)\(([^;]*)\)\s*\{\s*$")
COMMANDS = ROOT / "src" / "fieldstg" / "data" / "fieldstg.c"
LINKED = ([ROOT / "include" / "stages.h"] + sorted((ROOT / "src" / "fieldstg").rglob("*.c"))
          + sorted((ROOT / "docs").glob("*.md")))
HEADER = "// functions named by what calls them (tools/name_stage_funcs.py)"
GENERIC_TASKS = {"StageTask", "Task"}

# Names given by reading the code, where no table or call names a function
# (the stages are those that share it, src/stages/common)
GIVEN = {
    ("wstag745", "wstag746"): {
        "func_800A4CA4": "updateDarkness",  # draws the screen black in TASK_DONE
        "func_800A4EB8": "createDarkness",
    },
    ("wstag480", "wstag481"): {"func_800A4CBC": "stepTileSequences"},
    ("wstag740", "wstag741"): {"func_800A5130": "drawPairSprite"},
}


def functions(text):
    """{name: (parameters, body lines)} of a file's functions"""
    out = {}
    lines = text.split("\n")
    name = None
    for line in lines:
        m = FUNCTION.match(line)
        if m and not line.startswith(" "):
            name = m.group(1)
            out[name] = (m.group(2), [])
            continue
        if line == "}":
            name = None
        elif name is not None:
            out[name][1].append(line)
    return out


def script_commands():
    """{stage: [(function, name)]} of FIELDSTG_scriptCommands"""
    out = {}
    text = COMMANDS.read_text()
    m = re.search(r"^ScriptCommand FIELDSTG_scriptCommands\[\] = \{\n(.*?)^\};", text, re.M | re.S)
    if not m:
        return out
    for row in re.finditer(r"\{(\d+), (\w+), (\w+)\}", m.group(1)):
        command = int(row.group(1))
        for leaf, kind in ((row.group(2), "create"), (row.group(3), "handle")):
            f = re.fullmatch(r"(WSTAG\d+)_(\w+)", leaf)
            if f:
                out.setdefault(f.group(1).lower(), []).append((f.group(2), f"{kind}Command{command}"))
    return out


def structural_names(text, commands, stage):
    """[(function, name, from a table)] that the stage's tables and calls give its functions"""
    out = []
    funcs = functions(text)
    defs = definitions(text)

    events = defs.get("stageEvents")
    if events and isinstance(events[2], list):
        for event in events[2]:
            if isinstance(event, list) and len(event) == 5 and re.fullmatch(r"\d+", event[0]):
                for leaf, kind in ((event[3], "start"), (event[4], "end")):
                    f = target(leaf)
                    if f in funcs:
                        out.append((f, f"{kind}Event{int(event[0])}", True))

    out.extend((f, name, True) for f, name in commands if f in funcs)
    for stages, given in GIVEN.items():
        if stage in stages:
            out.extend((f, name, True) for f, name in given.items() if f in funcs)

    tables = {f: name for f, name, _ in out}
    for creator, (_, body) in funcs.items():
        calls = [m.group(1) for line in body for m in re.finditer(r"createTask(?:WithId)?\((\w+),", line)]
        if len(set(calls)) != 1 or calls[0] not in funcs:
            continue
        update = calls[0]
        m = re.match(r"(?:const\s+)?(\w+)\s*\*", funcs[update][0])
        if not m:
            continue
        if m.group(1) in GENERIC_TASKS:
            # the task of an event or a command
            starter = re.fullmatch(r"(?:start|create)(Event|Command)(\d+)", tables.get(creator, creator))
            if starter:
                out.append((update, f"update{starter.group(1)}{starter.group(2)}", False))
            continue
        task = re.sub(r"^Stage(?=[A-Z])", "", m.group(1))
        out.append((update, f"update{task}", False))
        out.append((creator, f"create{task}", False))
    return out


def included_names(text):
    """The functions and data the stage takes from src/stages/common"""
    names = set()
    for m in re.finditer(r'^#include "(common/\w+\.inc\.c)"', text, re.M):
        inc = (SRC / m.group(1)).read_text()
        names |= set(functions(inc)) | set(definitions(inc))
    return names


def stage_names(stage, text, versions, commands):
    """{function: name} for a stage, agreed by every version that builds it"""
    per_version = []
    taken = included_names(text)
    for v in versions:
        source = preprocess(text, v)
        taken |= set(functions(source)) | set(definitions(source))
        names = {}
        clash = set()
        for f, new, table in structural_names(source, commands, stage):
            if f in names and names[f][0] != new:
                if names[f][1] == table:
                    clash.add(f)
                continue
            names.setdefault(f, (new, table))
        per_version.append({f: n for f, (n, _) in names.items() if f not in clash})
    first = per_version[0]
    out = {f: n for f, n in first.items()
           if AUTO.match(f) and n not in taken and all(names.get(f) == n for names in per_version[1:])}
    counts = {}
    for n in out.values():
        counts[n] = counts.get(n, 0) + 1
    return {f: n for f, n in out.items() if counts[n] == 1}


def rename_linked(stage, renames):
    """Renames FIELDSTG's WSTAGnnn_ names of a stage's functions"""
    prefix = stage.upper() + "_"
    pattern = re.compile(r"\b" + prefix + r"(func_[0-9A-F]{8})\b")
    for path in LINKED:
        text = path.read_text()
        new = pattern.sub(lambda m: prefix + renames.get(m.group(1), m.group(1)), text)
        if new != text:
            path.write_text(new)


def main():
    parser = argparse.ArgumentParser(description="Names a stage's functions after what calls them.")
    parser.add_argument("stages", nargs="*")
    args = parser.parse_args()
    has = {v: stage_list(v) for v in VERSIONS}
    stages = args.stages or sorted(p.stem for p in SRC.glob("wstag[0-9][0-9][0-9].c"))
    commands = script_commands()
    total = 0
    for stage in stages:
        path = SRC / f"{stage}.c"
        text = path.read_text()
        versions = [v for v in VERSIONS if stage in has[v]]
        if not versions:
            continue
        renames = stage_names(stage, text, versions, commands.get(stage, []))
        if not renames:
            continue
        path.write_text(re.sub(r"\bfunc_[0-9A-F]{8}\b", lambda m: renames.get(m.group(0), m.group(0)), text))
        rename_linked(stage, renames)
        for v in versions:
            # A func_ name is us's address, or the version's own in a stage us hasn't;
            # else the version's symbol file has it, or its last link does
            if v == "us" or "us" not in versions:
                addresses = {f: int(AUTO.match(f).group(1), 16) for f in renames}
            else:
                elf = elf_addresses(v, stage)
                addresses = {f: elf.get(f, elf.get(n)) for f, n in renames.items()}
                addresses = {f: a for f, a in addresses.items() if a is not None}
            update_symbols(CONFIG / v / "stages" / f"{stage}.txt", renames, addresses, HEADER, " // type:func")
        total += len(renames)
    print(f"{total} functions named", file=sys.stderr)


if __name__ == "__main__":
    main()
