##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(unit.elliptic.exe           )
add_dependencies(unit.exe unit.elliptic.exe   )

make_unit( "unit.elliptic" ellint_1.cpp  )
make_unit( "unit.elliptic" ellint_2.cpp  )
make_unit( "unit.elliptic" ellint_d.cpp  )
make_unit( "unit.elliptic" ellint_rc.cpp )
make_unit( "unit.elliptic" ellint_rd.cpp )
make_unit( "unit.elliptic" ellint_rf.cpp )
make_unit( "unit.elliptic" ellint_rg.cpp )
make_unit( "unit.elliptic" ellint_rj.cpp )
