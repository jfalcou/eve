##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.algo.exe )

##==================================================================================================
## ALGO tests

# Components
make_unit("unit.algo" array_utils.cpp)
make_unit("unit.algo" concepts.cpp)
make_unit("unit.algo" for_each_iteration.cpp)
make_unit("unit.algo" preprocess_range.cpp)
make_unit("unit.algo" ptr_iterator.cpp)
make_unit("unit.algo" range_ref.cpp)
make_unit("unit.algo" traits.cpp)

# Containers
make_unit( "unit.algo" container/erase_remove.cpp )
make_unit( "unit.algo" container/soa_vector.cpp )
make_unit( "unit.algo" container/soa_vector2.cpp )
make_unit( "unit.algo" container/transform_points_into_lines.cpp )

# Algorithms
# find like -------------
make_unit("unit.algo" algorithm/all_of_generic.cpp)
make_unit("unit.algo" algorithm/any_of_generic.cpp)
make_unit("unit.algo" algorithm/none_of_generic.cpp)

make_unit("unit.algo" algorithm/find_if_generic.cpp)
make_unit("unit.algo" algorithm/find_if_not_generic.cpp)

make_unit("unit.algo" algorithm/equal_generic.cpp)
make_unit("unit.algo" algorithm/mismatch_generic.cpp)

make_unit("unit.algo" algorithm/find_like_special_cases.cpp)

# sums ------------------
make_unit("unit.algo" algorithm/inclusive_scan_inplace_generic.cpp)
make_unit("unit.algo" algorithm/inclusive_scan_to_generic.cpp)
make_unit("unit.algo" algorithm/reduce_generic.cpp)
make_unit("unit.algo" algorithm/sums_special_cases.cpp)

# shuffles
make_unit("unit.algo" algorithm/remove.cpp)
make_unit("unit.algo" algorithm/reverse_generic.cpp)

# transform
make_unit("unit.algo" algorithm/transform_inplace_generic.cpp)
make_unit("unit.algo" algorithm/transform_to_generic.cpp)
make_unit("unit.algo" algorithm/transform_special_cases.cpp)
make_unit("unit.algo" algorithm/iota_generic.cpp)
make_unit("unit.algo" algorithm/fill_generic.cpp)

# copy
make_unit("unit.algo" algorithm/copy_back.cpp)
make_unit("unit.algo" algorithm/copy_backward_generic.cpp)
make_unit("unit.algo" algorithm/copy_fwd.cpp)
make_unit("unit.algo" algorithm/copy_generic.cpp)
make_unit("unit.algo" algorithm/reverse_copy_generic.cpp)
make_unit("unit.algo" algorithm/swap_ranges_generic.cpp)
