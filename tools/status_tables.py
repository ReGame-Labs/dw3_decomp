#!/usr/bin/env python3
"""Write the progress figures of README.md's status table and of
docs/binaries.md's overlay table from `make report`.

    tools/status_tables.py                 write both tables
    tools/status_tables.py --check         fail if a figure differs
    tools/status_tables.py --check eu ...  the same, needing those versions

The figures come from build/<version>/report.json, which `make
VERSION=<version> report` writes, for each version that has one: the
README's rows of that version (the executable's game code, the 21
overlays, the stages and the total: functions in C, code and data), and,
from the USA version's report, the "Functions in C (us)" column of
docs/binaries.md (one row per overlay, and WSTAG### for the stages). The
rest of the tables, the parts' names and what each overlay runs, is
written by hand.

The CI builds each version in a job of its own and runs --check after
`make report`, so each job checks the figures of its version.
"""
import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
README = ROOT / "README.md"
BINARIES = ROOT / "docs" / "binaries.md"

# in the order of the README's rows
VERSIONS = {"eu": "Europe", "us": "USA", "jp": "Japan"}
# the version docs/binaries.md describes
BINARIES_VERSION = "us"
MEASURES = ("matched_functions", "total_functions", "matched_code", "total_code",
            "matched_data", "total_data")


def load(version):
    path = ROOT / "build" / version / "report.json"
    if not path.exists():
        return None
    with open(path) as f:
        return json.load(f)


def sums(categories):
    """The measures of a set of report categories, summed."""
    total = dict.fromkeys(MEASURES, 0)
    for category in categories:
        for key in MEASURES:
            total[key] += int(category["measures"].get(key) or 0)
    return total


def cells(m):
    """Functions in C, code and data, as the tables write them."""
    return [f"{m['matched_functions']:,} / {m['total_functions']:,}",
            f"{100 * m['matched_code'] / max(m['total_code'], 1):.2f} %",
            f"{100 * m['matched_data'] / max(m['total_data'], 1):.2f} %"]


def readme_rows(version, report):
    """The README's rows of one version: the parts, then the total."""
    game = [c for c in report["categories"] if c["id"] == "game"]
    stages = [c for c in report["categories"] if c["id"] == "stages"]
    overlays = [c for c in report["categories"] if c["id"] not in ("game", "stages")]
    total = {key: int(report["measures"].get(key) or 0) for key in MEASURES}
    return {
        "game": cells(sums(game)),
        "overlays": cells(sums(overlays)),
        "stages": cells(sums(stages)),
        "total": cells(total),
    }


def update_readme(text, reports):
    """README.md's text with the rows of the versions in reports rewritten.

    Each part has one row per version: the first names the part, the
    others leave it empty, and the total's are in bold."""
    lines = text.split("\n")
    start = next(i for i, line in enumerate(lines)
                 if line.startswith("| Part | Version | Functions in C |"))
    part = None
    for i in range(start + 2, len(lines)):
        cols = [c.strip() for c in lines[i].strip().strip("|").split("|")]
        if not lines[i].startswith("|") or len(cols) != 5:
            break
        if cols[0]:
            name = cols[0].strip("*")
            part = ("game" if name.startswith("Executable") else
                    "overlays" if "overlays" in name else
                    "stages" if "stages" in name else "total")
        version = next((v for v, label in VERSIONS.items() if cols[1].strip("*") == label), None)
        if version not in reports:
            continue
        values = readme_rows(version, reports[version])[part]
        if part == "total":
            values = [f"**{v}**" for v in values]
        lines[i] = "|" + "".join(f" {c} |" if c else " |" for c in cols[:2] + values)
    return "\n".join(lines)


def update_binaries(text, report):
    """docs/binaries.md's text with the overlays' functions rewritten."""
    measures = {c["id"]: c["measures"] for c in report["categories"]}

    def row(match):
        name, count, loads, functions, what = match.groups()
        key = "stages" if name.startswith("WSTAG") else name.lower()
        if key in measures:
            m = measures[key]
            functions = f"{int(m['matched_functions']):,} / {int(m['total_functions']):,}"
        return f"| `{name}`{count or ''} | {loads} | {functions} | {what}"

    # | `NAME` | `0x...` | n / n | what it runs |, and | `WSTAG###` (238) | ...
    pattern = re.compile(r"^\| `([A-Z_#0-9]+)`( \(\d+\))? \| (`0x[0-9A-F]+`) \| ([\d,]+ / [\d,]+) \| (.*)$",
                         re.M)
    return pattern.sub(row, text)


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("--check", nargs="*", metavar="VERSION",
                        help="fail if a figure differs, instead of writing it;"
                             " the versions named must have a report")
    args = parser.parse_args()

    reports = {v: r for v in VERSIONS if (r := load(v)) is not None}
    missing = [v for v in (args.check or []) if v not in reports]
    if missing or not reports:
        names = ", ".join(f"build/{v}/report.json" for v in missing or VERSIONS)
        sys.exit(f"no {names}: run make VERSION=<version> report first")

    files = {README: update_readme(README.read_text(), reports)}
    if BINARIES_VERSION in reports:
        files[BINARIES] = update_binaries(BINARIES.read_text(), reports[BINARIES_VERSION])

    checked = ", ".join(reports)
    stale = [path for path, text in files.items() if path.read_text() != text]
    if args.check is not None:
        if stale:
            for path in stale:
                print(f"{path.relative_to(ROOT)} differs from the report ({checked}):"
                      " run tools/status_tables.py", file=sys.stderr)
            sys.exit(1)
        print(f"the tables agree with the report ({checked})")
        return
    for path in stale:
        path.write_text(files[path])
        print(f"wrote {path.relative_to(ROOT)}")
    if not stale:
        print(f"the tables were up to date ({checked})")


if __name__ == "__main__":
    main()
