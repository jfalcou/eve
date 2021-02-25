##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.internals.exe       )
add_custom_target(unit.internals.scalar.exe)
add_custom_target(unit.internals.simd.exe  )

add_dependencies(unit.scalar.exe    unit.internals.scalar.exe )
add_dependencies(unit.simd.exe      unit.internals.simd.exe   )
add_dependencies(unit.internals.exe unit.internals.scalar.exe )
add_dependencies(unit.internals.exe unit.internals.simd.exe   )

add_dependencies(unit.scalar.exe    unit.internals.scalar.exe )
add_dependencies(unit.simd.exe      unit.internals.simd.exe   )
add_dependencies(unit.internals.exe unit.internals.scalar.exe )
add_dependencies(unit.internals.exe unit.internals.simd.exe   )

make_all_units(ROOT unit.internals  NAME to_logical ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.internals  NAME top_bits ARCH simd TYPES ${all_types} )
