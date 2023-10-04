##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv64)

set(CMAKE_C_COMPILER   	clang  )
set(CMAKE_CXX_COMPILER  clang++  )


if(NOT DEFINED ENV{RISCV_GCC})
  message(FATAL_ERROR "expected to have RISCV_GCC in environment")
endif()

set(CMAKE_CXX_FLAGS "-O3 -march=rv64gcv -std=c++20 -mrvv-vector-bits=128 --sysroot=$ENV{RISCV_GCC}/sysroot --gcc-toolchain=$ENV{RISCV_GCC} --static --target=riscv64-unknown-linux-gnu ${EVE_OPTIONS}" )

set(CMAKE_CROSSCOMPILING_CMD ${PROJECT_SOURCE_DIR}/cmake/toolchain/run_rvv128.sh )
