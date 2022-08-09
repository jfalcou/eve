##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_C_COMPILER    gcc  )
set(CMAKE_CXX_COMPILER  g++  )

set(CMAKE_CXX_FLAGS     "-Wno-psabi -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )
