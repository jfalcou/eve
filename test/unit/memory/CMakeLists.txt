##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.memory.exe       )
add_custom_target(unit.memory.scalar.exe)
add_custom_target(unit.memory.simd.exe  )

add_dependencies(unit.scalar.exe  unit.memory.scalar.exe)
add_dependencies(unit.simd.exe    unit.memory.simd.exe  )
add_dependencies(unit.memory.exe  unit.memory.scalar.exe)
add_dependencies(unit.memory.exe  unit.memory.simd.exe  )

##==================================================================================================
## Memory API tests
make_unit( "unit.memory" aligned_alloc.cpp )
make_unit( "unit.memory" aligned_allocator.cpp )
make_unit( "unit.memory" aligned_ptr.cpp )
make_unit( "unit.memory" is_aligned.cpp )
make_unit( "unit.memory" store.cpp )

# make_all_units(ROOT unit.api  NAME load       ARCH simd TYPES ${all_types} )
