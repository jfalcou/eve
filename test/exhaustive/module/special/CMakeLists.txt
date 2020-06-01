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
add_custom_target(exhaustive.special.unit)
add_custom_target(exhaustive.special.scalar.unit)
add_custom_target(exhaustive.special.simd.unit)
add_dependencies(exhaustive.special.unit exhaustive.special.scalar.unit)
add_dependencies(exhaustive.special.unit exhaustive.special.simd.unit)
add_dependencies(exhaustive.scalar.unit exhaustive.special.scalar.unit)
add_dependencies(exhaustive.simd.unit exhaustive.special.simd.unit)
add_dependencies(exhaustive.unit exhaustive.special.unit)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

### TEMPORARY MEASURE
### make_all_units(ROOT exhaustive.special NAME gamma                ARCH scalar simd TYPES ${real_types}    )
### make_all_units(ROOT exhaustive.special NAME stirling             ARCH scalar simd TYPES ${real_types}    )
### TEMPORARY MEASURE
