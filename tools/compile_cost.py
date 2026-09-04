#!/usr/bin/env python3
##======================================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
"""Turn clang's -fproc-stat-report output into a Markdown report.

The summary is written for $GITHUB_STEP_SUMMARY, where GitHub renders it on the run page, and the full
table for a file the run attaches. Give it a baseline to get a delta column, which is the part worth
reading: a ranking of what is expensive today gets looked at twice, where "this file gained 400 MB
since main" is acted on.

  compile_cost.py current.csv                        # a plain ranking, to stdout
  compile_cost.py current.csv --baseline main.csv    # with the delta against main

CPU time is added up wherever it appears, because compiling two units really does cost the sum of
the two. Peak memory is never added up: the peaks belong to processes that do not run at the same
time, and their sum matches no quantity any machine ever has to hold. What answers the question a
peak is asked for, how much memory a build needs and how many compilers a host can carry, is the
largest single unit and the shape of the distribution behind it.
"""

import argparse
import csv
import os
import sys

# clang writes, with no header: "program","output",total_us,user_us,peak_rss_kb
FIELDS = 5


def unit_of(output):
    """The source a CMake object path came from, as `module/core/add.cpp`.

    Object files live in `<build>/test/unit/CMakeFiles/<target>.dir/<path>.o`, so everything up to
    the `.dir/` is build layout and everything after it is what a reader recognises.
    """
    marker = ".dir/"
    i = output.find(marker)
    name = output[i + len(marker):] if i >= 0 else os.path.basename(output)
    return name[:-2] if name.endswith(".o") else name


def module_of(unit):
    """The two first path components, which is how the suite is laid out and reported."""
    parts = unit.split("/")
    return "/".join(parts[:2]) if len(parts) > 2 else (parts[0] if len(parts) > 1 else "top level")


def read(path, strip=""):
    """Peak RSS in KiB and CPU microseconds, keyed by the translation unit.

    A multi-config generator files the objects under `<target>.dir/<config>/`, and that segment is
    build layout too: `strip` names it, and is left alone where it is not there.
    """
    out = {}
    with open(path, newline="") as f:
        for row in csv.reader(f):
            if len(row) != FIELDS:
                continue
            try:
                unit = unit_of(row[1])
                if strip and unit.startswith(strip):
                    unit = unit[len(strip):]
                out[unit] = (int(row[4]), int(row[3]))
            except ValueError:
                continue
    return out


def mib(kib):
    return kib / 1024.0


def sec(usec):
    return usec / 1e6


def size(kib):
    """MiB below a gibibyte, GiB above: a report nobody has to convert in their head."""
    return "%.0f MiB" % mib(kib) if kib < 1024 * 1024 else "%.2f GiB" % (mib(kib) / 1024)


def duration(usec):
    """Tenths of a second under a minute, then hours, minutes and seconds, a part written only when it is not zero."""
    s = sec(usec)
    if s < 59.95:
        return "%.1f s" % s
    hours, rest = divmod(int(round(s)), 3600)
    minutes, seconds = divmod(rest, 60)
    parts = [(hours, "h"), (minutes, "min"), (seconds, "s")]
    return " ".join("%d %s" % (value, unit) for value, unit in parts if value)


def quantile(values, q):
    """Nearest-rank, on an already sorted list."""
    return values[min(len(values) - 1, int(q * len(values)))]


def delta_cell(now, before):
    if before is None:
        return "new"
    if before == 0:
        return "n/a"
    pct = 100.0 * (now - before) / before
    if abs(pct) < 1.0:
        return "="
    return "%+.0f %%" % pct


def table(rows, header, with_delta):
    head = "| %s | Peak RSS | CPU |" % header
    rule = "|---|--:|--:|"
    if with_delta:
        head += " Δ RSS |"
        rule += "--:|"
    out = [head, rule]
    for name, mem, cpu, d in rows:
        line = "| `%s` | %s | %s |" % (name, size(mem), duration(cpu))
        if with_delta:
            line += " %s |" % d
        out.append(line)
    return "\n".join(out)


def by_module(measures):
    """Units grouped under their module, each group sorted heaviest first."""
    groups = {}
    for unit, (mem, cpu) in measures.items():
        groups.setdefault(module_of(unit), []).append((unit, mem, cpu))
    for units in groups.values():
        units.sort(key=lambda u: u[1], reverse=True)
    return groups


