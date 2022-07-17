##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Reuse install.cmake to preapre package properly
##==================================================================================================
get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/eve-targets.cmake)
include(${SELF_DIR}/eve-multiarch.cmake)
set(EVE_LIBRARIES eve::eve)
