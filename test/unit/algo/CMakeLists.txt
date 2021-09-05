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
make_unit("unit.algo" concepts.cpp)
make_unit("unit.algo" convert.cpp)
make_unit("unit.algo" converting_eve_iterator.cpp)
make_unit("unit.algo" for_each_iteration.cpp)
make_unit("unit.algo" preprocess_range.cpp)
make_unit("unit.algo" preprocess_zip_range.cpp)
make_unit("unit.algo" ptr_iterator.cpp)
make_unit("unit.algo" range_ref.cpp)
make_unit("unit.algo" traits.cpp)
make_unit("unit.algo" unalign.cpp)
make_unit("unit.algo" zip_iterator.cpp)
make_unit("unit.algo" zip.cpp)

# Algorithms
make_unit("unit.algo" all_of.cpp)
make_unit("unit.algo" any_of.cpp)
make_unit("unit.algo" find.cpp)
make_unit("unit.algo" mismatch.cpp)
make_unit("unit.algo" find_like_special_cases.cpp)

make_unit("unit.algo" reduce.cpp)
make_unit("unit.algo" remove.cpp)
