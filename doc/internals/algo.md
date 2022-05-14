SIMD Algorithms  {#algo_rationale}
===============

# General Principles

SIMD algorithms are complex to design, implement and tests as a lot of care has to be put into
details like correct tail handling, alignment handling or unrolling.

**EVE**'s algorithms and views module is designed to simplify such design while:

  * Providing at least 90% of maximum possible performance easily achievable.
  * Making simple tasks reasonably simple.
  * Supporting a tiered structure to enable reuse
  * Providing customization options for handling extreme optimizations and corner cases.

All those features are usable through generic interfaces to allow for reuse of similar loops
structure at the cost of some idiosyncrasies.

For a in-depth discussion about those issues, you can take a look at the Algorithms section
of our [CppCon talk](https://www.youtube.com/embed/WZGNCPBMInI?t=1412).

# Basic Components

## Reusable loops

Many algorithms require some form of `while(f != l)` loop. However, with SIMD, even this simple
operation is non trivial. **EVE** algorithm building-blocks provide implementation for the most
frequent loop structure. Those loops can then customized and reused without having to care about
the actual range type used. For example, eve::mismatch is implemented as a customized call to eve::find.

## Ranges or Iterators

### General concepts

Iterators are more fundamental than ranges. However, ranges can have some extra information like,
for example, that instead of `begin()` it has `aligned_begin()` and the algorithm can use that.
So the interfaces are `range` based. We don't generally accept `iterator` in interfaces just because
it increases the maintenance. The  eve::algo::as_range can be used to turn iterators pair into
a **EVE** compatible range.

One case where it can be very awkward to use ranges instead of iterators is in multi-range algorithms
, like `transform_to`. In this case, unless we have some reason no to, we allow for passing anything
that zips to `range`, i.e. `range`, `iterator` or `iterator`,`range`. Exceptions are documented and
have `static_assert`s that will tell you it's not supported*.

### Relaxed concepts

Many things that we want to accept in the interfaces as `range` and/or `iterator` are not ideal for
writing code against. We also need to strip things like `vector::iterator` to pointers.
What also we want is to associate a `cardinal` with `iterator`.

This is why we have two layers: `relaxed_range`/`relaxed_iterator` and `iterator`.
There are a few things that `relaxed_*` should be able to do but the main one is `preprocess_range(traits, f, l)`
which returns enhanced `traits` and `iterator` pair.

# Customization

## Algorithms traits
**EVE** allows to customize algorithms with traits. Traits are passed via `[]` and can ve combined.

The more common ones are:

  * `no_aliging` - stop aligning data accesses
  * `unroll<N>` - unroll N times (1 for no unrolling).
  * `force_cardinal<N>` - force how many elements in per step to process, needed for writing code
    dealing with intrinsics.

The values used by default are documented by algorithm.
