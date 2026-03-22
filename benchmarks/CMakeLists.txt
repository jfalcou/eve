##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
include(target/generate_benchmark)

set(bench_root "${PROJECT_SOURCE_DIR}/benchmarks")

##==================================================================================================
## GLOB and process arch bench tests
##==================================================================================================
add_custom_target(bench.core.exe         )
add_dependencies(bench.exe bench.core.exe )
glob_bench("bench" ${bench_root} "core/*.cpp")