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
# Helpers
make_unit("unit.algo" preprocess_range.cpp)
make_unit("unit.algo" ptr_iterator.cpp)

# Algorithms
make_unit("unit.algo" any_of.cpp)
