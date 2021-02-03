##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018-2021 Joel FALCOU
##  Copyright 2018-2021 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_SYSTEM_NAME       Linux   )
set(CMAKE_SYSTEM_PROCESSOR  powerpc )

set(CMAKE_SYSROOT       /usr/powerpc64le-linux-gnu/ )
set(CMAKE_C_COMPILER    clang-10                    )
set(CMAKE_CXX_COMPILER  clang++-10                  )
set(CMAKE_BUILD_TYPE    Release                     )

set(CMAKE_CXX_FLAGS         "--target=powerpc64le-linux-gnu  -I/usr/powerpc64le-linux-gnu/include/c++/10/powerpc64le-linux-gnu" )
set(CMAKE_EXE_LINKER_FLAGS  "-fuse-ld=lld")
set(CMAKE_CROSSCOMPILING_CMD qemu-ppc64le)
