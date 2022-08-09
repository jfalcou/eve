##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_C_COMPILER    gcc-12  )
set(CMAKE_CXX_COMPILER  g++-12  )

set(CMAKE_CXX_FLAGS     "-DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )
