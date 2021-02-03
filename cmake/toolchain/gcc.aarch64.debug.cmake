##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018-2021 Joel FALCOU
##  Copyright 2018-2021 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux     )
set(CMAKE_SYSTEM_PROCESSOR arm  )

set(CMAKE_C_COMPILER    aarch64-linux-gnu-gcc-10  )
set(CMAKE_CXX_COMPILER  aarch64-linux-gnu-g++-10  )
set(CMAKE_BUILD_TYPE    Debug                     )

set(CMAKE_CROSSCOMPILING_CMD qemu-aarch64)