def headline(measures, title, level, grew_line=None):
    """The facts worth stating before any table, as a list rather than a paragraph."""
    peaks = sorted(m for m, _ in measures.values())
    total_cpu = sum(c for _, c in measures.values())
    worst, (worst_mem, worst_cpu) = max(measures.items(), key=lambda kv: kv[1][0])

    groups = by_module(measures)
    top_mod, top_units = max(groups.items(), key=lambda kv: sum(u[2] for u in kv[1]))
    top_cpu = sum(u[2] for u in top_units)

    out = ["%s %s\n" % ("#" * level, title)]
    out.append("- **%d translation units**, %s of CPU in all."
               % (len(measures), duration(total_cpu)))
    out.append("- The heaviest one is `%s`, peaking at **%s** over %s."
               % (worst, size(worst_mem), duration(worst_cpu)))
    out.append("- Half of them peak under %s, a tenth above %s."
               % (size(quantile(peaks, 0.5)), size(quantile(peaks, 0.9))))
    share = "%.0f %%" % (100.0 * top_cpu / total_cpu) if total_cpu else "n/a"
    out.append("- `%s` carries %s of that CPU on its own, %s of the build, over %d units."
               % (top_mod, duration(top_cpu), share, len(top_units)))
    if grew_line:
        out.append(grew_line)
    return "\n".join(out) + "\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("current")
    ap.add_argument("--baseline")
    ap.add_argument("--top", type=int, default=3, help="units shown per module (default 3)")
    ap.add_argument("--title", default="Compile cost")
    ap.add_argument("--full", help="write the complete per-unit table, as Markdown, to this file")
    ap.add_argument("--summary", help="write the summary to this file rather than to stdout")
    ap.add_argument("--strip", default="", help="path segment a multi-config generator adds, e.g. Debug/")
    args = ap.parse_args()

    out = open(args.summary, "w") if args.summary else sys.stdout

    now = read(args.current, args.strip)
    if not now:
        print("No measurement in `%s`." % args.current, file=out)
        return 0

    was = read(args.baseline, args.strip) if args.baseline else {}
    d = bool(was)

    # Regressions first: what changed is what gets acted on.
    grew = []
    if d:
        grew = [(k, v[0], was[k][0]) for k, v in now.items()
                if k in was and v[0] > was[k][0] * 1.05 and v[0] - was[k][0] > 16 * 1024]
        grew.sort(key=lambda t: t[1] - t[2], reverse=True)

    grew_line = None
    if d:
        grew_line = ("- **%d unit%s grew** by more than 5 %% and 16 MiB against the baseline."
                     % (len(grew), "" if len(grew) == 1 else "s")) if grew \
                    else "- Nothing grew by more than 5 % against the baseline."

    print(headline(now, args.title, 2, grew_line), file=out)

    if grew:
        print("\n### What grew\n", file=out)
        print(table([(k, m, now[k][1], delta_cell(m, b)) for k, m, b in grew[:10]],
                    "Translation unit", True), file=out)

    # One table per module: a suite this size has no single ranking anybody reads, but every module
    # has an owner who recognises its own three worst files.
    groups = by_module(now)
    ordered = sorted(groups.items(), key=lambda kv: sum(u[2] for u in kv[1]), reverse=True)

    for module, units in ordered:
        cpu = sum(u[2] for u in units)
        print("\n### `%s`\n" % module, file=out)
        print("%d unit%s, %s of CPU, heaviest at %s.\n"
              % (len(units), "" if len(units) == 1 else "s", duration(cpu), size(units[0][1])), file=out)
        # The module is a prefix of its units' names, except for the synthetic top level, where the name is kept whole.
        rows = [(u[0][len(module) + 1:] if u[0].startswith(module + "/") else u[0], u[1], u[2],
                 delta_cell(u[1], was.get(u[0], (None,))[0]))
                for u in units[: args.top]]
        print(table(rows, "Translation unit", d), file=out)

    if args.full:
        # The summary is capped at a mebibyte and nobody reads seven hundred rows on a run page.
        # The whole table goes to a file the workflow attaches, so nothing measured is thrown away.
        ranked = sorted(now.items(), key=lambda kv: kv[1][0], reverse=True)
        with open(args.full, "w") as f:
            f.write(headline(now, "%s, every translation unit" % args.title, 1, grew_line))
            f.write("\n")
            f.write(table([(k, v[0], v[1], delta_cell(v[0], was.get(k, (None,))[0]))
                           for k, v in ranked], "Translation unit", d))
            f.write("\n")
        print("\n*Every unit is measured. The complete table and the raw CSV are attached to this run.*", file=out)
    else:
        print("\n*Every unit is measured; the full table is in the attached CSV.*", file=out)

    if args.summary:
        out.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
