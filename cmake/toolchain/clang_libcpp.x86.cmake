##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_C_COMPILER    clang   )
set(CMAKE_CXX_COMPILER  clang++ )

set(CMAKE_CXX_FLAGS         "-stdlib=libc++ -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )
set(CMAKE_EXE_LINKER_FLAGS  "-stdlib=libc++")
