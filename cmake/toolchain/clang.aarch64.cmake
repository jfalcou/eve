##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux     )
set(CMAKE_SYSTEM_PROCESSOR arm  )

set(CMAKE_C_COMPILER    clang   )
set(CMAKE_CXX_COMPILER  clang++ )

set(CMAKE_CXX_FLAGS     "-target aarch64-linux-gnu -march=armv8-a -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )

set(CMAKE_CROSSCOMPILING_CMD qemu-aarch64)
