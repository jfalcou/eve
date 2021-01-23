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
add_custom_target(bench.combinatorial.exe)

##==================================================================================================
## Combinatorial function bench tests
##==================================================================================================

### TEMPORARY MEASURE
make_all_benchs(ROOT bench.combinatorial NAME gcd TYPES ${signed_types}    )
