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
add_custom_target(exhaustive.algorithm.tst)
add_custom_target(exhaustive.algorithm.scalar.tst)
add_custom_target(exhaustive.algorithm.simd.tst)
add_dependencies(exhaustive.algorithm.tst exhaustive.algorithm.scalar.tst)
add_dependencies(exhaustive.algorithm.tst exhaustive.algorithm.simd.tst)
add_dependencies(exhaustive.scalar.tst exhaustive.algorithm.scalar.tst)
add_dependencies(exhaustive.simd.tst exhaustive.algorithm.simd.tst)
add_dependencies(exhaustive.tst exhaustive.algorithm.tst)

##==================================================================================================
## Algoritms function unit tests
##==================================================================================================
make_all_units(ROOT exhaustive.algorithm NAME all     ARCH scalar simd TYPES ${all_types_32} )
make_all_units(ROOT exhaustive.algorithm NAME any     ARCH scalar simd TYPES ${all_types_32} )
make_all_units(ROOT exhaustive.algorithm NAME nbtrue  ARCH scalar simd TYPES ${all_types_32} )
make_all_units(ROOT exhaustive.algorithm NAME none    ARCH scalar simd TYPES ${all_types_32} )
