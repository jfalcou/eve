##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

set(CMAKE_SYSTEM_NAME Linux     )
set(CMAKE_SYSTEM_PROCESSOR arm  )

set(CMAKE_C_COMPILER    arm-linux-gnueabihf-gcc-10  )
set(CMAKE_CXX_COMPILER  arm-linux-gnueabihf-g++-10  )
set(CMAKE_BUILD_TYPE    Debug                       )
set(CMAKE_CXX_FLAGS     "-Wno-psabi -mfpu=neon -march=armv7-a -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}"  )

set(CMAKE_CROSSCOMPILING_CMD ${PROJECT_SOURCE_DIR}/cmake/toolchain/run_arm.sh     )
