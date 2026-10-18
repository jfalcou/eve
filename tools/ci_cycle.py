#!/usr/bin/env python3
"""Wall time of the CI cycle of a commit, from its first unit job to its last.

Usage::

    tools/ci_cycle.py eve 2412                     # head of a pull request
    tools/ci_cycle.py eve de94cb57b                # a commit
    tools/ci_cycle.py eve 2412 --svg cycle.svg     # chart of every job
    tools/ci_cycle.py eve 2412 --svg cycle.svg --style colors.json
    tools/ci_cycle.py eve 2412 --markdown body.md  # pull request comment
    tools/ci_cycle.py kumi 160                     # any repository

A unit workflow is one whose name contains ``--workflow``, Unit Tests by
default. ``--style`` reads a JSON object whose keys replace those of STYLE.
The exit status is 3 while a job still runs, and 4 when a run was cancelled.

The doctests run with ``python3 -m doctest tools/ci_cycle.py``.
"""
import argparse
import html
import json
import subprocess
import sys
from dataclasses import dataclass, field
from datetime import datetime, timezone

UNIT = "Unit Tests"
PENDING = 3
LEAD = 5
CANCELLED = 4

# The colors of the chart, by name. The runners list colors each runner in
# the order of its first job.
STYLE = {
    "background": "#fbf8f4",
    "text": "#231f1c",
    "muted": "#6f655e",
    "grid": "#e4dbd2",
    "failure": "#c42a2a",
    "font": 'ui-monospace, "IBM Plex Mono", Menlo, monospace',
    "runners": ["#d9772f", "#4f6fb8", "#8a8278", "#4f9a6a", "#8d5fb8",
                "#b8a14f", "#4fa8b8", "#b84f7a"],
}


@dataclass
class Job:
    """A job of one unit workflow, its times in minutes from the cycle start.

    ``started`` is None while the job waits for a runner, ``ended`` while it
    has not ended.
    """
    workflow: str
    name: str
    labels: str
    created: float
    started: float | None
    ended: float | None
    state: str

    @property
    def duration(self):
        """Minutes from the runner pick-up to the end, None while running or
        for a job that never had a runner.

        >>> Job("x86", "native", "", 0, 2, 20, "success").duration
        18
        >>> Job("x86", "native", "", 0, None, 22, "cancelled").duration is None
        True
        """
        if self.started is None or self.ended is None:
            return None
        return self.ended - self.started


@dataclass
class Cycle:
    """Every job of the latest run of each unit workflow of one commit.

    ``now`` is the minute the API was read, where a running job's bar ends,
    and ``opened`` the minute each workflow run was created.
    """
    repo: str
    sha: str
    start: datetime
    status: dict
    jobs: list
    now: float = 0
    unit: str = UNIT
    opened: dict = field(default_factory=dict)

    @property
    def done(self):
        return [j for j in self.jobs if j.ended is not None]

    @property
    def cancelled(self):
        """True when a run of the cycle was cancelled, by a newer push.

        >>> Cycle("eve", "abc", None, {"x86": "cancelled"}, []).cancelled
        True
        """
        return "cancelled" in self.status.values()

    @property
    def pending(self):
        """Number of jobs still running or waiting for a runner.

        >>> c = Cycle("eve", "abc", None, {}, [
        ...     Job("x86", "native-x86", "", 0, 0, 18, "success"),
        ...     Job("x86", "x86-gcc", "", 18, None, None, "queued")])
        >>> c.pending
        1
        """
        return len(self.jobs) - len(self.done)

    @property
    def span(self):
        """Minutes from the first job created to the last job ended.

        >>> c = Cycle("eve", "abc", None, {}, [
        ...     Job("x86", "native-x86", "", 0, 0, 18, "success"),
        ...     Job("Hosted", "riscv", "", 0, 30, 45, "success")])
        >>> c.span
        45
        """
        return max((j.ended for j in self.done), default=0)

    @property
    def natives(self):
        """Minutes at which the last native job ended, None while one has not
        run to its end or without any.

        >>> c = Cycle("eve", "abc", None, {}, [
        ...     Job("x86", "native-x86", "", 0, 0, 18, "success"),
        ...     Job("AVX512", "native-avx512", "", 0, 0, 22, "success"),
        ...     Job("x86", "x86-gcc", "", 22, 22, 50, "success")])
        >>> c.natives
        22
        >>> gone = Job("macOS", "native-macos", "", 0, None, 30, "cancelled")
        >>> c.jobs.append(gone)
        >>> c.natives is None
        True
        """
        natives = [j for j in self.jobs if j.name.startswith("native")]
        if any(j.duration is None for j in natives):
            return None
        return max((j.ended for j in natives), default=None)

    def natives_text(self):
        """How far the native jobs are, for the reports.

        >>> Cycle("eve", "abc", None, {}, []).natives_text()
        'no native job'
        """
        natives = [j for j in self.jobs if j.name.startswith("native")]
        if not natives:
            return "no native job"
        if self.natives is None:
            done = sum(j.duration is not None for j in natives)
            return "natives %d of %d done" % (done, len(natives))
        return "natives done at %.0f min" % self.natives

    def workflows(self):
        """Per workflow, its status, its end and its longest job.

        >>> c = Cycle("eve", "abc", None, {"x86": "completed"}, [
        ...     Job("x86", "native-x86", "", 0, 0, 18, "success"),
        ...     Job("x86", "x86-gcc", "", 18, 18, 48, "success")])
        >>> c.workflows()
        [('x86', 'completed', 48, 'x86-gcc', 30)]
        """
        rows = []
        for workflow in sorted(self.status):
            done = [j for j in self.done if j.workflow == workflow]
            ran = [j for j in done if j.duration is not None]
            longest = max(ran, key=lambda j: j.duration, default=None)
            rows.append((workflow, self.status[workflow],
                         max((j.ended for j in done), default=0),
                         longest.name if longest else "",
                         longest.duration if longest else 0))
        return rows


