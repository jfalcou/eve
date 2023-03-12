##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux         )
set(CMAKE_SYSTEM_PROCESSOR powerpc  )

set(CMAKE_C_COMPILER    powerpc64-linux-gnu-gcc-12  )
set(CMAKE_CXX_COMPILER  powerpc64-linux-gnu-g++-12  )
set(CMAKE_CXX_FLAGS     "-static -mpower8-vector -mvsx -DEVE_NO_FORCEINLINE -DNO_WARN_X86_INTRINSICS ${EVE_OPTIONS}" )

set(CMAKE_CROSSCOMPILING_CMD qemu-ppc64)
