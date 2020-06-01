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
add_custom_target(random.special.unit)
add_custom_target(random.special.scalar.unit)
add_custom_target(random.special.simd.unit)
add_dependencies(random.special.unit random.special.scalar.unit)
add_dependencies(random.special.unit random.special.simd.unit)
add_dependencies(random.scalar.unit random.special.scalar.unit)
add_dependencies(random.simd.unit random.special.simd.unit)
add_dependencies(random.unit random.special.unit)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

### TEMPORARY MEASURE
### make_all_units(ROOT random.special NAME gamma                ARCH scalar simd TYPES ${real_types}    )
### make_all_units(ROOT random.special NAME stirling             ARCH scalar simd TYPES ${real_types}    )
### TEMPORARY MEASURE
