##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
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
make_all_units(ROOT unit.real.combinatorial NAME double_factorial     ARCH scalar simd TYPES ${uint_types} )
make_all_units(ROOT unit.real.combinatorial NAME factorial            ARCH scalar simd TYPES ${uint_types} )
make_all_units(ROOT unit.real.combinatorial NAME fibonacci            ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.combinatorial NAME gcd                  ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT unit.real.combinatorial NAME lcm                  ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT unit.real.combinatorial NAME nth_prime            ARCH scalar simd TYPES ${uint_types} )
make_all_units(ROOT unit.real.combinatorial NAME rising_factorial     ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.combinatorial NAME lrising_factorial    ARCH scalar simd TYPES ${real_types} )

##==================================================================================================
## new style tests
##==================================================================================================
make_unit("unit.real.combinatorial"  bernouilli.cpp                   )
make_unit("unit.real.combinatorial"  prime_floor.cpp                  )
