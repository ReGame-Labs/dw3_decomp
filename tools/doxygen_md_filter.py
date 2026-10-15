#!/usr/bin/env python3
"""Doxygen's input filter for the Markdown pages (docs/Doxyfile): gives each
heading the anchor GitHub gives it, so that the pages' links to a heading
(`[Code](#code)`, `[Tools](../CONTRIBUTING.md#tools)`) work in the
documentation too; the files never change.

    tools/doxygen_md_filter.py FILE    prints FILE filtered, line for line

doxygen 1.9 doesn't make GitHub's anchors, and its labels are global, so a
heading of docs/toolchain.md gets {#docs_toolchain_<anchor>} and the links
are rewritten to it. A page's first heading gets the page's own label
(docs_toolchain), the target of the links to the page itself; README.md's
stays the main page (USE_MDFILE_AS_MAINPAGE).
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MAINPAGE = "README.md"
HEADING = re.compile(r"^(#{1,6})\s+(.*?)\s*#*\s*$")
LINK = re.compile(r"\]\(([^)\s#]*)#([^)\s]+)\)")
# a link to a file or folder of the repository, such as "(../src/engine/system/main.c)"
FILE_LINK = re.compile(r"\]\(([^)\s#:]+)\)")
SOURCE = re.compile(r"^(src|include)/.*(\.[ch]|/)$")
REPOSITORY = "https://github.com/ReGame-Labs/dw3_decomp"


def page_id(path):
    """docs/toolchain.md -> docs_toolchain"""
    return re.sub(r"\W", "_", os.path.splitext(path)[0])


def github_anchor(title):
    """GitHub's anchor of a heading: lower case, without punctuation, - for spaces"""
    title = re.sub(r"`|\*\*|\[([^]]*)\]\([^)]*\)", r"\1", title).lower()
    return re.sub(r"[^\w\- ]", "", title).replace(" ", "-")


def file_link(here, target):
    """A link to a source file or folder goes to its page; one to another file
    (a tool, a Markdown page doxygen links itself) stays or goes to GitHub"""
    if target.endswith(".md"):
        return target
    path = os.path.normpath(os.path.join(here, target))
    folder = os.path.isdir(os.path.join(ROOT, path))
    if SOURCE.match(path + ("/" if folder else "")):
        # doxygen finds a file by its path after STRIP_FROM_INC_PATH (src, include)
        return "@ref " + (path if folder else path.split("/", 1)[1])
    return f"{REPOSITORY}/{'tree' if folder else 'blob'}/main/{path}"


def filter_md(text, path):
    page = page_id(path)
    here = os.path.dirname(path)
    out = []
    fence = False
    first = True
    for line in text.split("\n"):
        if line.lstrip().startswith("```"):
            fence = not fence
        elif not fence:
            m = HEADING.match(line)
            if m:
                if first:
                    first = False
                    if path != MAINPAGE:
                        line = f"{m.group(1)} {m.group(2)} {{#{page}}}"
                else:
                    line = f"{m.group(1)} {m.group(2)} {{#{page}_{github_anchor(m.group(2))}}}"
            else:
                def relink(m):
                    target = page if not m.group(1) else page_id(os.path.normpath(os.path.join(here, m.group(1))))
                    return f"](#{target}_{m.group(2)})"
                line = LINK.sub(relink, line)
                line = FILE_LINK.sub(lambda m: "](" + file_link(here, m.group(1)) + ")", line)
        out.append(line)
    return "\n".join(out)


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__.split("\n\n")[1])
    path = os.path.relpath(os.path.abspath(sys.argv[1]), ROOT)
    with open(sys.argv[1], encoding="utf-8") as f:
        text = f.read()
    sys.stdout.write(filter_md(text, path))


if __name__ == "__main__":
    main()
