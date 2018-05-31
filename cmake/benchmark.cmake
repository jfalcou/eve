## -------------------------------------------------------------------------------------------------
##                              Copyright 2018 Joel FALCOU
##
##            Adapted from https://github.com/Crascit/DownloadProject/blob/master/CMakeLists.txt
##
##                   Distributed under the Boost Software License, Version 1.0.
##                        See accompanying file LICENSE.txt or copy at
##                            http://www.boost.org/LICENSE_1_0.txt
## -------------------------------------------------------------------------------------------------

include(download)

## Disable testing GBench
set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "")

download_project( PROJ                googlebenchmark
                  GIT_REPOSITORY      https://github.com/google/benchmark.git
                  GIT_TAG             master
                  "UPDATE_DISCONNECTED 1"
                  QUIET
                )

add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR})
include_directories("${googlebenchmark_SOURCE_DIR}/include")

## Setup our benchmarks
add_custom_target(bench)
#add_subdirectory(${PROJECT_SOURCE_DIR}/benchmark/)
