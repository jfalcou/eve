Property of EVE types  {#glossary_properties}
=====================

@tableofcontents

@section glossary_properties_cardinal Cardinal
The cardinal of a [value](reference/concepts.html#value) is the number of elements inside the
corresponding SIMD register. For any [scalar types](reference/concepts.html#scalar_value), the
cardinal is equal to 1. For [SIMD types](reference/concepts.html#simd_value), it's equal to the
number of lanes in the register.

**EVE** provides the [cardinal](reference/types/traits.html#cardinal) trait to access the cardinal
of any type.

@section glossary_element_type Element type
For any [value type](reference/concepts.html#value), **EVE** defines its underlying element type as
the basic type used to represent its value. For any [scalar types](reference/concepts.html#scalar_value),
its type is its own element type. For [SIMD types](reference/concepts.html#simd_value), it's defined
as its associated scalar type.

**EVE** provides the [element_type](reference/types/traits.html#element_type) trait to access the
element type of any type.

@section glossary_properties_type_family Type family
The type family is based on the value concept a type satisfies. One says a type is from a scalar
family if it satisfies the [scalar_value](reference/concepts.html#scalar_value) and from a SIMD
family if it satisfies the [simd_value](reference/concepts.html#simd_value).
