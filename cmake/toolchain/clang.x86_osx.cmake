##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_C_COMPILER    /usr/local/opt/llvm/bin/clang   )
set(CMAKE_CXX_COMPILER  /usr/local/opt/llvm/bin/clang++ )

set(CMAKE_CXX_FLAGS     "-DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )
