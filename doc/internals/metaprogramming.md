Metaprogramming Guidelines {#metaprog_rationale}
==========================

@section rationale-meta-intro Metaprogramming tool choice 

There are multiple ways to do metaprogramming in C++20. The choice made by **EVE** is to pick the
tool based on **what the result is** and not on what is the most familiar to write. Results can be 
one of the following :

  - an existing type, selected by pattern
  - a value, selected by pattern
  - a yes/no answer used as a constraint
  - a value that requires real computation
  - a brand new type

Each case has a single preferred tool, listed below in the order in which they should be considered.

@section rationale-meta-extern Extern variables for type matching

When the question is *"given these parameters, which already existing type do I get?"*, **EVE**
uses a declared-but-never-defined `extern` variable template, specialized for each case, and
reads its type with `decltype` through an alias:

```cpp
template<typename T, std::size_t Size> extern no_register<void> sve_register;

template<std::size_t S>                 extern sve_f32_t sve_register<float, S>;
template<std::signed_integral T>        extern sve_s32_t sve_register<T, 4>;

template<typename T, std::size_t S>
using sve_register_t = decltype(sve_register<T, S>);
```
@note extern variables can't be fully specialized.

This is preferred over a `struct` with a nested `::type` or over a `constexpr`/`conditional_t`
selection because:

  - only the declaration of a variable is instantiated: 
    - no class body
    - no member lookup 
    - no definition 
    - no code generation. 

  This makes it cheaper to compile on a path hit by nearly every `eve::wide`.

  - each architecture adds its own specializations from its own header. There is no central
    switch to edit.

  - overlapping specializations are diagnosed by the compiler and ordering does not matter.

  - the variable is never defined, so any accidental runtime use is a link error.

  - if the result type might be void, wrap it in `std::type_identity` 

Rules:

  - The variable is only used in unevaluated contexts (`decltype`, `sizeof`, `requires`...).
  - Always hide the `decltype` behind an alias. Call sites should read as plain type lookups.
  - The primary template is a sentinel (like `no_register<void>`), not a `static_assert`.
    "No answer" must stay detectable so it can be used by concepts and SFINAE.
  - The variable **does not introduce a new type**. If the result must be built, use a type
    (see @ref rationale-meta-type).

@section rationale-meta-inline Inline variables for trait matching

When the question is *"given these parameters, which value do I get?"* and the answer comes from
matching or simple computations, **EVE** uses an `inline constexpr` variable template,
specialized in the same way as the extern ones:

```cpp
template<typename T> inline constexpr bool is_wide_v = false;
template<typename T, typename N> inline constexpr bool is_wide_v<eve::wide<T, N>> = true;
```

This is preferred over a `struct` deriving from `std::bool_constant` or `std::integral_constant`
because it removes a class instantiation and the `::value` indirection. It also reads as what it
is: a fact about a type.

It is also preferred over a constexpr function when the computation are trivial as these are
parsed early by the compiler.

Rules:

  - Use `inline constexpr`, never a bare `constexpr`, so the variable has no per-TU copy.
  - Name them with the `_v` suffix, and keep them as the *implementation* of a trait. Users
    should consume the concept (see @ref rationale-meta-concept) when a yes/no answer is needed.
  - If the value is the result of a real algorithm (loop, arithmetic, table), it is not
    matching: use a function (see @ref rationale-meta-consteval).

@section rationale-meta-concept Concepts to expose constraints

Concepts are how **EVE** turns a trait into a requirement on an interface. They are used to
wrap inline variables, expressions, or other concepts:

```cpp
template<typename T> concept simd_value = is_wide_v<T> || is_logical_wide_v<T>;
```

They are preferred over `std::enable_if` or `requires` spelled in place because:

  - they give readable names to requirements and much clearer diagnostics.
  - they take part in overload resolution via subsumption, which makes `requires`-based
    specialization of both functions and variable templates possible.

Rules:

  - A concept is a **constraint**, not a getter: do not use it to retrieve a type or a value.
  - Define a concept as a conjunction/disjunction of other concepts when it must be *more
    specialized* than them. A concept that simply wraps a boolean variable
    (`concept c = trait_v<T>`) is a single atomic constraint and does not subsume anything.
  - Use plain wrapped traits freely when the concept is only a filter (`requires`,
    `static_assert`, template parameter constraint) and no ordering is needed.
  - Constrain specializations of extern/inline variables with concepts to classify by family
    (`std::signed_integral`, `std::floating_point`) instead of listing types.

@section rationale-meta-consteval Consteval functions for pure compile-time computation

When the result is a **value that needs real computation** and must never exist at runtime,
**EVE** uses a `consteval` function:

```cpp
template<typename T> consteval std::size_t best_width()
{
  // loops, branches, arithmetic on numbers...
}
```

This is the right choice when:

  - the logic is too involved to be written as a recursive or matching template.
  - the result only has a meaning at compile time (sizes, widths, masks, table content).
  - we want the *guarantee* that the computation is evaluated by the compiler and never
    generates code. A call that cannot be evaluated is a compile-time error.

Rules:

  - Functions cannot take types as parameters: pass a tag (`as<T>{}`) when the computation
    depends on a type.
  - Do not use a `consteval` function to *return a type* through `decltype(f())`. Use an extern
    variable (see @ref rationale-meta-extern).
  - A `consteval` function cannot be taken as a runtime function object or address. If the
    function may also be called with runtime inputs, it is a `constexpr` function.

@section rationale-meta-constexpr Constexpr functions when usable outside of traits

When the computation is useful **both at compile time and at runtime** (for example a helper
used to build a constant *and* to process runtime data), **EVE** uses a `constexpr` function:

```cpp
constexpr bool is_power_of_2(std::size_t n) { return n && !(n & (n - 1)); }
```

It is the difference with the previous section that matters: a `constexpr` function is a
regular function that *may* be evaluated at compile time, a `consteval` function *must* be.

Rules:

  - Prefer `consteval` for anything that is a trait or a metaprogramming helper only.
  - Use `constexpr` for utilities that are part of the general API and that are legitimately
    called with runtime values.
  - Do not use `constexpr` as a way to dodge the other rules: a pattern-matching result is
    an extern or inline variable, not a function.

@section rationale-meta-type Types when a type is the deliverable

When the result **is** a type, **EVE** defines a type. This is the case when:

  - several results must be provided together (`type`, `value`, helpers, names...).
  - the result carries members, state, or needs to be inherited from.
  - the result is a tag used for dispatch (`as<T>`, `ignore_none_`, decorators...).
  - the result requires ADL or needs its own nested names.
  - the result is an extension point for **external** use

```cpp
template<typename T> struct element_traits
{
  using type = T;
  static constexpr std::size_t size = sizeof(T);
  static consteval bool is_native() { /* ... */ }
};
```

Types are the heaviest tool: they must be instantiated, completed and looked up. They are
used when what they provide cannot be expressed more cheaply, not as a default.

@section rationale-meta-summary Summary

| The result is...                              | **EVE** uses...                          |
|-----------------------------------------------|------------------------------------------|
| an existing type, selected by pattern         | `extern` variable + `decltype` alias     |
| a value, selected by pattern                  | `inline constexpr` variable              |
| a yes/no requirement on an interface          | `concept`                                |
| a value needing computation, compile-time only| `consteval` function                     |
| a value needing computation, also at runtime  | `constexpr` function                     |

