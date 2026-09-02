#!/usr/bin/env python3
"""Turn clang's -fproc-stat-report output into a Markdown report.

The report is meant to be written straight into $GITHUB_STEP_SUMMARY, where GitHub renders it on the
run page. Give it a baseline to get a delta column, which is the part worth reading: a ranking of
what is expensive today gets looked at twice, whereas "this file gained 400 MB since main" is
actionable.

  compile_cost.py current.csv                        # a plain ranking
  compile_cost.py current.csv --baseline main.csv    # with the delta against main
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


def read(path):
    """Peak RSS in KiB and CPU microseconds, keyed by the translation unit."""
    out = {}
    with open(path, newline="") as f:
        for row in csv.reader(f):
            if len(row) != FIELDS:
                continue
            try:
                out[unit_of(row[1])] = (int(row[4]), int(row[3]))
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
    s = sec(usec)
    return "%.1f s" % s if s < 90 else "%.0f min" % (s / 60)


def delta_cell(now, before):
    if before is None:
        return "new"
    if before == 0:
        return "—"
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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("current")
    ap.add_argument("--baseline")
    ap.add_argument("--top", type=int, default=20)
    ap.add_argument("--title", default="Compile cost")
    ap.add_argument("--full", help="write the complete per-unit table, as Markdown, to this file")
    args = ap.parse_args()

    now = read(args.current)
    if not now:
        print("No measurement in `%s`." % args.current)
        return 0

    was = read(args.baseline) if args.baseline else {}
    d = bool(was)

    total_mem = sum(v[0] for v in now.values())
    total_cpu = sum(v[1] for v in now.values())
    worst, (worst_mem, _) = max(now.items(), key=lambda kv: kv[1][0])

    print("## %s\n" % args.title)
    print("%d translation unit%s. Peak memory adds up to %s, and the whole build costs %s of CPU. "
          "The heaviest single unit is `%s` at %s.\n"
          % (len(now), "" if len(now) == 1 else "s", size(total_mem), duration(total_cpu),
             worst, size(worst_mem)))

    # Regressions first: what changed is what gets acted on.
    if d:
        grew = [(k, v[0], was[k][0]) for k, v in now.items()
                if k in was and v[0] > was[k][0] * 1.05 and v[0] - was[k][0] > 16 * 1024]
        grew.sort(key=lambda t: t[1] - t[2], reverse=True)
        if grew:
            print("> **%d unit%s grew by more than 5 %% and 16 MiB.**\n"
                  % (len(grew), "" if len(grew) == 1 else "s"))
            print(table([(k, m, now[k][1], delta_cell(m, b)) for k, m, b in grew[:10]],
                        "Grew", True))
            print()
        else:
            print("> Nothing grew by more than 5 % against the baseline.\n")

    # Per module: ten-odd rows, which is the only view that fits a suite this size.
    mods = {}
    for k, (mem, cpu) in now.items():
        m = module_of(k)
        a = mods.setdefault(m, [0, 0, 0])
        a[0] += mem
        a[1] += cpu
        a[2] += 1
    base_mods = {}
    for k, (mem, _) in was.items():
        base_mods[module_of(k)] = base_mods.get(module_of(k), 0) + mem

    rows = sorted(((m, v[0], v[1], delta_cell(v[0], base_mods.get(m))) for m, v in mods.items()),
                  key=lambda r: r[1], reverse=True)
    print("### By module\n")
    print(table(rows, "Module", d))
    print()

    ranked = sorted(now.items(), key=lambda kv: kv[1][0], reverse=True)
    print("### The %d heaviest units\n" % min(args.top, len(ranked)))
    print(table([(k, v[0], v[1], delta_cell(v[0], was.get(k, (None,))[0]))
                 for k, v in ranked[: args.top]], "Translation unit", d))

    if args.full:
        # The summary is capped at a mebibyte and nobody reads seven hundred rows on a run page.
        # The whole table goes to a file the workflow attaches, so nothing measured is thrown away.
        with open(args.full, "w") as f:
            f.write("# %s, every translation unit\n\n" % args.title)
            f.write("%d unit%s, %s of peak memory, %s of CPU.\n\n"
                    % (len(now), "" if len(now) == 1 else "s", size(total_mem), duration(total_cpu)))
            f.write(table([(k, v[0], v[1], delta_cell(v[0], was.get(k, (None,))[0]))
                           for k, v in ranked], "Translation unit", d))
            f.write("\n")
        print("\n*Every unit is measured. The complete table and the raw CSV are attached to this run.*")
    else:
        print("\n*Every unit is measured; the full table is in the attached CSV.*")
    return 0


if __name__ == "__main__":
    sys.exit(main())
