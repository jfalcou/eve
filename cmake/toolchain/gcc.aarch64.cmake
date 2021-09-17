##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux     )
set(CMAKE_SYSTEM_PROCESSOR arm  )

set(CMAKE_C_COMPILER    aarch64-linux-gnu-gcc  )
set(CMAKE_CXX_COMPILER  aarch64-linux-gnu-g++  )

set(CMAKE_CXX_FLAGS     "-Wno-psabi -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )

set(CMAKE_CROSSCOMPILING_CMD qemu-aarch64)
