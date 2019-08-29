##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##  Copyright 2019 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## shuffle tests
## list_tests("cardinal_1" "core.simd.shuffle" ${all_types})
add_unit_test( "core.simd.shuffle" sandbox.cpp )
