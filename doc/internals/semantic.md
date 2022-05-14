Components Semantic {#glossary_semantic}
===================

**EVE** provides a lot of function that operates on similar premises. This page gather the general
behaviors **EVE** types and functions can exhibit.

# Property of EVE types

## Cardinal
For any [value type](@ref eve::value), the **cardinal** is the number of elements it contains.
This information is retrieved via the eve::cardinal type trait.

  - For any [scalar type](@ref eve::scalar_value) `T`, `eve::cardinal<T>::type` evaluates to @ref eve::scalar_cardinal.
  - For any [SIMD type](@ref eve::simd_value) `T`, `eve::cardinal<T>::type` evaluates to `eve::fixed<N>`, where `N` is the number of lanes of the underlying SIMD register.

Two types are said to be **cardinal compatible** if they have the same cardinal or at least one of them
is a [scalar type](@ref eve::scalar_value).

## Element type
For any [value type](@ref eve::value), its underlying **element type** is the type used to
represent its internal values. This information is retrieved via the eve::element_type type trait.

  - For any [scalar type](@ref eve::scalar_value) `T`, `eve::element_type<T>::type` evaluates to `T`.
  - For any [SIMD type](@ref eve::simd_value) `eve::wide<T,N>`, `eve::element_type<eve::wide<T,N>>::type` evaluates to `T`.
  - For any [logical type](@ref eve::logical_value) `eve::logical<T>`, `eve::element_type<eve::logical<T>>::type` evaluates to `eve::logical<T>`.

## ABI traits
[SIMD type](@ref eve::simd_value) internals depend on the actual architecture and instruction set
available. This information is retrieved via the eve::abi_of type trait.

  - When the type is based on a native SIMD register, the resulting types is architecture defined.
  - When the type is an aggregation of multiple SIMD registers, the resulting type is eve::aggregated_.
  - When the type uses an emulated SIMD register, the resulting type is eve::emulated_.
  - When the type elements are tuple-like, the resulting type is eve::bundle_.

# Operations Classification

## Generalized Element Access

**EVE** functions' semantics rely on a generic way to access an element of a [value](@ref eve::value),
be it [scalar](@ref eve::scalar_value) or [SIMD](@ref eve::simd_value).

To do so, we define a synthetic function `get(v,i)` that retrieve the `i`th element of a value `v`.

@code{.cpp}
template<eve::value V, std::integral I> auto get(V const& v,  I i)
{
  if constexpr( eve::simd_value<V>)   return v.get(i);
  else                                return v;
}
@endcode

@subsection glossary_elementwise Element-wise Operations
For any [values](@ref eve::value) `x1`, ..., `xn` of types `T1`, ..., `Tn` , a Callable Object `f`
returning a [value](@ref eve::value) of type `R` is said to be **Element-wise** if the expression
`R r = f(x1, ...,xn)` is semantically equivalent to:

  - if `R` models @ref eve::simd_value:
    @code{.cpp}
    R r = [](auto i, auto) { return f(get(x1,i),  ..., get(xn,i)); };
    @endcode

  - if `R` models @ref eve::scalar_value:
    @code{.cpp}
    R r = f(x1,  ..., xn);
    @endcode

@subsection glossary_reduction Reductions
For any [SIMD value](@ref eve::simd_value) `x` of type `T`, a Callable Object `f` returning a
[scalar value](@ref eve::scalar_value) of type `R` is said to be a **Reduction** if the expression
`R r = f(x)` is semantically equivalent to:

@code{.cpp}
R r = f(get(x,0),  ..., get(x,cardinal_v<T>-1));
@endcode

Most reduction operations are not defined on [scalar values](@ref eve::scalar_value) unless their
definition is required by the internal implementation.

# Function Semantic

@subsection glossary_arithmetic Arithmetic Functions

For any [values](@ref eve::value) `x1`, ..., `xn` of types `T1`, ..., `Tn` so that the expression
`using C = eve::common_compatible_t<T1,...,Tn>` is valid, a Callable Object `f` is said to be
an **Arithmetic Function** if the expression `C r = f(x1, ...,xn)` is semantically equivalent to:

  - if `C` models eve::simd_value:
    @code{.cpp}
    C r = [](auto i, auto) { return f(get(C(x1),i),  ..., get(C(xn),i)); };
    @endcode

  - if `C` models eve::scalar_value:
    @code{.cpp}
    C r = f(C(x1),  ..., C(xn));
    @endcode

In a less formal way, **EVE** @ref glossary_arithmetic generalizes the notion of native C++
arithmetic operations. By construction, a large majority of @ref glossary_arithmetic are _de facto_
@ref glossary_elementwise.

@subsection glossary_bitwise Bitwise Functions

For any [values](@ref eve::value) `x1`, ..., `xn` of types `T1`, ..., `Tn`so that the expression
`eve::bit_compatible_values<T1,...,Tn>` evaluates to `true`, a Callable Object `f` is said to be
a **Bitwise Function** if the expression `T1 r = f(x1, ..., xn)` is semantically equivalent to:

  - if `T1` models eve::simd_value:
    @code{.cpp}
    T1 r = [](auto i, auto) { return f(get(x1,i), ..., get(eve::bit_cast(xn, eve::as(x1)),i); };
    @endcode

  - if `T1` models eve::scalar_value:
    @code{.cpp}
    T1 r = f(x1,...eve::bit_cast(xn,eve::as(x1)));
    @endcode

In a less formal way, **EVE** @ref glossary_bitwise can be applied to any pair of types, the first
acting as the value type and the second as a type-less source of bits. By construction, a large
majority of @ref glossary_bitwise are _de facto_ @ref glossary_elementwise.

@subsection glossary_logical Logical Functions

**EVE** @ref glossary_logical are @ref glossary_arithmetic that can only be applied to
[logical values](@ref eve::logical_value) `L1`,... `Ln`  as long as they are all
**cardinal-compatible**. By construction, a large majority of @ref glossary_bitwise are
_de facto_ @ref glossary_elementwise.

@subsection glossary_constant Constant Functions

## General Principles
**EVE** constant generator are @callable that takes a single argument of type eve::as. This argument
provides the information about the type used to generate the constant. E.g:

@code{.cpp}
auto z  = eve::zero(as<int>());         //  equivalent to auto z  = static_cast<int>(0);
auto vp = eve::half(as<wide<float>>()); //  equivalent to auto vp = wide<float>(0.5);
@endcode

## Precision handling
Some constants are exactly representable in IEEE754 types. However, some mathematical constants can
be under-represented on a given type while simultaneously be over-represented on other. For example,
\f$\pi\f$ in `float` is greater than its mathematical value. Meanwhile \f$\pi\f$ in `double` is less
than its mathematical value.

The constant implementation is so that, for any constant generator `g`:

  - `g(eve::as<T>())`returns the nearest representable value of the mathematical constant
  - `eve::downward(g)(eve::as<T>())`returns a value no lesser than 0.5 ULP from the mathematical constant
  - `eve::upward(g)(eve::as<T>())`returns a value no greater than 0.5 ULP from the mathematical constant

For all constants, `eve::downward(g)(eve::as<T>()) <= g(eve::as<T>()) <= eve::upward(g)(eve::as<T>())`
is always verified.

We encourage user facing issue with reproducible computation to use those decorators to make all
constant generation stable across types.
