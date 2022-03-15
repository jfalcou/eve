##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
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
