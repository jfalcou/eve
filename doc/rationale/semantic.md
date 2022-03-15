Semantic of EVE functions {#glossary_semantic}
=========================

@tableofcontents

**EVE** provides a lot of function that operates on similar premises. This page gather the general
behaviors **EVE** functions can exhibit.

@section glossary_op_classes Operations Classification

@subsection glossary_access Generalized Element Access

**EVE** functions' semantics rely on a generic way to access an element of a [value](@ref eve::value),
be it [scalar](@ref eve::scalar_value) or [SIMD](@ref eve::simd_value).

To do so, we define a synthetic function `at(v,i)` that retrieve the `i`th element of a value `v`.

@code{.cpp}
template<eve::value V, std::integral I> auto at(V const& v,  I i)
{
  if constexpr( eve::simd_value<V>)   return v.get(i);
  else                                return v;
}
@endcode

---

@subsection glossary_elementwise Elementwise Operations

Elementwise operations in **EVE** describe functions that operates in a regular pattern over each
and every element of its input and generates a return value with the same cardinal as its inputs.

For any [values](@ref eve::value) `x1`, ..., `xn` of types `T1`, ..., `Tn`, a Callable Object `f`
returning a [value](@ref eve::value) of type `R` is said to be **Elementwise** if the expression
`R r = f(x1, ...,xn)` is semantically equivalent to:

  - if `R` models eve::simd_value:    `R r = [](auto i, auto) { return f(at(x1,i),  ..., at(xn,i)); }`
  - if `R` models eve::scalar_value:  `R r = return f(x1,  ..., xn)`

@note No constraints are required on either the input or output types.

---

@subsection glossary_reduction Reductions

Elementwise operations in **EVE** describe functions that operates over all elements of a given
[value](@ref eve::value) to produce a single [scalar result](@ref eve::scalar_value).

For any [value](@ref eve::value) `x` of type `T`, a Callable Object `f` returning a
[scalar value](@ref eve::scalar_value) of type `eve::element_type<T>` is said to be a **Reduction**.

@section glossary_function_semantic Function Semantic

@subsection glossary_arithmetic Arithmetic Functions

For any [values](@ref eve::value) `x1`, ..., `xn` of types `T1`, ..., `Tn` so that the expression
`using C = eve::common_compatible_t<T1,...,Tn>` is valid, a Callable Object `f` is said to be
an **Arithmetic Function** if the expression `C r = f(x1, ...,xn)` is semantically equivalent to:

  - if `C` models eve::simd_value: `C r = [](auto i, auto) { return f(at(C(x1),i),  ..., at(C(xn),i)); }`
  - if `C` models eve::scalar_value:  `C r = return f(C(x1),  ..., C(xn))`

In a less formal way, **EVE** @ref glossary_arithmetic generalizes the notion of native C++
arithmetic operations.

@note A large majority of @ref glossary_arithmetic are _de facto_ @ref glossary_elementwise .

---

@subsection glossary_bitwise Bitwise Functions

For any [values](@ref eve::value) `x1`, ..., `xn` of types `T1`, ..., `Tn`so that the expression
`eve::bit_compatible_values<T1,...,Tn>` evaluates to `true`, a Callable Object `f` is said to be
a **Bitwise Function** if the expression `T1 r = f(x1, ..., xn)` is semantically equivalent to:

  - if `T1` models eve::simd_value:     `T1 r = [](auto i, auto) { return f(at(x1,i),... at(``eve::bit_cast(xn,``eve::as(x1)``),i); }`
  - if `T1` models eve::scalar_value:   `T1 r = return f(x1,...``eve::bit_cast(xn,``eve::as(x1)``))`

In a less formal way, **EVE** @ref glossary_bitwise can be applied to any pair of types, the first
acting as the value type and the second as a type-less source of bits.

@note A large majority of @ref glossary_bitwise are _de facto_ @ref glossary_elementwise .

---

@subsection glossary_logical Logical Functions

**EVE** @ref glossary_logical are @ref glossary_arithmetic that can only be applied to
[logical values][@ref eve::logical_value) `L1`,... `Ln` that verify that either
`eve::cardinal``<L1>::value == ``eve::cardinal``<Ln>::value` or that, for a given `n`, the
expression `std::same_as<``eve::cardinal``<Ln>, ``eve::scalar_cardinal``>` evaluates to `true`.

In a less formal way, **EVE** @ref glossary_logical can be applied to set of
[logical values](@ref eve::logical_value) as long as they all share the same [number of lanes](@ref eve::cardinal),
except for any potential logical scalar values.

@note A large majority of @ref glossary_logical are _de facto_ @ref glossary_elementwise .

---

@subsection glossary_constant Constant Functions

Some of the object functions defined by **EVE** have as only parameter a `target` value. All but two (see above) are reputed to be
constants of the type referenced by the target.

For instance `eve::one(eve::as<float>())` is merely 1.0f, `eve::one(eve::as<eve::wide<float>>())` is a `eve::wide<float>` value filled with
elements equal to 1.0f.

All these constants can be bracketed using decorators downward and upward.
This means that for all constants, say of name xxx, one have

            downward(xxx)(as<T>()) <= xxx(as<T>()) <= upward(xxx)(as<T>()).

For most constants the 3 values are identical, but this is not the case when the constant semantic is a mathematical value which does not possess an exact
representation in the target type. For instance think of pi or sqrt(2) for ieee floating type values.

In these later cases the direct call to constant value always returns the nearest representable value to the mathematical constant,
but it is constant dependant if this effective value is less or greater than the full precision  mathematical value.

For pi:
   - eve::pi(as<float>()) is greater than the mathematical pi
   - eve::pi(as<double>()) is less than the mathematical pi

The decorators give the guarantee that if math(xxx) is the (not representable) mathematical value, we get:

            downward(xxx)(as<T>()) <= math(xxx) <= upward(xxx)(as<T>())

for all supported target with ordered type. Of course one of these two values is the constant itself and the two values differs at most by 0.5ulp.

@note Special case of eve::true_ and eve::false_

        - they are the only constants whose name ends with an underscore (for obvious language limitations reason),
        - eve::true_(as<T>()) and eve::false_(as<T>()) do not return a value of type T but as_logical<T>.
        - they do not support any decorator.