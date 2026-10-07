#!/usr/bin/env python3
"""
Names a stage's data after the function that uses it.

What the stage's tables don't name (tools/name_stage_data.py) is mostly the
data that its functions read: animation frames, spots and the like. This
names a datum that one named function alone uses (not a func_XXXXXXXX)
after it, by kind:

    AnimFrame, StageTileFrame, ...Frame       <function>Frames
    StageEffectSpot, ...Spot                  <function>Spots
    StageSeqStep                              <function>Steps
    StageQuad, StageQuadTexture               <function>Quads, <function>Textures
    StageFallParams                           <function>Params

numbered in the order the function first uses them (<function>Frames0,
<function>Frames1...) when it uses several of a kind; and a datum that only
one named table holds, after the table and its place in it: <table>_<i>.
A datum that only one version of a stage has, or whose name the stage
already has, keeps its address name. The names go into the C and both
versions' config/<version>/stages/<stage>.txt (then `make regenerate` each
version). Only splat's names (D_XXXXXXXX) are renamed, so it can be run
again at any time:

    tools/name_stage_uses.py [wstag200 ...]
"""
import argparse
import re
import sys

from name_stage_data import (
    AUTO, CONFIG, SRC, VERSIONS, definitions, elf_addresses, preprocess, stage_list, update_symbols,
)
from name_stage_funcs import functions, included_names

HEADER = "// named by the function or table that uses them (tools/name_stage_uses.py)"
KINDS = (
    (re.compile(r"^(AnimFrame|Stage\w*Frame)$"), "Frames"),
    (re.compile(r"^Stage\w*Spot$"), "Spots"),
    (re.compile(r"^StageSeqStep$"), "Steps"),
    (re.compile(r"^StageQuad$"), "Quads"),
    (re.compile(r"^StageQuadTexture$"), "Textures"),
    (re.compile(r"^StageFallParams$"), "Params"),
)
TOKEN = re.compile(r"\b\w+\b")


def kind(type_name):
    for pattern, suffix in KINDS:
        if pattern.match(type_name):
            return suffix
    return None


def leaves(init):
    """The top-level items of an initializer, each flattened to its text"""
    def flat(item):
        return item if isinstance(item, str) else " ".join(flat(i) for i in item)

    return [flat(i) for i in init] if isinstance(init, list) else [init]


def use_names(text):
    """[(datum, name)] that the stage's functions and tables give its data"""
    defs = definitions(text)
    funcs = functions(text)
    users = {}  # datum: set of (kind, user)
    first_use = {}  # (function, datum): the order of its first use in the function
    for f, (_, body) in funcs.items():
        order = 0
        for line in body:
            for tok in TOKEN.findall(line):
                if tok in defs:
                    users.setdefault(tok, set()).add(("function", f))
                    if (f, tok) not in first_use:
                        first_use[(f, tok)] = order
                        order += 1
    holders = {}  # datum: [(table, index)]
    for table, (_, _, init) in defs.items():
        for i, leaf in enumerate(leaves(init)):
            for tok in TOKEN.findall(leaf):
                if tok in defs and tok != table:
                    users.setdefault(tok, set()).add(("table", table))
                    holders.setdefault(tok, []).append((table, i))

    out = {}
    by_function = {}
    for datum, (type_name, _, _) in defs.items():
        u = users.get(datum, set())
        suffix = kind(type_name)
        if not AUTO.match(datum) or suffix is None or len(u) != 1:
            continue
        (what, f), = u
        if what != "function" or f.startswith("func_"):
            continue
        by_function.setdefault((f, suffix), []).append(datum)
    for (f, suffix), data in by_function.items():
        data.sort(key=lambda d: first_use[(f, d)])
        for n, datum in enumerate(data):
            out[datum] = f + suffix + (str(n) if len(data) > 1 else "")

    # then the data that only one table holds, once, after the table
    changed = True
    while changed:
        changed = False
        for datum in defs:
            if datum in out or not AUTO.match(datum) or len(users.get(datum, ())) != 1:
                continue
            held = holders.get(datum, [])
            if len(held) != 1:
                continue
            table, i = held[0]
            name = out.get(table, table)
            if AUTO.match(name) or name.startswith("func_"):
                continue
            out[datum] = f"{name}_{i}"
            changed = True
    return list(out.items())


def stage_names(text, versions):
    """{datum: name} for a stage, agreed by every version that builds it"""
    per_version = []
    taken = included_names(text)
    for v in versions:
        source = preprocess(text, v)
        taken |= set(functions(source)) | set(definitions(source))
        per_version.append(dict(use_names(source)))
    first = per_version[0]
    out = {d: n for d, n in first.items()
           if n not in taken and all(names.get(d) == n for names in per_version[1:])}
    counts = {}
    for n in out.values():
        counts[n] = counts.get(n, 0) + 1
    return {d: n for d, n in out.items() if counts[n] == 1}


def main():
    parser = argparse.ArgumentParser(description="Names a stage's data after the function that uses it.")
    parser.add_argument("stages", nargs="*")
    args = parser.parse_args()
    has = {v: stage_list(v) for v in VERSIONS}
    stages = args.stages or sorted(p.stem for p in SRC.glob("wstag[0-9][0-9][0-9].c"))
    total = 0
    for stage in stages:
        path = SRC / f"{stage}.c"
        text = path.read_text()
        versions = [v for v in VERSIONS if stage in has[v]]
        if not versions:
            continue
        renames = stage_names(text, versions)
        if not renames:
            continue
        path.write_text(re.sub(r"\bD_[0-9A-F]{8}\b", lambda m: renames.get(m.group(0), m.group(0)), text))
        for v in versions:
            # A D_ name is us's address, or the version's own in a stage us hasn't;
            # else the version's symbol file has it, or its last link does
            if v == "us" or "us" not in versions:
                addresses = {d: int(AUTO.match(d).group(1), 16) for d in renames}
            else:
                elf = elf_addresses(v, stage)
                addresses = {d: elf.get(d, elf.get(n)) for d, n in renames.items()}
                addresses = {d: a for d, a in addresses.items() if a is not None}
            update_symbols(CONFIG / v / "stages" / f"{stage}.txt", renames, addresses, HEADER)
        total += len(renames)
    print(f"{total} data named", file=sys.stderr)


if __name__ == "__main__":
    main()
