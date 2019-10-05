##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## General API tests
make_unit( "api" memory/aligned_alloc.cpp )
make_unit( "api" memory/aligned_allocator.cpp )
make_unit( "api" memory/aligned_ptr.cpp )
make_unit( "api" memory/is_aligned.cpp )

##==================================================================================================
## Function tests
make_units("function/scalar/load/arithmetic"  "api" ${all_types})
make_units("function/scalar/load/logical"     "api" ${all_types})
make_units("function/simd/load/arithmetic"    "api" ${all_types})
make_units("function/simd/load/logical"       "api" ${all_types})
make_units("function/simd/store/arithmetic"   "api" ${all_types})
make_units("function/simd/store/logical"      "api" ${all_types})

##==================================================================================================
## Constant tests
make_unit( "api" constant/constant.cpp )

##==================================================================================================
## wide API tests
make_units("wide/combine/arithmetic"    "api" ${all_types})
make_units("wide/decrement/arithmetic"  "api" ${all_types})
make_units("wide/increment/arithmetic"  "api" ${all_types})
make_units("wide/load/arithmetic"       "api" ${all_types})
make_units("wide/make/arithmetic"       "api" ${all_types})
make_units("wide/slice/arithmetic"      "api" ${all_types})
make_units("wide/splat/arithmetic"      "api" ${all_types})

check_failures("wide/decrement/logical" "api" ${all_types})
check_failures("wide/increment/logical" "api" ${all_types})
make_units      ("wide/combine/logical"   "api" ${all_types})
make_units      ("wide/load/logical"      "api" ${all_types})
make_units      ("wide/make/logical"      "api" ${all_types})
make_units      ("wide/slice/logical"     "api" ${all_types})
make_units      ("wide/splat/logical"     "api" ${all_types})

make_unit( "api" wide/std.cpp )

##==================================================================================================
## logical API tests
make_units("logical"   "api" ${all_types})
