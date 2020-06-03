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
add_custom_target(special.bench)
add_custom_target(special.scalar.bench)
add_custom_target(special.simd.bench)
add_dependencies(special.bench special.scalar.bench)
add_dependencies(special.bench special.simd.bench)

##==================================================================================================
## Elementwise function bench tests
##==================================================================================================

### TEMPORARY MEASURE
### make_all_benchs(ROOT special NAME gamma                ARCH scalar simd TYPES ${real_types}    )
### make_all_benchs(ROOT special NAME stirling             ARCH scalar simd TYPES ${real_types}    )
### TEMPORARY MEASURE
