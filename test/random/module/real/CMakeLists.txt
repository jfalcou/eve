##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
add_custom_target(random.real.scalar.exe)
add_custom_target(random.real.simd.exe  )
add_dependencies(random.scalar.exe  random.real.scalar.exe )
add_dependencies(random.simd.exe    random.real.simd.exe   )

add_subdirectory(core)
add_subdirectory(math)
add_subdirectory(special)
