##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

set(CMAKE_SYSTEM_NAME Linux         )
set(CMAKE_SYSTEM_PROCESSOR powerpc  )

set(CMAKE_C_COMPILER    powerpc64-linux-gnu-gcc-10  )
set(CMAKE_CXX_COMPILER  powerpc64-linux-gnu-g++-10  )
set(CMAKE_BUILD_TYPE    Debug                       )
set(CMAKE_CXX_FLAGS     "-static -mpower8-vector -mvsx -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )

set(CMAKE_CROSSCOMPILING_CMD qemu-ppc64)
