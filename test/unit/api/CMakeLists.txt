##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.api.tst       )
add_custom_target(unit.api.scalar.tst)
add_custom_target(unit.api.simd.tst  )

add_dependencies(unit.scalar.tst    unit.api.scalar.tst )
add_dependencies(unit.simd.tst      unit.api.simd.tst   )
add_dependencies(unit.api.tst       unit.api.scalar.tst )
add_dependencies(unit.api.tst       unit.api.simd.tst   )

##==================================================================================================
## General API tests
make_unit( "unit.api" memory/aligned_alloc.cpp )
make_unit( "unit.api" memory/aligned_allocator.cpp )
make_unit( "unit.api" memory/aligned_ptr.cpp )
make_unit( "unit.api" memory/is_aligned.cpp )

##==================================================================================================
## Function tests
make_units("function/scalar/load/arithmetic"  "unit.api" ${all_types})
make_units("function/scalar/load/logical"     "unit.api" ${all_types})
make_units("function/simd/load/arithmetic"    "unit.api" ${all_types})
make_units("function/simd/load/logical"       "unit.api" ${all_types})
make_units("function/simd/store/arithmetic"   "unit.api" ${all_types})
make_units("function/simd/store/logical"      "unit.api" ${all_types})

##==================================================================================================
## Constant tests
make_unit( "unit.api" constant/constant.cpp )

##==================================================================================================
## wide API tests
make_units("wide/combine/arithmetic"    "unit.api" ${all_types})
make_units("wide/decrement/arithmetic"  "unit.api" ${all_types})
make_units("wide/increment/arithmetic"  "unit.api" ${all_types})
make_units("wide/load/arithmetic"       "unit.api" ${all_types})
make_units("wide/make/arithmetic"       "unit.api" ${all_types})
make_units("wide/slice/arithmetic"      "unit.api" ${all_types})
make_units("wide/splat/arithmetic"      "unit.api" ${all_types})

check_failures("wide/decrement/logical" "unit.api" ${all_types})
check_failures("wide/increment/logical" "unit.api" ${all_types})
make_units      ("wide/combine/logical"   "unit.api" ${all_types})
make_units      ("wide/load/logical"      "unit.api" ${all_types})
make_units      ("wide/make/logical"      "unit.api" ${all_types})
make_units      ("wide/slice/logical"     "unit.api" ${all_types})
make_units      ("wide/splat/logical"     "unit.api" ${all_types})

make_unit( "unit.api" wide/std.cpp )

##==================================================================================================
## logical API tests
make_all_units(ROOT unit.api NAME logical ARCH scalar simd TYPES ${all_types} )