def parse_time(text):
    """A GitHub timestamp, always in UTC.

    >>> parse_time("2026-10-16T13:56:04Z").isoformat()
    '2026-10-16T13:56:04+00:00'
    """
    stamp = datetime.strptime(text, "%Y-%m-%dT%H:%M:%SZ")
    return stamp.replace(tzinfo=timezone.utc)


def machine(labels):
    """The runner a job ran on: its last label.

    >>> machine("self-hosted,generic-x86")
    'generic-x86'
    >>> machine("ubuntu-latest")
    'ubuntu-latest'
    """
    return labels.split(",")[-1]


def label(name, unit=UNIT):
    """A workflow name without the part that marks it as a unit workflow,
    the whole name when nothing else is left.

    >>> label("EVE - Unit Tests x86")
    'x86'
    >>> label("Unit Tests")
    'Unit Tests'
    """
    rest = name.partition(unit)[2].strip(" -")
    return rest or name


def latest_runs(runs):
    """The latest run of each workflow: a nightly schedule reruns main on the
    same commit, and one cycle is one run per workflow.

    >>> runs = [{"name": "x86", "created_at": "2026-10-16T01:00:00Z"},
    ...         {"name": "x86", "created_at": "2026-10-16T13:00:00Z"}]
    >>> [r["created_at"][11:16] for r in latest_runs(runs)]
    ['13:00']
    """
    latest = {}
    for run in runs:
        kept = latest.get(run["name"])
        if kept is None or run["created_at"] > kept["created_at"]:
            latest[run["name"]] = run
    return list(latest.values())


def gh(path):
    """The JSON object at an API path, its pages merged."""
    out = subprocess.run(["gh", "api", "--paginate", "--slurp", path],
                         check=True, capture_output=True, text=True).stdout
    pages = json.loads(out)
    merged = pages[0]
    for page in pages[1:]:
        for key, value in page.items():
            if isinstance(value, list):
                merged[key] = merged[key] + value
    return merged


def is_pull_request(ref):
    """Whether a ref names a pull request: a sha has seven characters at least,
    and may hold nothing but digits.

    >>> is_pull_request("2345"), is_pull_request("565936663")
    (True, False)
    """
    return ref.isdigit() and len(ref) < 7


def head_sha(repo, ref):
    """The full commit a pull request number or a short sha names."""
    if is_pull_request(ref):
        return gh("repos/%s/pulls/%s" % (repo, ref))["head"]["sha"]
    return gh("repos/%s/commits/%s" % (repo, ref))["sha"]


