//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup simd
//! @{
//!   @defgroup algorithms Algorithms and Views
//!   @brief Algorithms and Views
//!
//!   This module provides implementation of SIMD versions of some std ranges algorithms.
//!   Take care that some prerequisite and syntaxes are not fully standard conformant
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
#include <eve/module/algo/algo/equal.hpp>
#include <eve/module/algo/algo/fill.hpp>
#include <eve/module/algo/algo/find_last.hpp>
#include <eve/module/algo/algo/find.hpp>
#include <eve/module/algo/algo/for_each_iteration.hpp>
#include <eve/module/algo/algo/for_each_iteration_fixed_overflow.hpp>
#include <eve/module/algo/algo/for_each.hpp>
#include <eve/module/algo/algo/inclusive_scan.hpp>
#include <eve/module/algo/algo/iota.hpp>
#include <eve/module/algo/algo/iterator_helpers.hpp>
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
#include <eve/module/algo/algo/swap_ranges.hpp>
#include <eve/module/algo/algo/traits.hpp>
#include <eve/module/algo/algo/transform_reduce.hpp>
#include <eve/module/algo/algo/transform.hpp>
#include <eve/module/algo/views/backward.hpp>
#include <eve/module/algo/views/convert.hpp>
#include <eve/module/algo/views/iota.hpp>
#include <eve/module/algo/views/map.hpp>
#include <eve/module/algo/views/reverse.hpp>
#include <eve/module/algo/views/zip.hpp>
