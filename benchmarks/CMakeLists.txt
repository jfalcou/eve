##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(benchmark)

add_subdirectory(module/bessel)
add_subdirectory(module/polynomial)

add_subdirectory(module/algorithm)
add_subdirectory(module/core)
add_subdirectory(module/math)
add_subdirectory(module/special)
add_subdirectory(module/combinatorial)
