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
add_custom_target(unit.real.probas.exe                )
add_custom_target(unit.real.probas.constant.exe       )
add_custom_target(unit.real.probas.constant.scalar.exe)
add_custom_target(unit.real.probas.constant.simd.exe  )
add_custom_target(unit.real.probas.scalar.exe         )
add_custom_target(unit.real.probas.simd.exe           )

add_dependencies(unit.real.scalar.exe          unit.real.probas.scalar.exe          )
add_dependencies(unit.real.simd.exe            unit.real.probas.simd.exe            )
add_dependencies(unit.real.probas.constant.exe unit.real.probas.constant.scalar.exe )
add_dependencies(unit.real.probas.constant.exe unit.real.probas.constant.simd.exe   )
add_dependencies(unit.real.probas.scalar.exe   unit.real.probas.constant.scalar.exe )
add_dependencies(unit.real.probas.simd.exe     unit.real.probas.constant.simd.exe   )
add_dependencies(unit.real.probas.exe          unit.real.probas.constant.exe        )
add_dependencies(unit.real.probas.exe          unit.real.probas.scalar.exe          )
add_dependencies(unit.real.probas.exe          unit.real.probas.simd.exe            )

##==================================================================================================
## Other tests
##==================================================================================================
##add_subdirectory(failure)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================
make_all_units(ROOT unit.real.probas NAME exponential_distribution  ARCH scalar simd TYPES ${real_types}     )
make_all_units(ROOT unit.real.probas NAME cauchy              ARCH scalar simd TYPES ${real_types}     )
make_all_units(ROOT unit.real.probas NAME normal_distribution       ARCH scalar simd TYPES ${real_types}     )
make_all_units(ROOT unit.real.probas NAME binomial            ARCH scalar simd TYPES ${real_types}     )
make_all_units(ROOT unit.real.probas NAME poisson             ARCH scalar simd TYPES ${real_types}     )
make_all_units(ROOT unit.real.probas NAME uniform_real_distribution ARCH scalar simd TYPES ${real_types}     )
