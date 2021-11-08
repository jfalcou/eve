##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_C_COMPILER    clang   )
set(CMAKE_CXX_COMPILER  clang++ )

set(CMAKE_CXX_FLAGS         "-stdlib=libc++ -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )
set(CMAKE_EXE_LINKER_FLAGS  "-stdlib=libc++")
