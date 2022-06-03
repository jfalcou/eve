##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
##==================================================================================================
## General meta tests
make_unit( "unit.meta" as_floating_point.cpp )
make_unit( "unit.meta" as_logical.cpp )
make_unit( "unit.meta" as_integer.cpp )
make_unit( "unit.meta" as_uinteger.cpp )
make_unit( "unit.meta" as_wide.cpp )

##==================================================================================================
## Concepts tests
make_unit( "unit.meta.concept" scalar.cpp )
make_unit( "unit.meta.concept" simd.cpp )
make_unit( "unit.meta.concept" decorator.cpp )
make_unit( "unit.meta.concept" value.cpp )
make_unit( "unit.meta.concept" native_simd_for_abi.cpp )

##==================================================================================================
## Traits tests
make_unit( "unit.meta" cardinal.cpp )
make_unit( "unit.meta" common_type.cpp )
make_unit( "unit.meta" element_type.cpp )
make_unit( "unit.meta" has_abi.cpp )
make_unit( "unit.meta" iterator_cardinal.cpp )
make_unit( "unit.meta" max_scalar_size.cpp )
make_unit( "unit.meta" value_type.cpp )
make_unit( "unit.meta" wide_value_type.cpp )


##==================================================================================================
## Interoperability tests
make_unit( "unit.meta" std_compatibility.cpp )
