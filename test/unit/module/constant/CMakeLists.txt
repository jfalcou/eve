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
add_custom_target(unit.constant.exe       )
add_custom_target(unit.constant.scalar.exe)
add_custom_target(unit.constant.simd.exe  )

add_dependencies(unit.scalar.exe    unit.constant.scalar.exe )
add_dependencies(unit.simd.exe      unit.constant.simd.exe   )
add_dependencies(unit.constant.exe unit.constant.scalar.exe   )
add_dependencies(unit.constant.exe unit.constant.simd.exe     )

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
