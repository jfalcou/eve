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
add_custom_target(unit.real.stats.exe                )
add_custom_target(unit.real.stats.constant.exe       )
add_custom_target(unit.real.stats.constant.scalar.exe)
add_custom_target(unit.real.stats.constant.simd.exe  )
add_custom_target(unit.real.stats.scalar.exe         )
add_custom_target(unit.real.stats.simd.exe           )

add_dependencies(unit.real.scalar.exe         unit.real.stats.scalar.exe          )
add_dependencies(unit.real.simd.exe           unit.real.stats.simd.exe            )
add_dependencies(unit.real.stats.constant.exe unit.real.stats.constant.scalar.exe )
add_dependencies(unit.real.stats.constant.exe unit.real.stats.constant.simd.exe   )
add_dependencies(unit.real.stats.scalar.exe   unit.real.stats.constant.scalar.exe )
add_dependencies(unit.real.stats.simd.exe     unit.real.stats.constant.simd.exe   )
add_dependencies(unit.real.stats.exe          unit.real.stats.constant.exe        )
add_dependencies(unit.real.stats.exe          unit.real.stats.scalar.exe          )
add_dependencies(unit.real.stats.exe          unit.real.stats.simd.exe            )

##==================================================================================================
## Other tests
##==================================================================================================
##add_subdirectory(failure)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================
make_all_units(ROOT unit.real.stats NAME cauchy                   ARCH scalar simd TYPES ${real_types}     )
