##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## scalar tests
list_tests("scalar/popcnt" "core" ${integral_types})
list_tests("scalar/plus" "core" ${all_types})

##==================================================================================================
## SIMD tests
list_tests("simd/plus" "core" ${all_types})
