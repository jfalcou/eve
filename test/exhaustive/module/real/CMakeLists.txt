##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0-1.0
##==================================================================================================
add_custom_target(exhaustive.real.scalar.exe)
add_custom_target(exhaustive.real.simd.exe  )
add_dependencies(exhaustive.scalar.exe  exhaustive.real.scalar.exe )
add_dependencies(exhaustive.simd.exe    exhaustive.real.simd.exe   )

add_subdirectory(core)
add_subdirectory(math)
add_subdirectory(special)
