##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Reuse install.cmake to preapre package properly
##==================================================================================================
include("${CMAKE_CURRENT_LIST_DIR}/eve-targets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/eve-multiarch.cmake")
set(EVE_LIBRARIES eve::eve)
