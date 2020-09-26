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
add_custom_target(exhaustive.special.exe)
add_custom_target(exhaustive.special.scalar.exe)
add_custom_target(exhaustive.special.simd.exe)
add_dependencies(exhaustive.special.exe exhaustive.special.scalar.exe)
add_dependencies(exhaustive.special.exe exhaustive.special.simd.exe)
add_dependencies(exhaustive.scalar.exe exhaustive.special.scalar.exe)
add_dependencies(exhaustive.simd.exe exhaustive.special.simd.exe)
add_dependencies(exhaustive.exe exhaustive.special.exe)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

### TEMPORARY MEASURE
### make_all_units(ROOT exhaustive.special NAME gamma                ARCH scalar simd TYPES ${real_types}    )
### make_all_units(ROOT exhaustive.special NAME stirling             ARCH scalar simd TYPES ${real_types}    )
### TEMPORARY MEASURE
