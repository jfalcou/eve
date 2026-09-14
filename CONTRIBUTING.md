# Contributing to EVE

Thank you for your interest in EVE. Bug reports, documentation fixes, a missing overload on one architecture and whole new functions are all welcome.

By opening a pull request you agree to license your contribution under the [Boost Software License 1.0](LICENSE.md), like the rest of the project, and confirm you have the right to do so. Everyone taking part is expected to follow the [Code of Conduct](CODE_OF_CONDUCT.md).

Bugs and feature requests go through the [issue templates](.github/ISSUE_TEMPLATE). This document is about how to contribute code, tests and documentation. If anything below is unclear, or you would rather talk an idea through before writing it, come and ask on [our Discord](https://discord.gg/8A4Q4HkhcW). No question is too small, and a five minute conversation there often saves a rewrite.

## Generative AI

We will not ask whether a patch was written with a language model, and we would be badly placed to: parts of this project's own infrastructure were.

**What gets reviewed is the patch, not how the code was written.**

The reciprocal is also true. A pull request nobody has read is a review  request pointed at us rather than a contribution, and reading generated code costs more than writing  the thing by hand. Concretely:

- **Answer the issue, not its checklist.** A patch that satisfies every word of a report while missing what it was asked for is useless. Here that means testing past the machine on your desk:  the CI image cross-builds and runs every architecture EVE supports. Covering only some of them is fine as long as you say which, and asking for help with the rest is fine too. What does not work is a half-finished patch checked against the emulated backend alone, the one configuration that exercises no SIMD at all, and left for someone else to finish.
- **Send only what you have read and can explain.** "That is what the model produced" is not an answer to a review comment, and a branch its author cannot defend is closed rather than iterated on.
- **A feature arrives with tests that fail without it.** A model will happily produce tests that pass against any implementation, wrong ones included; those are worth less than no tests at all, because they look like coverage.
- **Build it and run the suite before opening the pull request**, as described further down. An unbuilt patch is noise rather than a draft
- **Opening pull requests in bulk is spam**, and it gets you blocked from the repository without discussion

None of this is about the tool. The same pull request typed by hand is closed just as fast.

## Courses and hackathons

Some of you arrive here because a course, a hackathon or a seasonal event asks for a number of merged pull requests. **You are welcome.** A student who wants to see what a SIMD library looks like from the inside is exactly who we wrote this for, and nobody is going to hold a deadline against you.

What does not work is the shape those events push you into. A quota counts pull requests, so it rewards volume, and volume is the one thing a small maintainer team cannot absorb. A batch of whitespace fixes, README typos or reformatted headers costs more attention than it saves anyone, and it buries the reports we actually need to read. Those get closed, and **it is the format's fault rather than yours**.

So say so. In the issue, or on [Discord](https://discord.gg/8A4Q4HkhcW): "I have two weeks and I would like to land something real" is a message we answer gladly, and we will point you at something that fits the time you have. The [good first issue](https://github.com/jfalcou/eve/labels/good%20first%20issue) label lists work that is genuinely open, sized for a newcomer and worth having. One of those, with questions asked along the way, will teach you more and stands a far better chance of being merged than ten cosmetic patches.

The line between the two is intent, and it is usually plain to see: someone who asks questions gets answers, an account opening the same patch across thirty repositories gets blocked.

## Building and running the tests

```bash
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/gcc.x86.cmake
cmake --build build --target unit.core.average.exe && ./build/unit/unit.core.average.exe
```

One target per test file, `test/unit/module/core/average.cpp` building as `unit.core.average.exe`,
and that is the loop you want while working on a function. `unit.exe` builds the entire suite and
wants a machine for it. CMake globs `test/doc/<module>/` and `test/unit/module/<module>/`, so a new
`.cpp` there needs no CMake edit.

The rest is already written down:
 + [Setup](https://jfalcou.github.io/eve/setup.html) lists the CMake options,
 + [Building for Testing](https://jfalcou.github.io/eve/dev_cmake.html) gives the toolchain file and command line of every configuration the CI runs plus the full target list, and
 + [Development Environment](https://jfalcou.github.io/eve/dev_environment.html) covers the two Docker images that carry the architectures you do not own.


## Other kinds of change

Most contributions are not a new function. A patch can be :

  + **A bug fix.** The fix and its test in the same commit. The new case goes at the end of the test file that already covers the entity, `test/unit/module/core/popcount.cpp` for a wrong `popcount` for example, next to the cases that did not catch it. Write the case first and watch it fail: a regression test that was never red proves nothing.

  + **An architecture-specific implementation of an existing callable.** A new `impl/simd/<arch>/<name>.hpp`, included from the public header behind the matching `EVE_INCLUDE_<ARCH>_HEADER` guard. Constrain it with `EVE_REQUIRES(<tag>)` and a `requires` clause naming the ABI *and* the options you actually implement, then hand everything else back with `behavior(cpu_{}, opts, …)`. An overload that quietly swallows an option it does not honour is the failure mode here, and it will not show up on your machine. The documentation block does not change: it says what the callable computes, not where it runs.

  + **A new option on an existing callable.** Three edits travel together: the flag in the callable's option list, a signature line plus its numbered *Return value* entry in the documentation, and a case in the test file. An option that no callable consumes is dead code that reads like a feature.

  + **Documentation alone.** Still code: an example under `test/doc/` is compiled by the CI like any other file, and the `doxygen` target has to stay silent.

  + **Infrastructure, CMake, the CI workflows, the test harness.** There is no unit test to write, so the pull request body carries the weight. Say what changes for someone building the project, and whether an existing build directory keeps working. **Those patches are very sensitive** so discussion on [Discord](https://discord.gg/8A4Q4HkhcW) is strongly recommended before you write one.

  + **An issue rather than a patch.** A wrong result is only actionable with the element type, the instruction set it was compiled for, and the input values. A Godbolt link that reproduces it is worth more than all three.

  + **Work on an open issue.** The [open issues](https://github.com/jfalcou/eve/issues) are all fair game, and help on any of them is welcome. Say on the issue that you are taking it, so that two people do not write the same patch.

  + **Anything else.** Ideas outside this list are welcome too. Bring one up on [Discord](https://discord.gg/8A4Q4HkhcW) before you write it: a design that has been talked through lands, and one that has not tends to need rewriting once it arrives.

## Before you push
A few things to consider:
  + Build and run the tests for what you touched, then the documentation:
  + Everything committed here is in English, comments and doxygen included.
  + **Commit titles are one short imperative line.** No body unless the change is genuinely not obvious, and then a few sentences of prose rather than a bulleted report.
  + Branches are `issue-<n>/<short-description>` for a tracked issue, or a short explicit name otherwise. Titles for a tracked fix read `Fix #<n> - short description`.
  + Pull request descriptions are plain prose, as long as the "why" requires and no longer.
