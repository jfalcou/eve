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
add_custom_target(unit.real.constant.exe       )
add_custom_target(unit.real.constant.scalar.exe)
add_custom_target(unit.real.constant.simd.exe  )

add_dependencies(unit.real.scalar.exe   unit.real.constant.scalar.exe )
add_dependencies(unit.real.simd.exe     unit.real.constant.simd.exe   )
add_dependencies(unit.real.constant.exe unit.real.constant.scalar.exe )
add_dependencies(unit.real.constant.exe unit.real.constant.simd.exe   )

##==================================================================================================
## Regular constant function unit tests
##==================================================================================================

make_all_units(ROOT unit.real.constant NAME basic                ARCH scalar simd TYPES ${all_types}    )
make_all_units(ROOT unit.real.constant NAME ieee754              ARCH scalar simd TYPES ${real_types}   )
make_all_units(ROOT unit.real.constant NAME limit                ARCH scalar simd TYPES ${all_types}    )
make_all_units(ROOT unit.real.constant NAME math                 ARCH scalar simd TYPES ${real_types}   )

##==================================================================================================
## Other Constant tests
make_unit( "unit.real.constant" constant.cpp     )
