##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## scalar tests
add_unit_test( "core" scalar/bitwise_and.cpp )
add_unit_test( "core" scalar/bitwise_or.cpp )
add_unit_test( "core" scalar/bitwise_cast.cpp )

list_tests("scalar/minus"         "core" ${all_types})
list_tests("scalar/plus"          "core" ${all_types})
list_tests("scalar/popcnt"        "core" ${integral_types})

##==================================================================================================
## SIMD tests
add_unit_test( "core" simd/bitwise_cast.cpp )

list_tests("simd/minus" "core" ${all_types})
list_tests("simd/plus" "core" ${all_types})
list_tests("simd/bitwise_and" "core" ${all_types})
list_tests("simd/bitwise_or" "core" ${all_types})
