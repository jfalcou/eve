##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.18)
project(eve-multi-arch LANGUAGES CXX)

find_package(eve CONFIG REQUIRED)

add_library(setup INTERFACE)
target_link_libraries(setup INTERFACE eve::eve)
target_compile_options(setup INTERFACE "-O3")

eve_build_variants( NAME compute
                    INTERFACE   setup
                    TARGET      basic advanced perfect
                    OPTIONS     "-msse2"  "-msse4.1" "-march=haswell"
                    SOURCES     kernel.cpp
                  )

add_executable(multi-arch main.cpp compute.cpp)
add_dependencies(multi-arch ${eve_compute_variants})
target_link_libraries(multi-arch PUBLIC setup ${CMAKE_DL_LIBS})
