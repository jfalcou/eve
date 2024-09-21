##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_SYSTEM_PROCESSOR arm  )

set(CMAKE_C_COMPILER    /opt/homebrew/opt/llvm@15/bin/clang   )
set(CMAKE_CXX_COMPILER  /opt/homebrew/opt/llvm@15/bin/clang++ )

set(CMAKE_CXX_FLAGS     "--target=arm-linux-gnueabihf -mfpu=neon-vfpv4 -march=armv7-a -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )
