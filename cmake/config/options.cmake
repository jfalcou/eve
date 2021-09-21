##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

## =================================================================================================
## Handle options
## =================================================================================================
option( EVE_USE_PCH             "Build unit tests with precompield headers"     ON  )
option( EVE_BUILD_TEST          "Build unit tests for eve"                      ON  )
option( EVE_BUILD_RANDOM        "Build random precision tests for eve"          OFF )
option( EVE_BUILD_BENCHMARKS    "Build benchmarks for eve"                      OFF )
option( EVE_BUILD_SRC_HTML      "Convert source to html for eve documentation"  OFF )
option( EVE_BUILD_DOCUMENTATION "Compile Doxygen documentation"                 ON  )

if( EVE_USE_PCH )
  set(pch_status "ON")
else()
  set(pch_status "OFF")
endif()

if( EVE_BUILD_TEST )
  set(test_status "ON")
else()
  set(test_status "OFF")
endif()

if( EVE_BUILD_RANDOM )
  set(random_status "ON")
else()
  set(random_status "OFF")
endif()

if( EVE_BUILD_BENCHMARKS )
  set(bench_status "ON")
else()
  set(bench_status "OFF")
endif()

if( EVE_BUILD_SRC_HTML )
  set(html_status "ON")
else()
  set(html_status "OFF")
endif()

message( STATUS "[eve] Building ${CMAKE_BUILD_TYPE} mode with: ${CMAKE_CXX_FLAGS}"      )
message( STATUS "[eve] Use PCH            : ${pch_status} (via EVE_USE_PCH)"            )
message( STATUS "[eve] Unit tests         : ${test_status} (via EVE_BUILD_TEST)"        )
message( STATUS "[eve] Random tests       : ${random_status} (via EVE_BUILD_RANDOM)"    )
message( STATUS "[eve] Benchmarks tests   : ${bench_status} (via EVE_BUILD_BENCHMARKS)" )
message( STATUS "[eve] Source generation  : ${html_status} (via EVE_BUILD_SRC_HTML)"    )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
