##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
##==================================================================================================
## General meta tests
make_unit( "unit.meta" as_floating_point.cpp )
make_unit( "unit.meta" as_integer.cpp )
make_unit( "unit.meta" as_uinteger.cpp )
make_unit( "unit.meta" as_wide.cpp )
make_unit( "unit.meta" sign_of.cpp )

##==================================================================================================
## Concepts tests
make_unit( "unit.meta.concept" decorator.cpp )
make_unit( "unit.meta.concept" value.cpp )
make_unit( "unit.meta.concept" native_simd_for_abi.cpp )

##==================================================================================================
## Traits tests
make_unit( "unit.meta" cardinal.cpp )
make_unit( "unit.meta" has_abi.cpp )
make_unit( "unit.meta" element_type.cpp )
