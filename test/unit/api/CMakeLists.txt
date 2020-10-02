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
add_custom_target(unit.api.exe       )
add_custom_target(unit.api.scalar.exe)
add_custom_target(unit.api.simd.exe  )

add_dependencies(unit.scalar.exe    unit.api.scalar.exe )
add_dependencies(unit.simd.exe      unit.api.simd.exe   )
add_dependencies(unit.api.exe       unit.api.scalar.exe )
add_dependencies(unit.api.exe       unit.api.simd.exe   )

##==================================================================================================
## wide API tests
add_subdirectory(wide)

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
## logical API tests
make_all_units(ROOT unit.api      NAME logical  ARCH scalar simd  TYPES ${all_types} )
