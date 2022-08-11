##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

add_custom_target(unit.combinatorial.exe           )
add_dependencies(unit.exe unit.combinatorial.exe   )


make_unit( "unit.combinatorial" bernouilli.cpp       )
make_unit( "unit.combinatorial" fibonacci.cpp        )
make_unit( "unit.combinatorial" gcd.cpp              )
make_unit( "unit.combinatorial" lcm.cpp              )
make_unit( "unit.combinatorial" nth_prime.cpp        )
make_unit( "unit.combinatorial" prime_ceil.cpp       )
make_unit( "unit.combinatorial" prime_floor.cpp      )
