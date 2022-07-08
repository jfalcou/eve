##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.19)
project(eve-multi-arch LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "/usr/local/lib")
find_package(eve)

eve_build_variants( NAME compute
                    INTERFACE   ${EVE_LIBRARIES}
                    TARGET      sse2 sse4 haswell
                    OPTIONS     "-msse2"  "-msse4.1" "-mavx2"
                    SOURCES     kernel.cpp
                  )

add_executable(multi-arch main.cpp compute.cpp)
add_dependencies(multi-arch ${eve_compute_variants})
target_link_libraries(multi-arch PUBLIC ${EVE_LIBRARIES})

