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
add_custom_target(unit.special.exe       )
add_custom_target(unit.special.scalar.exe)
add_custom_target(unit.special.simd.exe  )

add_dependencies(unit.scalar.exe    unit.special.scalar.exe )
add_dependencies(unit.simd.exe      unit.special.simd.exe   )
add_dependencies(unit.special.exe unit.special.scalar.exe   )
add_dependencies(unit.special.exe unit.special.simd.exe     )

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

make_all_units(ROOT unit.special NAME beta                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME dawson               ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME erf                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME erfc                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME erfcx                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME j0                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME j1                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME gamma                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME gammainc             ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME gammaln              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME signgam              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME stirling             ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME y0                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME y1                   ARCH scalar simd TYPES ${real_types}    )
