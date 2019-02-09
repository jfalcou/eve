##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##  Copyright 2019 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## scalar tests
add_unit_test( "core" scalar/bitwise_and.cpp )
add_unit_test( "core" scalar/bitwise_or.cpp )
add_unit_test( "core" scalar/bitwise_xor.cpp )
add_unit_test( "core" scalar/bitwise_cast.cpp )
add_unit_test( "core" scalar/bitwise_not.cpp )
add_unit_test( "core" scalar/bitwise_notand.cpp )
add_unit_test( "core" scalar/bitwise_andnot.cpp )
add_unit_test( "core" scalar/bitwise_ornot.cpp )
add_unit_test( "core" scalar/bitwise_notor.cpp )
add_unit_test( "core" scalar/unary_plus.cpp )
add_unit_test( "core" scalar/unary_minus.cpp )

list_tests("scalar/sub"     "core" ${all_types})
list_tests("scalar/add"     "core" ${all_types})
list_tests("scalar/popcnt"  "core" ${integral_types})

add_unit_test( "core" scalar/inf.cpp )
add_unit_test( "core" scalar/minf.cpp )
add_unit_test( "core" scalar/nan.cpp )


##==================================================================================================
## SIMD tests
add_unit_test( "core" simd/bitwise_cast.cpp )

list_tests("simd/sub"         "core" ${all_types})
list_tests("simd/add"         "core" ${all_types})
list_tests("simd/bitwise_and" "core" ${all_types})
list_tests("simd/bitwise_or"  "core" ${all_types})
list_tests("simd/bitwise_xor" "core" ${all_types})
list_tests("simd/bitwise_not" "core" ${all_types})
list_tests("simd/bitwise_notand" "core" ${all_types})
list_tests("simd/bitwise_andnot" "core" ${all_types})
list_tests("simd/bitwise_ornot" "core" ${all_types})
list_tests("simd/bitwise_notor" "core" ${all_types})
list_tests("simd/unary_plus" "core" ${all_types})
list_tests("simd/unary_minus" "core" ${all_types}) 
