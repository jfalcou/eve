##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
include(test)

add_subdirectory(doc)
# add_subdirectory(exhaustive)

if( EVE_BUILD_RANDOM )
  add_subdirectory(random)
endif()

add_subdirectory(unit)
