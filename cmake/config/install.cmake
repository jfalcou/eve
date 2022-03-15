##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

## =================================================================================================
## Install target
## =================================================================================================
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/eve TYPE INCLUDE)

## =================================================================================================
## Exporting target for external use
## =================================================================================================
add_library(eve_lib INTERFACE)
target_include_directories(eve_lib INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_compile_features(eve_lib INTERFACE cxx_std_20)
add_library(eve::eve ALIAS eve_lib)
