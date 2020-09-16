##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(random.algorithm.tst)
add_custom_target(random.algorithm.scalar.tst)
add_custom_target(random.algorithm.simd.tst)
add_dependencies(random.algorithm.tst random.algorithm.scalar.tst)
add_dependencies(random.algorithm.tst random.algorithm.simd.tst)
add_dependencies(random.scalar.tst random.algorithm.scalar.tst)
add_dependencies(random.simd.tst random.algorithm.simd.tst)
add_dependencies(random.tst random.algorithm.tst)

##==================================================================================================
## Algoritms function unit tests
##==================================================================================================
make_all_units(ROOT random.algorithm NAME all     ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT random.algorithm NAME any     ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT random.algorithm NAME nbtrue  ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT random.algorithm NAME none    ARCH scalar simd TYPES ${all_types} )
