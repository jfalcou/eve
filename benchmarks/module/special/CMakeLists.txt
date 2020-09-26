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

##==================================================================================================
## Elementwise function bench tests
##==================================================================================================

### TEMPORARY MEASURE
make_all_benchs(ROOT special NAME erf      TYPES ${real_types}    )
make_all_benchs(ROOT special NAME erfc     TYPES ${real_types}    )
### make_all_benchs(ROOT special NAME gamma    TYPES ${real_types}    )
### make_all_benchs(ROOT special NAME stirling TYPES ${real_types}    )
### TEMPORARY MEASURE
