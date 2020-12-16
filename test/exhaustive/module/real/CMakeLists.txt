##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(exhaustive.real.scalar.exe)
add_custom_target(exhaustive.real.simd.exe  )
add_dependencies(exhaustive.scalar.exe  exhaustive.real.scalar.exe )
add_dependencies(exhaustive.simd.exe    exhaustive.real.simd.exe   )

add_subdirectory(algorithm)
add_subdirectory(core)
add_subdirectory(math)
add_subdirectory(special)
