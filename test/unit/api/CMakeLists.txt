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

##==================================================================================================
## pack API tests
list_tests("pack/combine"   "api" ${all_types})
list_tests("pack/decrement" "api" ${all_types})
list_tests("pack/increment" "api" ${all_types})
list_tests("pack/load"      "api" ${all_types})
list_tests("pack/make"      "api" ${all_types})
list_tests("pack/slice"     "api" ${all_types})
list_tests("pack/splat"     "api" ${all_types})
