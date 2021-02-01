##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry LAPRESTE
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

make_unit( "unit.api" conditional.cpp  )

##==================================================================================================
## wide API tests
add_subdirectory(wide)
add_subdirectory(arithmetic)
add_subdirectory(bitwise)
add_subdirectory(comparisons)

##==================================================================================================
## General API tests
make_unit( "unit.api" memory/aligned_alloc.cpp )
make_unit( "unit.api" memory/aligned_allocator.cpp )
make_unit( "unit.api" memory/aligned_ptr.cpp )
make_unit( "unit.api" memory/is_aligned.cpp )

##==================================================================================================
## Function tests
make_all_units(ROOT unit.api  NAME function/load  ARCH scalar simd TYPES ${all_types} )

##==================================================================================================
## logical API tests
make_all_units(ROOT unit.api      NAME logical  ARCH scalar simd  TYPES ${all_types} )