def fetch(repo, ref, unit=UNIT):
    """The latest run of each unit workflow at a ref and all its jobs, times
    from the first job created."""
    sha = head_sha(repo, ref)
    runs = gh("repos/%s/actions/runs?head_sha=%s&per_page=100"
              % (repo, sha))["workflow_runs"]
    runs = latest_runs([r for r in runs if unit in r["name"]])
    if not runs:
        sys.exit("no unit workflow run for %s" % sha)
    start = min(parse_time(r["created_at"]) for r in runs)
    now = datetime.now(timezone.utc)

    def minutes(text):
        return (parse_time(text) - start).total_seconds() / 60

    jobs, status, opened = [], {}, {}
    for run in runs:
        workflow = run["name"]
        status[workflow] = run["conclusion"] or run["status"]
        opened[workflow] = minutes(run["created_at"])
        path = "repos/%s/actions/runs/%d/jobs?per_page=100" % (repo, run["id"])
        for job in gh(path)["jobs"]:
            # A job GitHub never gave a runner reports its creation as its
            # start, queued as well as cancelled before it ran.
            started = job["started_at"] if job["runner_name"] else None
            ended = job["completed_at"]
            jobs.append(Job(workflow, job["name"], ",".join(job["labels"]),
                            minutes(job["created_at"]),
                            minutes(started) if started else None,
                            minutes(ended) if ended else None,
                            job["conclusion"] or job["status"]))
    return Cycle(repo.split("/")[1], sha, start, status, jobs,
                 (now - start).total_seconds() / 60, unit, opened)


def summary(cycle):
    """The text report, times in the local zone of the machine."""
    def local(minutes):
        moment = cycle.start.timestamp() + 60 * minutes
        return datetime.fromtimestamp(moment).strftime("%H:%M")

    zone = cycle.start.astimezone().tzname()
    natives = cycle.natives_text()
    so_far = "so far " if cycle.pending else ""
    # While a job runs or waits, the cycle lasts until the reading.
    span = cycle.now if cycle.pending else cycle.span
    running = (", %d jobs still running" % cycle.pending
               if cycle.pending else "")
    if cycle.cancelled:
        running += ", cancelled"
    lines = ["%s %s  from %s to %s %s  %s%.0f min, %s%s"
             % (cycle.repo, cycle.sha[:9], local(0), local(span), zone,
                so_far, span, natives, running)]
    for workflow, status, end, job, minutes in cycle.workflows():
        head = "  %-26s %-11s ends at %3.0f min" % (workflow, status, end)
        lines.append(head + "   longest job %3.0f min  %s" % (minutes, job))
    return "\n".join(lines)


def markdown(cycle):
    """The pull request comment. Its first line is the marker the CI step
    looks for to edit the comment instead of adding one.

    >>> c = Cycle("eve", "4a2caa74a5", parse_time("2026-10-16T13:56:00Z"),
    ...           {"EVE - Unit Tests x86": "completed"},
    ...           [Job("EVE - Unit Tests x86", "x86-gcc", "", 0, 0, 18, "ok")])
    >>> print(markdown(c))
    <!-- ci-cycle -->
    **CI cycle of 4a2caa74a: 18 min**, 13:56 to 14:14 UTC, no native job.
    <BLANKLINE>
    | Workflow | Result | Ends at | Longest job |
    |---|---|---:|---|
    | x86 | completed | 18 min | x86-gcc, 18 min |
    """
    def utc(minutes):
        moment = cycle.start.timestamp() + 60 * minutes
        return datetime.fromtimestamp(moment, timezone.utc).strftime("%H:%M")

    natives = cycle.natives_text()
    lines = ["<!-- ci-cycle -->",
             "**CI cycle of %s: %.0f min**, %s to %s UTC, %s."
             % (cycle.sha[:9], cycle.span, utc(0), utc(cycle.span), natives),
             "",
             "| Workflow | Result | Ends at | Longest job |",
             "|---|---|---:|---|"]
    for workflow, status, end, job, minutes in cycle.workflows():
        name = label(workflow, cycle.unit)
        lines.append("| %s | %s | %.0f min | %s, %.0f min |"
                     % (name, status, end, job, minutes))
    return "\n".join(lines)


def duration(minutes):
    """A duration for the chart, in seconds under a minute.

    >>> duration(0.2), duration(17.6)
    ('12 s', '18 min')
    """
    if minutes < 1:
        return "%d s" % round(60 * minutes)
    return "%.0f min" % minutes


def style(overrides=None):
    """STYLE with some of its keys replaced.

    >>> style({"grid": "#000000"})["grid"]
    '#000000'
    >>> style({"grey": "#000000"})
    Traceback (most recent call last):
    ...
    ValueError: unknown style keys: grey
    """
    overrides = overrides or {}
    if not isinstance(overrides, dict):
        raise ValueError("a JSON object is expected")
    unknown = sorted(set(overrides) - set(STYLE))
    if unknown:
        raise ValueError("unknown style keys: " + ", ".join(unknown))
    return {**STYLE, **overrides}


