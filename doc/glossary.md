Glossary {#glossary}
========

@tableofcontents

@section glossary_semantic Semantic of E.V.E functions

@subsection glossary_arithmetic Arithmetic operations semantic

Let `x`, `y` and `z` be three values of respective types `T, U, V`.

For any callable object `f`, the expression `f(x,y)` has an **arithmetic operations semantic**
if `T` and `U`  are [compatible](../../concepts.html#compatible) [values](../../concepts.html#value)
and the call is semantically equivalent to:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
using TU = std::conditional< scalar_value<T>, U, T>;
return f(TU(x), TU(y));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the same way, the expression `f(x,y,z)` has an **arithmetic operations semantic**
if `T`, `U` and `V` are mutually [compatible](../../concepts/compatible.html)
[values](../../concepts/value.html) and the call is semantically equivalent to:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
using TU  = std::conditional< scalar_value<T> , U, T >;
using TUV = std::conditional< scalar_value<TU>, V, TU>;
return f(TUV(x), TUV(y),TUV(z));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In each case the return type is the compatibility result of the types of the three parameters.

These definition can easily be extended to the N parameters case.

@subsection glossary_bitwise Bitwise operations semantic
Let `x`, `y` be two values of respective types `T` and `U`.

When invoking the function-call operator of an object `f`,  the calls `f(x,y)`
will be reputed to respond to the **bitwise operations semantic**
if the two types are bit_compatible and the call is semantically equivalent to:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
if constexpr(scalar_value<T> && simd_value<U>)
{
  using r_t = wide<element_type<T>>,cardinal_t<U>)
  r_t xx(bit_cast(x, as<element_type<T>()>);
  r_t yy(bit_cast(y, as<r_t>()));
  return f(xx, yy);
}
else if  constexpr(simd_value<T> && scalar_value<U>)
{
  auto yy = bit_cast(y, as<element_type<T>()>);
  return f(x, yy);
}
else
{
  auto yy = bit_cast(y, as<T>()>);
  return f(x, yy);
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The return type always has `T` as element type.

@subsection glossary_logical Logical operations semantic

Let `x`, `y` be two values of respective types `T` and `U`.

When invoking the function-call operator of an object `f`,  the calls `f(x,y)`
will be reputed to respond to the **logical operations semantic**
if the two types are ... TODO

@subsection glossary_elementwise Element-wise operations

Let `x1`, `x2`, ..., `xn` be  values of respective types `X1` and `X2`, ... `Xn` which are mutually compatible.
and let `C` be the compatibility result of these types.

When invoking the function-call operator of an object `f`, the call `f(x1, x2, ...)` will be reputed to
respond to the **element-wise operations semantic** if it is semantically equivalent to:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  C x_1(x1), ..., x_n(xn);

  if constexpr(simd_value<C>)
  {
    for(int i=0; i < cardinal_v<T>; ++i)
    {
      r[i] = f(x_1[i],  ..., x_n[i]);
    }
  }
  else
  {
    r = f(x_1, ..., x_n);
  }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

@section glossary_properties Property of EVE types

@subsection Cardinal
The cardinal of a [value](reference/concepts.html#value) is the number of elements inside the
corresponding SIMD register. For any [scalar types](reference/concepts.html#scalar_value), the
cardinal is equal to 1. For [SIMD types](reference/concepts.html#simd_value), it's equal to the
number of lanes in the register.

**EVE** provides the [cardinal](reference/types/traits.html#cardinal) trait to access the cardinal
of any type.

@subsection Element type
For any [value type](reference/concepts.html#value), **EVE** defines its underlying element type as
the basic type used to represent its value. For any [scalar types](reference/concepts.html#scalar_value),
its type is its own element type. For [SIMD types](reference/concepts.html#simd_value), it's defined
as its associated scalar type.

**EVE** provides the [element_type](reference/types/traits.html#element_type) trait to access the
element type of any type.

@subsection Type family
The type family is based on the value concept a type satisfies. One says a type is from a scalar
family if it satisfies the [scalar_value](reference/concepts.html#scalar_value) and from a SIMD
family if it satisfies the [simd_value](reference/concepts.html#simd_value).
