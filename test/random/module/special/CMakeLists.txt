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
add_custom_target(random.special.tst)
add_custom_target(random.special.scalar.tst)
add_custom_target(random.special.simd.tst)
add_dependencies(random.special.tst random.special.scalar.tst)
add_dependencies(random.special.tst random.special.simd.tst)
add_dependencies(random.scalar.tst random.special.scalar.tst)
add_dependencies(random.simd.tst random.special.simd.tst)
add_dependencies(random.tst random.special.tst)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

### TEMPORARY MEASURE
### make_all_units(ROOT random.special NAME gamma                ARCH scalar simd TYPES ${real_types}    )
### make_all_units(ROOT random.special NAME stirling             ARCH scalar simd TYPES ${real_types}    )
### TEMPORARY MEASURE
