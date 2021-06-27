##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.algo.exe       )
add_custom_target(unit.algo.simd.exe  )

##==================================================================================================
## ALGO tests

# Components
make_unit("unit.algo" array_utils.cpp)
make_unit("unit.algo" converting_iterator.cpp)
make_unit("unit.algo" one_range_algorithm_adapter.cpp)
make_unit("unit.algo" preprocess_range.cpp)
make_unit("unit.algo" ptr_iterator.cpp)
make_unit("unit.algo" traits.cpp)
make_unit("unit.algo" for_each_iteration.cpp)

# Algorithms
make_unit("unit.algo" any_of.cpp)
make_unit("unit.algo" find.cpp)
