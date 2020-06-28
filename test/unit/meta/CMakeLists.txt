##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## General meta tests
make_unit( "unit.meta" as_floating_point.cpp )
make_unit( "unit.meta" as_integer.cpp )
make_unit( "unit.meta" as_wide.cpp )
make_unit( "unit.meta" sign_of.cpp )

##==================================================================================================
## Concepts tests
make_unit( "unit.meta.concept" rebindable.cpp )
make_unit( "unit.meta.concept" decorator.cpp )
make_unit( "unit.meta.concept" value.cpp )

##==================================================================================================
## Traits tests
make_unit( "unit.meta" cardinal.cpp )
make_unit( "unit.meta" has_abi.cpp )
make_unit( "unit.meta" element_type.cpp )
