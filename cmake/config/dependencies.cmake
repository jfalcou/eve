##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Find Boost
##==================================================================================================
find_package(Boost 1.74.0 QUIET)

if(Boost_FOUND)
  message( STATUS "[eve] Boost found in ${Boost_INCLUDE_DIRS} - Boost dependent tests activated")
else()
  set(Boost_INCLUDE_DIRS "")
endif()
