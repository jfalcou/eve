##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(random_root "${CMAKE_SOURCE_DIR}/test/random/module")

##==================================================================================================
## GLOB and process core random tests
##==================================================================================================
add_custom_target(random.core.exe           )
add_dependencies(random.exe random.core.exe )
glob_unit("random" ${random_root} "module/" "module/core/*.cpp")

##==================================================================================================
## GLOB and process math random tests
##==================================================================================================
add_custom_target(random.math.exe           )
add_dependencies(random.exe random.math.exe )
glob_unit("random" ${random_root} "module/" "module/math/*.cpp")
