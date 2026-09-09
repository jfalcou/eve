# Contributing to EVE

Thank you for your interest in EVE. Bug reports, documentation fixes, a missing overload on one
architecture and whole new functions are all welcome.

By opening a pull request you agree to license your contribution under the
[Boost Software License 1.0](LICENSE.md), like the rest of the project, and confirm you have the
right to do so. Everyone taking part is expected to follow the
[Code of Conduct](CODE_OF_CONDUCT.md).

Bugs and feature requests go through the [issue templates](.github/ISSUE_TEMPLATE); the rest of
this page is about patches.

If anything below is unclear, or you would rather talk an idea through before writing it, come
and ask on [our Discord](https://discord.gg/8A4Q4HkhcW). No question is too small, and a five
minute conversation there often saves a rewrite.

## Generative AI

We will not ask whether a patch was written with a language model, and we would be badly placed
to: parts of this project's own infrastructure were. **What gets reviewed is the patch, not how
the characters arrived.**

That cuts both ways. A pull request nobody has read is not a contribution, it is a review
request pointed at us, and reading generated code costs more than writing the thing by hand.
Concretely:

- **answer the issue, not its checklist.** A patch that satisfies every word of a report while
  missing what it was asked for is a rewrite waiting to happen, and it is the failure mode a
  model falls into first. In practice that means testing past the machine on your desk: the CI
  image cross-builds and runs every architecture EVE supports. Covering only some of them is
  fine as long as you say which, and asking for help with the rest is fine too — a half-finished
  patch checked against the emulated backend alone, the one configuration that exercises no SIMD
  at all, and left for someone else to finish is not
- **send only what you have read and can explain.** "That is what the model produced" is not an
  answer to a review comment, and a branch its author cannot defend is closed rather than
  iterated on
- **a feature arrives with tests that fail without it.** A model will happily produce tests that
  pass against any implementation, wrong ones included; those are worth less than no tests at
  all, because they look like coverage
- **build it and run the suite before opening the pull request**, as described further down. An
  unbuilt patch is not a draft, it is noise
- **opening pull requests in bulk is spam**, and it gets you blocked from the repository without
  discussion

None of this is about the tool. The same pull request typed by hand is closed just as fast.

## Here for a course or a hackathon?

Some of you arrive here because a course, a hackathon or a seasonal event asks for a number of
merged pull requests. **You are welcome.** A student who wants to see what a SIMD library looks like
from the inside is exactly the reader this page was written for, and nobody is going to hold a
deadline against you.

What does not work is the shape those events push you into. A quota counts pull requests, so it
rewards volume — and volume is the one thing a small maintainer team cannot absorb. A batch of
whitespace fixes, README typos or reformatted headers costs more attention than it saves anyone,
and it buries the reports we actually need to read. Those get closed, and **it is the format's
fault rather than yours**.

So say so. In the issue, or on [Discord](https://discord.gg/8A4Q4HkhcW) — "I have two weeks and
I would like to land something real" is a message we answer gladly, and we will point you at
something that fits the time you have. The
[good first issue](https://github.com/jfalcou/eve/labels/good%20first%20issue) label lists work
that is genuinely open, sized for a newcomer and worth having. One of those, with questions
asked along the way, will teach you more and stands a far better chance of being merged than ten
cosmetic patches.

The line between the two is intent, and it is usually plain to see: someone who asks questions
gets answers, an account opening the same patch across thirty repositories gets blocked.

## Building and running the tests

```bash
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/gcc.x86.cmake
cmake --build build --target unit.core.average.exe && ./build/unit/unit.core.average.exe
```

**One target per test file** — `test/unit/module/core/average.cpp` builds as
`unit.core.average.exe` — and that is the loop you want while working on a function.
`unit.exe` builds the entire suite and wants a machine for it.

The rest is already written down, so it is not repeated here:
[Setup](https://jfalcou.github.io/eve/setup.html) lists the CMake options,
[Building for Testing](https://jfalcou.github.io/eve/dev_cmake.html) gives the toolchain file
and command line of every configuration the CI runs plus the full target list, and
[Development Environment](https://jfalcou.github.io/eve/dev_environment.html) covers the two
Docker images that carry the architectures you do not own.

## Adding a function

A callable touches seven places. CMake globs `test/doc/<module>/` and
`test/unit/module/<module>/`, so dropping a `.cpp` there is enough — no CMake edit.

| | |
|---|---|
| `include/eve/module/<m>/regular/<name>.hpp` | the callable object and its documentation |
| `include/eve/module/<m>/regular/impl/<name>.hpp` | the generic implementation |
| `include/eve/module/<m>/regular/impl/simd/<arch>/<name>.hpp` | optional, per architecture |
| `include/eve/module/<m>/regular/core.hpp` | the include |
| `include/eve/module/<m>.hpp` | the group listing, where the module keeps one |
| `test/doc/<m>/<name>.cpp` | the example `@godbolt` points at |
| `test/unit/module/<m>/<name>.cpp` | the unit test |

### The callable

**One callable per file, named after the file.** The object declares the interface and nothing
else; the body is always `EVE_DISPATCH_CALL`.

```cpp
namespace eve
{
  template<typename Options>
  struct average_t : tuple_callable<average_t, Options, raw_option, kahan_option>
  {
    template<value... Ts>
    requires(sizeof...(Ts) != 0 && eve::same_lanes_or_scalar<Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<Ts...> operator()(Ts... ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    EVE_CALLABLE_OBJECT(average_t, average_);
  };

  // …documentation block…

  inline constexpr auto average = functor<average_t>;
}
```

**Picking the base class is the real decision**: `elementwise_callable`,
`strict_elementwise_callable`, `tuple_callable`, `constant_callable`, `bit_callable` or plain
`callable`. Inheriting the right one gives masking, type promotion and tuple unrolling for
free — writing them by hand means you picked the wrong base.

Implementations go in `namespace eve::_`, in free functions named `<name>_`, selected by
architecture tag through `EVE_REQUIRES`. Fall back to the generic level with
`f.behavior(cpu_{}, opts, …)`, never by calling another function directly.

### Options

**Never a new namespace, never a suffixed name.** Options are flags used through `operator[]`:

```cpp
average[eve::kahan](a, b)        // semantic option
average[eve::ignore_last(2)](a)  // masking, composes with the above
```

Read them with `O::contains(kahan)`. Once you have handled an option, strip it with
`o.drop(kahan)` before forwarding the rest of the pack — dropping it is what keeps the call
from landing straight back on you.

## Documentation

The block sits between the `<name>_t` type and the `inline constexpr auto`, and always runs
through the same sections in the same order:

- `@addtogroup <group>` and `@{`, then `@var <name>` and a one-line `@brief` naming the base
  class the callable inherits from
- `@groupheader{Header file}` — the single header a user includes, never the internal path
- `@groupheader{Callable Signatures}` — every overload, in a `namespace eve` code block,
  grouped under `// Regular overloads`, `// Lanes masking` and `// Semantic options`, each
  line closed by a `// n` comment
- **Parameters** — one bullet per parameter name, each linking its concept with `@ref`
- **Return value** — a numbered list answering the `// n` of the signatures, one entry per
  number, options included
- `@groupheader{External references}` — the reference the definition comes from
- `@groupheader{Example}` and `@godbolt{doc/<m>/<name>.cpp}`

```cpp
//! @addtogroup core_arithmetic
//! @{
//!   @var average
//!   @brief `tuple_callable` computing the arithmetic mean of its arguments.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto average(eve::floating_value auto x, eve::floating_value auto... xs) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto average[conditional_expr auto c](/* any of the above overloads */)   noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto average[kahan](/* any of the above overloads */)                     noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...`: [floating values](@ref eve::floating_value) to average.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!
//!   **Return value**
//!
//!     1. The arithmetic mean of the arguments. No overflow occurs.
//!     2. [The operation is performed conditionnaly](@ref conditional)
//!     3. Compensated algorithm for better precision.
//!
//!   @groupheader{External references}
//!   *  [Wikipedia Mean](https://en.wikipedia.org/wiki/Mean)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/core/average.cpp}
//! @}
```

The example that `@godbolt` names must exist and must compile — it is built by the CI like any
other file. It demonstrates **one** callable, starts with `// revision 0`, and aligns its output
so the reader can scan it.

Two rules worth stating because they are easy to break silently:

- an unclosed `` ` `` or `\f$` turns the rest of the block into code, and the alias expansion
  along with it, without any error at the point where you wrote it
- `@var` documents a variable, `@concept` a concept, `@typedef` an alias, `@fn` a function.
  Using the wrong one leaves the entity undocumented and Doxygen says so quietly

## Tests

One test file per function, three cases in this order: return types, nominal behaviour,
then the decorated and masked forms.

```cpp
TTS_CASE_TPL("Check return types of average", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS(eve::average(T(), T()), T);
};

TTS_CASE_WITH("Check behavior of average", eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000.0, 1000.0), tts::randoms(-1000.0, 1000.0)))
<typename T>(T const& a0, T const& a1)
{
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::average(a0, a1),
                tts::map([](auto e, auto f) -> v_t { return (e + f) / 2; }, a0, a1), 2);
};
```

The reference is a scalar lambda passed to `tts::map`, and the tolerance is a number of ULP you
chose. **Never `TTS_EQUAL` on a floating result.**

- compute the reference from the definition, not from the implementation — a test that repeats
  the source cannot fail
- make sure the reference is more accurate than what it checks, or the test measures its own
  error
- **no `long double`**: it collapses to `double` on MSVC and several ARM ABIs. Hardcode the value
  or compare relatively
- generators must fit the type: `tts::randoms(0, 1000)` overflows `std::int8_t`. Prefer
  `tts::randoms(eve::valmin, eve::valmax)`

## Other kinds of change

Most contributions are not a new function. What is expected instead:

**A bug fix.** The fix and its test in the same commit. The new case goes at the end of the
test file that already covers the entity — `test/unit/module/core/popcount.cpp` for a wrong
`popcount` — next to the cases that did not catch it. Write the case first and watch it fail:
a regression test that was never red proves nothing.

**An architecture-specific implementation of an existing callable.** A new
`impl/simd/<arch>/<name>.hpp`, included from the public header behind the matching
`EVE_INCLUDE_<ARCH>_HEADER` guard. Constrain it with `EVE_REQUIRES(<tag>)` and a `requires`
clause naming the ABI *and* the options you actually implement, then hand everything else back
with `behavior(cpu_{}, opts, …)`. An overload that quietly swallows an option it does not
honour is the failure mode here, and it will not show up on your machine. The documentation
block does not change: it says what the callable computes, not where it runs.

**A new option on an existing callable.** Three edits travel together — the flag in the
callable's option list, a signature line plus its numbered *Return value* entry in the
documentation, and a case in the test file. An option that no callable consumes is dead code
that reads like a feature.

**Documentation alone.** Still code: an example under `test/doc/` is compiled by the CI like
any other file, and the `doxygen` target has to stay silent.

**Infrastructure — CMake, the CI workflows, the test harness.** There is no unit test to write,
so the pull request body carries the weight. Say what changes for someone building the project,
and whether an existing build directory keeps working.

**An issue rather than a patch.** A wrong result is only actionable with the element type, the
instruction set it was compiled for, and the input values. A Godbolt link that reproduces it is
worth more than all three.

## Before you push

Build and run the tests for what you touched, then the documentation:

```bash
ctest --test-dir build --output-on-failure -R "average"
cmake --build build --target doxygen
```

Use the `doxygen` target rather than calling `doxygen doc/Doxyfile` by hand: the target sets
the output directory the Doxyfile expects and fetches the tagfiles the cross-references
resolve against. **It should stay silent** — a warning here is a broken link on the website.

If your change is architecture-dependent — anything under an `impl/simd/` directory, anything
touching an ABI or a width — run the test on the targets you cannot boot, from inside the
CI image:

```bash
docker run -i -t -v${PWD}:${PWD} ghcr.io/jfalcou/compilers:v10
```

From there, configure a second build directory with the toolchain file of the architecture you
are after and build the same target. Each toolchain names its own emulator — `qemu-aarch64`, a
`run_*.sh` wrapper, Intel SDE — so the binary you just cross-compiled runs like a native one.

## Commits and pull requests

**Commit titles are one short imperative line.** No body unless the change is genuinely not
obvious, and then a few sentences of prose rather than a bulleted report.

Branches are `issue-<n>/<short-description>` for a tracked issue, or a short explicit name
otherwise. Titles for a tracked fix read `Fix #<n> - short description`.

Pull request descriptions are plain prose, as long as the "why" requires and no longer. No
section headers, no test plan, no restating the issue number that is already in the title.
