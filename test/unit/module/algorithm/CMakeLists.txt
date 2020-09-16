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
add_custom_target(unit.algorithm.tst       )
add_custom_target(unit.algorithm.scalar.tst)
add_custom_target(unit.algorithm.simd.tst  )

add_dependencies(unit.scalar.tst    unit.algorithm.scalar.tst )
add_dependencies(unit.simd.tst      unit.algorithm.simd.tst   )
add_dependencies(unit.algorithm.tst unit.algorithm.scalar.tst )
add_dependencies(unit.algorithm.tst unit.algorithm.simd.tst   )

##==================================================================================================
## Algoritms function unit tests
##==================================================================================================
make_all_units(ROOT unit.algorithm NAME all                   ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT unit.algorithm NAME any                   ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT unit.algorithm NAME nbtrue                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT unit.algorithm NAME none                  ARCH scalar simd TYPES ${all_types}     )
