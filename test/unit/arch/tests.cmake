##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
add_test( NAME unit.arch.arch_includes.cmake
          COMMAND ${CMAKE_COMMAND} -DEVE_ROOT=${PROJECT_SOURCE_DIR} -P ${unit_root}/arch/arch_includes.cmake
        )