def css(colors):
    """The style sheet of the chart. The SVG is published out of any page,
    so its colors are written in it.
    """
    return """
.grid {{ stroke: {grid}; stroke-width: 1; }}
.tick {{ font-size: 10px; fill: {muted}; }}
.natives {{ stroke: {text}; stroke-width: 1.2; stroke-dasharray: 4 3; }}
.natives-t {{ fill: {text}; }}
.lbl {{ font-size: 10px; fill: {text}; }}
.lbl.fail {{ fill: {failure}; font-weight: 600; }}
.dur {{ font-size: 9.5px; fill: {muted}; }}
.ttl {{ font-size: 13px; font-weight: 600; fill: {text}; }}
.wait {{ opacity: 0.25; }}
.needs {{ opacity: 0.5; stroke-width: 2; stroke-dasharray: 2 3; }}
.run.fail {{ stroke: {failure}; stroke-width: 1.5; }}
text {{ font-family: {font}; }}
""".format(**colors)


def chart(cycle, colors=STYLE):
    """A standalone SVG with one row per job, grouped by runner: a dotted
    line while the job waits for the jobs it needs, a pale bar while it waits
    for a runner, a full one while it runs. A job still queued has no full
    bar, and reads queued.

    >>> native = Job("x86", "native-x86", "generic-x86", 0, 0, 18, "success")
    >>> gated = Job("x86", "x86-gcc", "generic-x86", 18, 25, 50, "success")
    >>> c = Cycle("eve", "abc", None, {"x86": "completed"}, [native, gated],
    ...           opened={"x86": 0})
    >>> svg = chart(c)
    >>> svg.startswith("<svg") and "natives 18" in svg
    True
    >>> svg.count('class="needs"'), svg.count('class="wait"')
    (1, 1)
    >>> queued = Job("x86", "x86-clang", "generic-x86", 18, None, None, "")
    >>> c = Cycle("eve", "abc", None, {"x86": "in_progress"}, [native, queued],
    ...           now=30, opened={"x86": 0})
    >>> svg = chart(c)
    >>> svg.count('class="run'), svg.count('class="wait"')
    (1, 1)
    >>> "queued</text>" in svg
    True
    >>> gone = Job("x86", "x86-gcc", "generic-x86", 18, None, 22, "cancelled")
    >>> "cancelled</text>" in chart(Cycle("eve", "abc", None, {}, [gone]))
    True

    The axis opens on the last tick five minutes or more before the first job
    a runner took.

    >>> late = Job("x86", "native-x86", "generic-x86", 0, 64, 80, "success")
    >>> svg = chart(Cycle("eve", "abc", None, {"x86": "success"}, [late]))
    >>> 'class="tick">0</text>' in svg, 'class="tick">50</text>' in svg
    (False, True)
    """
    left, width, row, top = 340, 820, 13, 72
    jobs = list(cycle.jobs)

    def begin(job):
        return job.created if job.started is None else job.started

    first = {}
    for job in sorted(jobs, key=begin):
        first.setdefault(machine(job.labels), begin(job))
    order = sorted(first, key=lambda m: (first[m], m))
    runners = colors["runners"]
    color = {m: runners[k % len(runners)] for k, m in enumerate(order)}
    jobs.sort(key=lambda j: (order.index(machine(j.labels)), begin(j), j.name))
    running = [cycle.now for j in jobs if j.ended is None]
    span = max([cycle.span, 1] + running) * 1.02
    bottom = top + row * len(jobs) + 2
    # The axis opens a few minutes before the first job a runner took, so a
    # long wait for runners does not push every bar to the right.
    ran = [j.started for j in jobs if j.started is not None]
    origin = max(0.0, min(ran, default=0.0) - LEAD)
    step = 10 if span - origin <= 120 else 30
    origin -= origin % step

    def x(minutes):
        return left + width * (max(minutes, origin) - origin) / (span - origin)

    span_now = cycle.now if cycle.pending else cycle.span
    title = "%s %s, %.0f min%s" % (cycle.repo, cycle.sha[:9], span_now,
                                   " so far" if cycle.pending else "")
    out = ['<text x="%d" y="18" class="ttl">%s</text>'
           % (left, html.escape(title))]
    for k, name in enumerate(order):
        out.append('<rect x="%d" y="26" width="10" height="10" fill="%s"/>'
                   '<text x="%d" y="35" class="tick">%s</text>'
                   % (left + 120 * k, color[name], left + 120 * k + 14,
                      html.escape(name)))
    for m in range(int(origin), int(span) + 1, step):
        out.append('<line x1="%.1f" y1="%d" x2="%.1f" y2="%d" class="grid"/>'
                   '<text x="%.1f" y="%d" text-anchor="middle" class="tick">'
                   '%d</text>'
                   % (x(m), top - 4, x(m), bottom, x(m), top - 8, m))
    if cycle.natives is not None:
        n = cycle.natives
        out.append('<line x1="%.1f" y1="%d" x2="%.1f" y2="%d" '
                   'class="natives"/><text x="%.1f" y="%d" '
                   'text-anchor="middle" class="tick natives-t">natives %.0f'
                   '</text>'
                   % (x(n), top - 4, x(n), bottom, x(n), top - 22, n))
    for i, job in enumerate(jobs):
        y = top + i * row
        fill = color[machine(job.labels)]
        fail = " fail" if job.state == "failure" else ""
        ended = cycle.now if job.ended is None else job.ended
        out.append('<text x="%d" y="%.1f" text-anchor="end" class="lbl%s">%s'
                   '</text>' % (left - 8, y + row - 3, fail,
                                html.escape(job.name[:52])))
        # GitHub creates a job only once the jobs it needs have ended.
        opened = cycle.opened.get(job.workflow, 0)
        if job.created > opened + 0.3:
            out.append('<line x1="%.1f" y1="%.1f" x2="%.1f" y2="%.1f" '
                       'class="needs" stroke="%s" stroke-opacity="0.5"/>'
                       % (x(opened), y + row / 2, x(job.created), y + row / 2,
                          fill))
        if job.started is not None:
            start = job.started
        else:
            start = cycle.now if job.ended is None else job.ended
        if start > job.created + 0.3:
            out.append('<rect x="%.1f" y="%.1f" width="%.1f" height="%d" '
                       'class="wait" fill="%s" fill-opacity="0.25"/>'
                       % (x(job.created), y + 2, x(start) - x(job.created),
                          row - 4, fill))
        if job.started is None:
            out.append('<text x="%.1f" y="%.1f" class="dur">%s</text>'
                       % (x(start) + 4, y + row - 3,
                          "queued" if job.ended is None else job.state))
            continue
        bar = max(1.5, x(ended) - x(job.started))
        out.append('<rect x="%.1f" y="%.1f" width="%.1f" height="%d" '
                   'class="run%s" fill="%s"/>'
                   % (x(job.started), y + 2, bar, row - 4, fail, fill))
        out.append('<text x="%.1f" y="%.1f" class="dur">%s</text>'
                   % (x(ended) + 4, y + row - 3,
                      duration(ended - job.started)))
    w, h = left + width + 40, top + row * len(jobs) + 12
    return ('<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 %d %d" '
            'width="%d" height="%d" role="img" aria-label="%s">'
            '<style>%s</style><rect width="100%%" height="100%%" '
            'fill="%s"/>%s</svg>\n'
            % (w, h, w, h, html.escape(title), css(colors),
               colors["background"], "".join(out)))


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("repo", help="name under jfalcou, or owner/name")
    parser.add_argument("ref", help="pull request number or commit")
    parser.add_argument("--svg", help="write the chart of every job there")
    parser.add_argument("--markdown", help="write the comment there")
    parser.add_argument("--style", help="JSON object of colors for the chart")
    parser.add_argument("--workflow", default=UNIT,
                        help="text the name of a unit workflow contains")
    args = parser.parse_args()
    try:
        overrides = None
        if args.style:
            with open(args.style) as source:
                overrides = json.load(source)
        colors = style(overrides)
    except (OSError, ValueError) as error:
        parser.error("--style: %s" % error)

    repo = args.repo if "/" in args.repo else "jfalcou/" + args.repo
    cycle = fetch(repo, args.ref, args.workflow)
    print(summary(cycle))
    if cycle.cancelled:
        print("cancelled: no report for a cycle a newer push replaced")
        sys.exit(CANCELLED)
    if args.svg:
        with open(args.svg, "w") as out:
            out.write(chart(cycle, colors))
        print("chart:", args.svg)
    if args.markdown:
        with open(args.markdown, "w") as out:
            out.write(markdown(cycle) + "\n")
        print("markdown:", args.markdown)
    if cycle.pending:
        sys.exit(PENDING)


if __name__ == "__main__":
    main()
