//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup eve_simd
//! @{
//!   @defgroup eve_algorithms Algorithms and Views
//!   @brief SIMD versions of the standard range-based algorithms.
//!
//!   An algorithm of this module processes its data with SIMD operations, through eve::wide, with
//!   the loop, the alignment and the tail handled by the library. A call looks like its
//!   `std::ranges` counterpart, and the callable receives SIMD values in place of scalars:
//!
//!   @code
//!   std::vector<float> in(1024), out(1024);
//!   eve::algo::transform_to(in, out, [](auto x) { return x * x; });
//!   @endcode
//!
//!   Two things differ from the standard:
//!
//!   - an algorithm takes ranges, never an iterator pair, which `eve::algo::as_range` turns into
//!     a range;
//!   - the callable is called on eve::wide values of any cardinal, so it is written for a SIMD
//!     value and never for a scalar alone.
//!
//!   **Required header:** @code{.cpp} #include <eve/module/algo.hpp> @endcode
//! @}
//==================================================================================================
#include <eve/module/algo/algo/all_of.hpp>
#include <eve/module/algo/algo/any_of.hpp>
#include <eve/module/algo/algo/array_utils.hpp>
#include <eve/module/algo/algo/as_range.hpp>
#include <eve/module/algo/algo/common_forceinline_lambdas.hpp>
#include <eve/module/algo/algo/concepts.hpp>
#include <eve/module/algo/algo/container/soa_vector.hpp>
#include <eve/module/algo/algo/copy.hpp>
#include <eve/module/algo/algo/copy_if.hpp>
#include <eve/module/algo/algo/count_if.hpp>
#include <eve/module/algo/algo/equal.hpp>
#include <eve/module/algo/algo/fill.hpp>
#include <eve/module/algo/algo/find_last.hpp>
#include <eve/module/algo/algo/find.hpp>
#include <eve/module/algo/algo/for_each_iteration_fixed_overflow.hpp>
#include <eve/module/algo/algo/for_each_iteration_with_expensive_optional_part.hpp>
#include <eve/module/algo/algo/for_each_iteration.hpp>
#include <eve/module/algo/algo/for_each_selected.hpp>
#include <eve/module/algo/algo/for_each.hpp>
#include <eve/module/algo/algo/inclusive_scan.hpp>
#include <eve/module/algo/algo/iota.hpp>
#include <eve/module/algo/algo/iterator_helpers.hpp>
#include <eve/module/algo/algo/keep_if.hpp>
#include <eve/module/algo/algo/max_element.hpp>
#include <eve/module/algo/algo/max_value.hpp>
#include <eve/module/algo/algo/min_element.hpp>
#include <eve/module/algo/algo/min_value.hpp>
#include <eve/module/algo/algo/mismatch.hpp>
#include <eve/module/algo/algo/none_of.hpp>
#include <eve/module/algo/algo/preprocess_range.hpp>
#include <eve/module/algo/algo/ptr_iterator.hpp>
#include <eve/module/algo/algo/range_ref.hpp>
#include <eve/module/algo/algo/reduce.hpp>
#include <eve/module/algo/algo/remove.hpp>
#include <eve/module/algo/algo/reverse.hpp>
#include <eve/module/algo/algo/search.hpp>
#include <eve/module/algo/algo/set_intersection.hpp>
#include <eve/module/algo/algo/swap_ranges.hpp>
#include <eve/module/algo/algo/traits.hpp>
#include <eve/module/algo/algo/transform.hpp>
#include <eve/module/algo/algo/transform_copy_if.hpp>
#include <eve/module/algo/algo/transform_keep_if.hpp>
#include <eve/module/algo/algo/transform_reduce.hpp>
#include <eve/module/algo/algo/two_stage_iteration.hpp>
#include <eve/module/algo/views/backward.hpp>
#include <eve/module/algo/views/convert.hpp>
#include <eve/module/algo/views/iota.hpp>
#include <eve/module/algo/views/map.hpp>
#include <eve/module/algo/views/reverse.hpp>
#include <eve/module/algo/views/zip.hpp>
