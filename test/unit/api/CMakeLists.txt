##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
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
## Wide API tests
make_unit("unit.api"  arithmetic.cpp  )
make_unit("unit.api"  bitwise.cpp     )
make_unit("unit.api"  comparisons.cpp )
make_unit("unit.api"  shift.cpp       )
make_unit("unit.api"  wide.cpp        )

##==================================================================================================
## logical API tests
make_all_units(ROOT unit.api      NAME logical  ARCH scalar simd  TYPES ${all_types} )

##==================================================================================================
## Wide related tools
make_unit( "unit.api" conditional.cpp )
make_unit( "unit.api" replace.cpp     )
make_unit( "unit.api" pattern.cpp     )

##==================================================================================================
## Memory API tests
make_unit( "unit.api" memory/aligned_alloc.cpp )
make_unit( "unit.api" memory/aligned_allocator.cpp )
make_unit( "unit.api" memory/aligned_ptr.cpp )
make_unit( "unit.api" memory/is_aligned.cpp )
