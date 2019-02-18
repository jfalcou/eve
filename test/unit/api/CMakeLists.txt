##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## General API tests
add_unit_test( "api" memory/aligned_alloc.cpp )
add_unit_test( "api" memory/aligned_allocator.cpp )
add_unit_test( "api" memory/aligned_ptr.cpp )
add_unit_test( "api" memory/is_aligned.cpp )

##==================================================================================================
## Function tests
list_tests("function/scalar/load"  "api" ${all_types})
list_tests("function/simd/load"    "api" ${all_types})
list_tests("function/simd/store"   "api" ${all_types})

##==================================================================================================
## Constant tests
add_unit_test( "api" constant/constant.cpp )

##==================================================================================================
## wide API tests
list_tests("wide/combine"   "api" ${all_types})
list_tests("wide/decrement" "api" ${all_types})
list_tests("wide/increment" "api" ${all_types})
list_tests("wide/load"      "api" ${all_types})
list_tests("wide/make"      "api" ${all_types})
list_tests("wide/slice"     "api" ${all_types})
list_tests("wide/splat"     "api" ${all_types})
