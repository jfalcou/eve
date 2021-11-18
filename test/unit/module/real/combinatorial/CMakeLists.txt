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
## new style tests
##==================================================================================================
make_unit("unit.real.combinatorial"  bernouilli.cpp                   )
make_unit("unit.real.combinatorial"  double_factorial.cpp             )
make_unit("unit.real.combinatorial"  factorial.cpp                    )
make_unit("unit.real.combinatorial"  fibonacci.cpp                    )
make_unit("unit.real.combinatorial"  lfactorial.cpp                   )
make_unit("unit.real.combinatorial"  nth_prime.cpp                    )
make_unit("unit.real.combinatorial"  prime_floor.cpp                  )
make_unit("unit.real.combinatorial"  lrising_factorial.cpp            )
make_unit("unit.real.combinatorial"  rising_factorial.cpp             )
make_unit("unit.real.combinatorial"  gcd.cpp                          )
make_unit("unit.real.combinatorial"  lcm.cpp                          )
