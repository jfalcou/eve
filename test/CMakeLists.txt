##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Find Boost
##==================================================================================================
find_package(Boost 1.65.0 QUIET)

if(Boost_FOUND)
  set(EVE_USE_BOOST 1)
  message( STATUS "[eve] Boost found in ${Boost_INCLUDE_DIRS} - Boost dependent tests activated")
  string(REPLACE "/usr/include" "" Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
else()
  set(Boost_INCLUDE_DIRS "")
endif()

add_subdirectory(doc)
#add_subdirectory(exhaustive)
#add_subdirectory(random)
add_subdirectory(unit)
