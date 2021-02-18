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
add_custom_target(unit.real.algorithm.exe       )
add_custom_target(unit.real.algorithm.scalar.exe)
add_custom_target(unit.real.algorithm.simd.exe  )

add_dependencies(unit.real.scalar.exe     unit.real.algorithm.scalar.exe )
add_dependencies(unit.real.simd.exe       unit.real.algorithm.simd.exe   )
add_dependencies(unit.real.algorithm.exe  unit.real.algorithm.scalar.exe )
add_dependencies(unit.real.algorithm.exe  unit.real.algorithm.simd.exe   )

##==================================================================================================
## Algoritms function unit tests
##==================================================================================================
make_all_units(ROOT unit.real.algorithm NAME all         ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT unit.real.algorithm NAME any         ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT unit.real.algorithm NAME count_true      ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT unit.real.algorithm NAME first_true  ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT unit.real.algorithm NAME none        ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT unit.real.algorithm NAME maximum     ARCH scalar simd TYPES ${all_types} )
