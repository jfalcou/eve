##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_C_COMPILER    gcc-14  )
set(CMAKE_CXX_COMPILER  g++-14  )

set(CMAKE_CXX_FLAGS     "-Wno-psabi ${EVE_OPTIONS}" )
set(CMAKE_CROSSCOMPILING_CMD ${PROJECT_SOURCE_DIR}/cmake/toolchain/run_x86_spr.sh )
