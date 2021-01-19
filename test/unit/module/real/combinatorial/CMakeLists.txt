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
add_custom_target(unit.real.combinatorial.exe       )
add_custom_target(unit.real.combinatorial.scalar.exe)
add_custom_target(unit.real.combinatorial.simd.exe  )

add_dependencies(unit.real.scalar.exe         unit.real.combinatorial.scalar.exe )
add_dependencies(unit.real.simd.exe           unit.real.combinatorial.simd.exe   )
add_dependencies(unit.real.combinatorial.exe  unit.real.combinatorial.scalar.exe )
add_dependencies(unit.real.combinatorial.exe  unit.real.combinatorial.simd.exe   )

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================
make_all_units(ROOT unit.real.combinatorial NAME double_factorial    ARCH scalar simd TYPES ${uint_types} )
####make_all_units(ROOT unit.real.combinatorial NAME factorial           ARCH scalar simd TYPES ${uint_types} )
make_all_units(ROOT unit.real.combinatorial NAME fibonacci           ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.combinatorial NAME gcd                 ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT unit.real.combinatorial NAME lcm                 ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT unit.real.combinatorial NAME nth_prime           ARCH scalar simd TYPES ${uint_types}  )
