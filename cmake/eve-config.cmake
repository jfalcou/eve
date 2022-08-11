##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Reuse install.cmake to preapre package properly
##==================================================================================================
include("${CMAKE_CURRENT_LIST_DIR}/eve-targets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/eve-multiarch.cmake")
set(EVE_LIBRARIES eve::eve)
