##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

set(CMAKE_C_COMPILER    clang-10   )
set(CMAKE_CXX_COMPILER  clang++-10 )
set(CMAKE_BUILD_TYPE    Debug      )

set(CMAKE_CXX_FLAGS     "-DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )
set(CMAKE_CROSSCOMPILING_CMD ${PROJECT_SOURCE_DIR}/cmake/toolchain/run_x86_sde.sh     )
