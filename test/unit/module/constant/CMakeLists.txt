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
add_custom_target(unit.constant.tst       )
add_custom_target(unit.constant.scalar.tst)
add_custom_target(unit.constant.simd.tst  )

add_dependencies(unit.scalar.tst    unit.constant.scalar.tst )
add_dependencies(unit.simd.tst      unit.constant.simd.tst   )
add_dependencies(unit.constant.tst unit.constant.scalar.tst   )
add_dependencies(unit.constant.tst unit.constant.simd.tst     )

##==================================================================================================
## Regular constant function unit tests
##==================================================================================================

make_all_units(ROOT unit.constant NAME basic                ARCH scalar simd TYPES ${all_types}    )
make_all_units(ROOT unit.constant NAME ieee754              ARCH scalar simd TYPES ${real_types}   )
make_all_units(ROOT unit.constant NAME limit                ARCH scalar simd TYPES ${all_types}    )
make_all_units(ROOT unit.constant NAME math                 ARCH scalar simd TYPES ${real_types}   )

##==================================================================================================
## Other Constant tests
make_unit( "unit.constant" constant.cpp     )
make_unit( "unit.constant" conditional.cpp  )
