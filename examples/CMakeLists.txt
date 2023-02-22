##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(examples_root "${PROJECT_SOURCE_DIR}/examples")

##==================================================================================================
## GLOB and process regular examples tests
##==================================================================================================
add_custom_target(examples.exe         )
add_dependencies(examples.exe unit.api.exe )
glob_unit("examples" ${examples_root} "*.cpp")
glob_unit("examples" ${examples_root} "algorithms/writing_new/*.cpp")
glob_unit("examples" ${examples_root} "oop/*.cpp")
glob_unit("examples" ${examples_root} "quick-start/*.cpp")
glob_unit("examples" ${examples_root} "tutorial/*.cpp")

##==================================================================================================
## GLOB and process examples tests with finer needs
##==================================================================================================
make_unit( "examples" algorithms/using_existing/memcmp__two_range_algorithms_interface_specifics.cpp )
make_unit( "examples" algorithms/using_existing/inclusive_scan_zip__using_zip_with_algorithms.cpp )
make_unit( "examples" algorithms/using_existing/case_insensitive_equals.cpp )
make_unit( "examples" algorithms/using_existing/combining_zip_map_and_algos.cpp )
make_unit( "examples" algorithms/using_existing/linspace.cpp )

find_package(Threads REQUIRED)
make_unit( "examples" algorithms/using_existing/inclusive_scan_par_unseq.cpp )
target_link_libraries(examples.algorithms.using_existing.inclusive_scan_par_unseq.exe PRIVATE Threads::Threads)
