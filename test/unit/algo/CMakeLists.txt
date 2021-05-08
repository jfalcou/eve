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
make_unit("unit.algo" ptr_iterator.cpp)
make_unit("unit.algo" preprocess_range.cpp)
