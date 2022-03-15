##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(unit.polynomial.exe           )
add_dependencies(unit.exe unit.polynomial.exe   )

make_unit("unit.polynomial"  gegenbauer.cpp     )
make_unit("unit.polynomial"  hermite.cpp        )
make_unit("unit.polynomial"  horner.cpp         )
make_unit("unit.polynomial"  laguerre.cpp       )
make_unit("unit.polynomial"  legendre.cpp       )
make_unit("unit.polynomial"  newton.cpp         )
make_unit("unit.polynomial"  reverse_horner.cpp )
