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
add_custom_target(exhaustive.real.special.exe)
add_custom_target(exhaustive.real.special.scalar.exe)
add_custom_target(exhaustive.real.special.simd.exe)
add_dependencies(exhaustive.real.special.exe exhaustive.real.special.scalar.exe)
add_dependencies(exhaustive.real.special.exe exhaustive.real.special.simd.exe)
add_dependencies(exhaustive.real.scalar.exe exhaustive.real.special.scalar.exe)
add_dependencies(exhaustive.real.simd.exe exhaustive.real.special.simd.exe)
add_dependencies(exhaustive.real.exe exhaustive.real.special.exe)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

### TEMPORARY MEASURE
### make_all_units(ROOT exhaustive.real.special NAME gamma                ARCH scalar simd TYPES ${real_types}    )
### make_all_units(ROOT exhaustive.real.special NAME stirling             ARCH scalar simd TYPES ${real_types}    )
### TEMPORARY MEASURE
