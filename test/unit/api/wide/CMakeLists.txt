##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## wide API failure tests
check_failures("decrement/logical" "unit.api" ${all_types})
check_failures("increment/logical" "unit.api" ${all_types})

##==================================================================================================
## wide API tests
make_unit( "unit.api" std.cpp )
make_all_units(ROOT unit.api  NAME make   ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME splat  ARCH simd TYPES ${all_types} )
