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
add_custom_target(special.scalar.unit)
add_custom_target(special.simd.unit)
add_dependencies(special.unit special.scalar.unit)
add_dependencies(special.unit special.simd.unit)

##==================================================================================================
## Other tests
##==================================================================================================
#add_subdirectory(failure)
#add_subdirectory(constant)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

### TEMPORARY MEASURE
### make_all_units(ROOT special NAME gamma                ARCH scalar simd TYPES ${real_types}    )
### make_all_units(ROOT special NAME stirling             ARCH scalar simd TYPES ${real_types}    )
### TEMPORARY MEASURE
