##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(unit.complex.exe          )
add_dependencies(unit.exe unit.complex.exe  )

make_unit("unit.complex"  constructor.cpp   )
make_unit("unit.complex"  imag.cpp          )
make_unit("unit.complex"  real.cpp          )
