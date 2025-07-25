##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_C_COMPILER    gcc-14  )
set(CMAKE_CXX_COMPILER  g++-14  )

# Disable cmake isysroot parameter injection and g++ automatic sysroot detection to avoid SDK conflicts
set(CMAKE_SYSTEM_NAME   Generic )
set(CMAKE_CXX_FLAGS     "-Wno-psabi -nostdinc++ -isystem /opt/homebrew/include/c++/14 -isystem /opt/homebrew/include/c++/14/aarch64-apple-darwin24 -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )
