##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(unit.compensated.exe           )
add_dependencies(unit.exe unit.compensated.exe   )

make_unit("unit.compensated"  asum.cpp           )
#make_unit("unit.compensated"  dot.cpp            )
