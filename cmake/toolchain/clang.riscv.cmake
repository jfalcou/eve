##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_SYSTEM_NAME       Generic)
set(CMAKE_SYSTEM_PROCESSOR  riscv64)

set(CMAKE_C_COMPILER    /opt/llvm/bin/clang)
set(CMAKE_CXX_COMPILER  /opt/llvm/bin/clang++)

set(CMAKE_CXX_FLAGS "-march=rv64gcv --static --target=riscv64-unknown-linux-gnu ${EVE_OPTIONS}" )
set(CMAKE_CROSSCOMPILING_CMD ${PROJECT_SOURCE_DIR}/cmake/toolchain/run_rvv128.sh )
