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
add_custom_target(exhaustive.algorithm.exe)
add_custom_target(exhaustive.algorithm.scalar.exe)
add_custom_target(exhaustive.algorithm.simd.exe)
add_dependencies(exhaustive.algorithm.exe exhaustive.algorithm.scalar.exe)
add_dependencies(exhaustive.algorithm.exe exhaustive.algorithm.simd.exe)
add_dependencies(exhaustive.scalar.exe exhaustive.algorithm.scalar.exe)
add_dependencies(exhaustive.simd.exe exhaustive.algorithm.simd.exe)
add_dependencies(exhaustive.exe exhaustive.algorithm.exe)

##==================================================================================================
## Algoritms function unit tests
##==================================================================================================
make_all_units(ROOT exhaustive.algorithm NAME all     ARCH scalar simd TYPES ${all_types_32} )
make_all_units(ROOT exhaustive.algorithm NAME any     ARCH scalar simd TYPES ${all_types_32} )
make_all_units(ROOT exhaustive.algorithm NAME nbtrue  ARCH scalar simd TYPES ${all_types_32} )
make_all_units(ROOT exhaustive.algorithm NAME none    ARCH scalar simd TYPES ${all_types_32} )
