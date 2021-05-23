##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

set(CMAKE_C_COMPILER    gcc-11  )
set(CMAKE_CXX_COMPILER  g++-11  )
set(CMAKE_BUILD_TYPE    Debug   )

set(CMAKE_CXX_FLAGS     "-Wno-psabi -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )
