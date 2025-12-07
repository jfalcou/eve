# LLM README

A starting point for LLMs to understand the codebase.

## Code authoring points

* LESS IS MORE - the less code you produce the better.
* Do not add comments unless specifically requested by the user
* Use clang-format. Some files are not already formatted - take care
  to undo all the unrelated / accidental changes.
* We aim for 100% of the logic to be well but not excessively tested.
* Start by adding a failing test, then make it pass.
* While working add logs to the code you are writing to make sure
  it's executed the way you expected.
* Intentionally introduce small bugs in the code you wrote to see that the problem is
  covered. If it's not, cover it with a test then undo the bug.

## How to build and test

Eve uses docker to build and test.
Read unit.yml to get an idea on how we run everything in CI.
Find the correct docker img in there.
Each build configuration should be in its own build* directory
The build directories are:
  build_compiler_variation

Examples:
* clang build for avx2 should be in build_clang_avx2
* gcc build for aarch64 should be build_gcc_aarch64
* gcc build for sve256 should be build_gcc_sve256

### The naming convention for targets:

We only have test targets, the library itself is header only.
Each test file corresponds to one .exe target.
.exe is just short for executable, doesn't have anything to do with Windows.

Target naming works like this.

For doc test targets:
* test/doc/algo/all_of.cpp - doc.algo.all_of.exe

For unit tests (the word module is skipped):
* test/unit/module/core/abs.cpp - unit.core.abs.exe

Test targets are auto-generated via CMake glob, never added as
individual targets

For a faster compilation of tests add -DEVE_NO_FORCEINLINE macro to the compilation.

### How to run tests

Which test configurations can run on the machine depends on the
specific machine in question.

The docker ships with tools to run everything on x86.
Get the correct information on how to run things from unit.yml -
which will lead you to the toolchain files.

NOTE: if the native CPU doesn't support avx512, we also have the SDE emulator
to help with that in the docker image.

### Putting it together

Ask the user if they want to try running some unit tests.

If yes, try putting everything together:
* create build directories for clang_avx2 and gcc_aarch64, if they are not there
* start a docker shell
* configure these directories
* Run doc.algo.all_of.exe and unit.core.abs.exe for both avx2 and aarch64.
* Give the user summary with the command to build and run (build && run)
  for the doc.algo.all_of.exe and unit.core.abs.exe for both avx2 and aarch64.
