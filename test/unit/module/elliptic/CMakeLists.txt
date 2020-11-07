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
add_custom_target(unit.elliptic.exe       )
add_custom_target(unit.elliptic.scalar.exe)
add_custom_target(unit.elliptic.simd.exe  )

add_dependencies(unit.scalar.exe    unit.elliptic.scalar.exe )
add_dependencies(unit.simd.exe      unit.elliptic.simd.exe   )
add_dependencies(unit.elliptic.exe unit.elliptic.scalar.exe   )
add_dependencies(unit.elliptic.exe unit.elliptic.simd.exe     )

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

make_all_units(ROOT unit.elliptic NAME am                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.elliptic NAME ellint_d             ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.elliptic NAME ellint_rc            ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.elliptic NAME ellint_rd            ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.elliptic NAME ellint_rf            ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.elliptic NAME ellint_rg            ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.elliptic NAME ellint_1             ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.elliptic NAME ellint_2             ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.elliptic NAME ellint_3             ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.elliptic NAME jacobi_zeta          ARCH scalar simd TYPES ${real_types}    )
#make_all_units(ROOT unit.elliptic NAME jacobi_elliptic      ARCH scalar simd TYPES ${real_types}    )