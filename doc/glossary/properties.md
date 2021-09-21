Property of EVE types  {#glossary_properties}
=====================

@tableofcontents

@section glossary_properties_type_family Type family
The type family is based on the value concept a type satisfies. One says a type is from the scalar
family if it models eve::scalar_value and from the SIMD family if it models eve::simd_value.

@section glossary_properties_cardinal Cardinal
The cardinal of a [value](@ref eve::value) is the number of elements inside said value.
**EVE** provides the eve::cardinal type trait to generically retrieve the cardinal of any type.

For any [scalar type](@ref eve::scalar_value) `T`, `eve::cardinal<T>``::type` evaluates to eve::scalar_cardinal.
For any [SIMD type](@ref eve::simd_value) `T`, `eve::cardinal<T>``::type` evaluates to `eve::fixed``<N>`,
  where `N` is the number of lanes of the underlying SIMD register.

@section glossary_element_type Element type
For any [value type](@ref eve::value), **EVE** defines its underlying element type as the basic type
used to represent its value.

**EVE** provides the eve::element_type type trait to generically retrieve the element type of any type.

For any [scalar type](@ref eve::scalar_value) `T`, `eve::element_type<T>``::type` evaluates to `T`.
For any [SIMD type](@ref eve::simd_value) `eve::wide``<T,N>`, `eve::element_type<``eve::wide`<T,N>>``::type`
evaluates to `T`.
For any [logical type](@ref eve::logical_value) `eve::logical``<T>`, `eve::element_type``<`eve::logical``<T>``::type`
evaluates to `eve::logical`<T>`.
