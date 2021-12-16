##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
add_custom_target(unit.real.scalar.exe)
add_custom_target(unit.real.simd.exe  )
add_dependencies(unit.scalar.exe  unit.real.scalar.exe )
add_dependencies(unit.simd.exe    unit.real.simd.exe   )

add_subdirectory(algorithm)
add_subdirectory(constant)
add_subdirectory(core)

if(EVE_USE_BOOST)
add_subdirectory(math)
add_subdirectory(special)
add_subdirectory(elliptic)
add_subdirectory(combinatorial)
endif()

add_subdirectory(proba)
