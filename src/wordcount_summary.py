#!/usr/bin/env python3
"""Summarise texcount output as a chapter/section/subsection tree.

Reads the per-subcount output produced by `texcount -inc main.tex`
(e.g. _build/wordcount.txt) and reports, for every chapter, section and
subsection, both its own word count and the total rolled up from all of
its descendants. File divisions in the texcount output are ignored: the
structure is derived purely from the Chapter/Section/Subsection headings.

Usage:
    python3 wordcount_summary.py [wordcount.txt]

Defaults to _build/wordcount.txt relative to this script.
"""

import os
import re
import sys

# Matches a texcount subcount line, e.g.
#   751+1+0 (1/0/0/0) Section: Context
#   1338+25+0 (9/0/8/0) Subsection: SMT representations}\label{subsec:smt-rep
SUBCOUNT_RE = re.compile(
    r"^\s*(\d+)\+(\d+)\+(\d+)\s*\(([^)]*)\)\s*(.*)$"
)

LEVELS = {"Chapter": 0, "Section": 1, "Subsection": 2, "Subsubsection": 3}


class Node:
    def __init__(self, level, title, text=0, headers=0, captions=0):
        self.level = level          # -1 for the synthetic root
        self.title = title
        self.text = text            # own words in text
        self.headers = headers      # own words in headers
        self.captions = captions    # own words in captions/floats
        self.children = []

    @property
    def own(self):
        return self.text + self.headers + self.captions

    def total(self):
        return self.own + sum(c.total() for c in self.children)

    def total_text(self):
        return self.text + sum(c.total_text() for c in self.children)


def clean_title(raw):
    """Strip LaTeX cruft from a heading title for display."""
    t = raw.strip()
    # Drop a trailing }\label{...} (texcount includes the label).
    t = re.sub(r"\}?\\label\{[^}]*\}?.*$", "", t)
    # Remove \kl[..]{..} / \kl{..} and \cinline{..} style wrappers, keep arg.
    t = re.sub(r"\\[a-zA-Z]+(?:\[[^\]]*\])?\{([^{}]*)\}", r"\1", t)
    t = re.sub(r"\\[a-zA-Z]+(?:\[[^\]]*\])?\{([^{}]*)\}", r"\1", t)
    # Remaining stray control sequences and braces.
    t = re.sub(r"\\[a-zA-Z]+\\?", "", t)
    t = t.replace("{", "").replace("}", "").replace("\\", "")
    t = re.sub(r"\s+", " ", t).strip()
    return t or "(untitled)"


def parse(path):
    root = Node(-1, "ROOT")
    # stack[i] is the currently-open node whose level == i-1 in the tree.
    stack = [root]
    pending_top = None  # a _top_ block seen before any chapter opens

    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            m = SUBCOUNT_RE.match(line)
            if not m:
                continue
            text, headers, captions = int(m[1]), int(m[2]), int(m[3])
            label = m[5].strip()

            # Skip file-total summary lines.
            if label.startswith("File:") or label.startswith("Included file:"):
                continue

            # Identify the structural level.
            level = None
            title = None
            for name, lvl in LEVELS.items():
                if label == name or label.startswith(name + ":") \
                        or label.startswith(name + "}") \
                        or label.startswith(name + " "):
                    level = lvl
                    rest = label[len(name):].lstrip(": ")
                    title = clean_title(rest) if rest else name
                    break

            if level is None:
                # _top_ or other non-structural material: fold into the
                # nearest open node (or a preamble bucket) as extra own words.
                target = stack[-1]
                if target is root:
                    if pending_top is None:
                        pending_top = Node(0, "(front matter)")
                        root.children.append(pending_top)
                    target = pending_top
                target.text += text
                target.headers += headers
                target.captions += captions
                continue

            node = Node(level, title, text, headers, captions)
            # Pop until the top of stack is the correct parent (level-1).
            while len(stack) > 1 and stack[-1].level >= level:
                stack.pop()
            stack[-1].children.append(node)
            stack.append(node)

    return root


def md_escape(text):
    return text.replace("|", "\\|")


def render(root):
    """Render the tree as nested markdown tables.

    A top-level summary table lists the chapters; each chapter then gets
    its own heading and table of sections/subsections, with nesting shown
    by indentation in the first column.
    """
    lines = []

    # Non-breaking spaces so markdown renderers keep the indentation.
    nbsp = "    "
    prefix = {1: "", 2: nbsp, 3: nbsp * 2}

    # --- Summary of chapters -------------------------------------------
    lines.append("# Word counts")
    lines.append("")
    lines.append("Counts are `text + headers + captions`. **Own** is the "
                 "prose directly under a heading; **Total** rolls up all "
                 "descendants.")
    lines.append("")
    lines.append("## Chapters")
    lines.append("")
    lines.append("| Chapter | Total | Own |")
    lines.append("| :-- | --: | --: |")
    for ch in root.children:
        if ch.own == ch.total():
            total_cell, own_cell = "", f"**{ch.own}**"
        else:
            total_cell, own_cell = f"**{ch.total()}**", str(ch.own)
        lines.append(f"| {md_escape(ch.title)} | {total_cell} | {own_cell} |")
    lines.append("")
    lines.append(f"| **Document total** | **{sum(c.total() for c in root.children)}** | |")
    lines.append("")

    # --- One table per chapter -----------------------------------------
    def count_cells(node):
        """(total_cell, own_cell): if own == total, blank the total and
        show the value under Own; otherwise show both."""
        if node.own == node.total():
            return "", str(node.own)
        return str(node.total()), str(node.own)

    def sub_rows(node, depth, acc):
        """Emit rows for subsections (and deeper): blank Section column,
        the subsection title in the second column (indented by depth)."""
        for child in node.children:
            pad = nbsp * depth
            total_cell, own_cell = count_cells(child)
            acc.append(
                f"|  | {pad}{md_escape(child.title)} | "
                f"{total_cell} | {own_cell} |"
            )
            sub_rows(child, depth + 1, acc)

    for ch in root.children:
        lines.append(f"## {md_escape(ch.title)}")
        lines.append("")
        lines.append(f"**Chapter total: {ch.total()}** "
                     f"(own {ch.own})")
        lines.append("")

        sections = [c for c in ch.children if c.level == 1]
        if sections:
            lines.append("| Section | Subsection | Total | Own |")
            lines.append("| :-- | :-- | --: | --: |")
            for sec in sections:
                total_cell, own_cell = count_cells(sec)
                lines.append(
                    f"| {md_escape(sec.title)} |  | "
                    f"{total_cell} | {own_cell} |"
                )
                sub_rows(sec, 0, lines)
            lines.append("")

    return "\n".join(lines).rstrip() + "\n"


def main():
    here = os.path.dirname(os.path.abspath(__file__))
    default = os.path.join(here, "_build", "wordcount.txt")
    path = sys.argv[1] if len(sys.argv) > 1 else default
    if not os.path.exists(path):
        sys.exit(f"No such file: {path}")
    print(render(parse(path)))


if __name__ == "__main__":
    main()
