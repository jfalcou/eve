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
list_tests("function/scalar/load/arithmetic"  "api" ${all_types})
list_tests("function/scalar/load/logical"     "api" ${all_types})
list_tests("function/simd/load/arithmetic"    "api" ${all_types})
list_tests("function/simd/load/logical"       "api" ${all_types})
list_tests("function/simd/store/arithmetic"   "api" ${all_types})
list_tests("function/simd/store/logical"      "api" ${all_types})

##==================================================================================================
## Constant tests
add_unit_test( "api" constant/constant.cpp )

##==================================================================================================
## wide API tests
list_tests("wide/combine/arithmetic"    "api" ${all_types})
list_tests("wide/decrement/arithmetic"  "api" ${all_types})
list_tests("wide/increment/arithmetic"  "api" ${all_types})
list_tests("wide/load/arithmetic"       "api" ${all_types})
list_tests("wide/make/arithmetic"       "api" ${all_types})
list_tests("wide/slice/arithmetic"      "api" ${all_types})
list_tests("wide/splat/arithmetic"      "api" ${all_types})

list_build_tests("wide/decrement/logical" "api" ${all_types})
list_build_tests("wide/increment/logical" "api" ${all_types})
list_tests      ("wide/combine/logical"   "api" ${all_types})
list_tests      ("wide/load/logical"      "api" ${all_types})
list_tests      ("wide/make/logical"      "api" ${all_types})
list_tests      ("wide/slice/logical"     "api" ${all_types})
list_tests      ("wide/splat/logical"     "api" ${all_types})

add_unit_test( "api" wide/std.cpp )

##==================================================================================================
## logical API tests
list_tests("logical"   "api" ${all_types})
