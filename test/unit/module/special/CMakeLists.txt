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
add_custom_target(unit.special.tst       )
add_custom_target(unit.special.scalar.tst)
add_custom_target(unit.special.simd.tst  )

add_dependencies(unit.scalar.tst    unit.special.scalar.tst )
add_dependencies(unit.simd.tst      unit.special.simd.tst   )
add_dependencies(unit.special.tst unit.special.scalar.tst   )
add_dependencies(unit.special.tst unit.special.simd.tst     )

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

make_all_units(ROOT unit.special NAME beta                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME dawson               ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME erf                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME erfc                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME erfcx                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME gamma                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME gammaln              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME signgam              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.special NAME stirling             ARCH scalar simd TYPES ${real_types}    )
