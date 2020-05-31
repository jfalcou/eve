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
add_custom_target(algorithm.unit)
add_custom_target(algorithm.scalar.unit)
add_custom_target(algorithm.simd.unit)
add_dependencies(algorithm.unit algorithm.scalar.unit)
add_dependencies(algorithm.unit algorithm.simd.unit)

##==================================================================================================
## Algoritms function unit tests
##==================================================================================================
make_all_units(ROOT algorithm NAME all                   ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT algorithm NAME any                   ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT algorithm NAME nbtrue                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT algorithm NAME none                  ARCH scalar simd TYPES ${all_types}     )
