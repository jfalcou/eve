##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_SYSTEM_NAME       Linux   )
set(CMAKE_SYSTEM_PROCESSOR  powerpc )

set(CMAKE_SYSROOT       /usr/powerpc64le-linux-gnu/ )
set(CMAKE_C_COMPILER    clang-12                    )
set(CMAKE_CXX_COMPILER  clang++-12                  )
set(CMAKE_BUILD_TYPE    Debug                       )

set(CMAKE_CXX_FLAGS         "-DEVE_NO_FORCEINLINE ${EVE_OPTIONS} --target=powerpc64le-linux-gnu  -I/usr/powerpc64le-linux-gnu/include/c++/10/powerpc64le-linux-gnu" )
set(CMAKE_EXE_LINKER_FLAGS  "-fuse-ld=lld")
set(CMAKE_CROSSCOMPILING_CMD qemu-ppc64le)
