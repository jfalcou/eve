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
add_unit_test( "core" scalar/is_equal.cpp )
add_unit_test( "core" scalar/extract.cpp )
add_unit_test( "core" scalar/logical_not.cpp )
add_unit_test( "core" scalar/is_not_equal.cpp )
add_unit_test( "core" scalar/is_eqz.cpp )
add_unit_test( "core" scalar/is_nez.cpp )
add_unit_test( "core" scalar/bitwise_select.cpp )
add_unit_test( "core" scalar/bitwise_mask.cpp )
add_unit_test( "core" scalar/is_less.cpp )
add_unit_test( "core" scalar/is_greater.cpp )
add_unit_test( "core" scalar/logical_and.cpp )

list_tests("scalar/sub"     "core" ${all_types})
list_tests("scalar/add"     "core" ${all_types})
list_tests("scalar/popcnt"  "core" ${integral_types})

add_unit_test( "core" scalar/inf.cpp )
add_unit_test( "core" scalar/minf.cpp )
add_unit_test( "core" scalar/nan.cpp )
add_unit_test( "core" scalar/mzero.cpp )
add_unit_test( "core" scalar/signmask.cpp )

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
list_tests("simd/is_equal" "core" ${all_types})
list_tests("simd/extract" "core" ${all_types})
list_tests("simd/logical_not" "core" ${all_types})
list_tests("simd/is_not_equal" "core" ${all_types})
list_tests("simd/is_eqz" "core" ${all_types})
list_tests("simd/is_nez" "core" ${all_types})
list_tests("simd/bitwise_select"  "core" ${all_types})
list_tests("simd/bitwise_mask" "core" ${all_types})
list_tests("simd/is_less" "core" ${all_types})
list_tests("simd/is_greater" "core" ${all_types})
list_tests("simd/logical_and" "core" ${all_types})
