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
add_custom_target(random.algorithm.exe)
add_custom_target(random.algorithm.scalar.exe)
add_custom_target(random.algorithm.simd.exe)
add_dependencies(random.algorithm.exe random.algorithm.scalar.exe)
add_dependencies(random.algorithm.exe random.algorithm.simd.exe)
add_dependencies(random.scalar.exe random.algorithm.scalar.exe)
add_dependencies(random.simd.exe random.algorithm.simd.exe)
add_dependencies(random.exe random.algorithm.exe)

##==================================================================================================
## Algoritms function unit tests
##==================================================================================================
make_all_units(ROOT random.algorithm NAME all     ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT random.algorithm NAME any     ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT random.algorithm NAME nbtrue  ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT random.algorithm NAME none    ARCH scalar simd TYPES ${all_types} )
