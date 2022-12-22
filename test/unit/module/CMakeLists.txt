##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

## Modules
add_subdirectory(algo)
add_subdirectory(core)
add_subdirectory(complex)

if(EVE_USE_BOOST)
add_subdirectory(bessel)
add_subdirectory(combinatorial)
add_subdirectory(elliptic)
add_subdirectory(math)
add_subdirectory(polynomial)
add_subdirectory(special)
endif()
