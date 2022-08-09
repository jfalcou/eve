##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_C_COMPILER    clang   )
set(CMAKE_CXX_COMPILER  clang++ )
set(CMAKE_BUILD_TYPE    Debug   )

set(CMAKE_CXX_FLAGS        "-DEVE_NO_FORCEINLINE -fsanitize=address ${EVE_OPTIONS}")
set(CMAKE_EXE_LINKER_FLAGS "-fsanitize=address")
