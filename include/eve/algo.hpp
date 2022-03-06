//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup functions
//! @{
//! @defgroup bessel Bessel function
//! @brief Bessel functions
//!
//! This module provides implementation for the
//! [Bessel functions](https://en.wikipedia.org/wiki/Bessel_function) and related operations.
//!
//! **Required header:** @code{.cpp} #include <eve/module/bessel.hpp> @endcode
//!
//! @}
//==================================================================================================

#include <eve/algo/all_of.hpp>
#include <eve/algo/any_of.hpp>
#include <eve/algo/array_utils.hpp>
#include <eve/algo/as_range.hpp>
#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/copy.hpp>
#include <eve/algo/equal.hpp>
#include <eve/algo/fill.hpp>
#include <eve/algo/find.hpp>
#include <eve/algo/for_each.hpp>
#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/inclusive_scan.hpp>
#include <eve/algo/iota.hpp>
#include <eve/algo/iterator_helpers.hpp>
#include <eve/algo/mismatch.hpp>
#include <eve/algo/none_of.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/ptr_iterator.hpp>
#include <eve/algo/range_ref.hpp>
#include <eve/algo/reduce.hpp>
#include <eve/algo/remove.hpp>
#include <eve/algo/reverse.hpp>
#include <eve/algo/swap_ranges.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/transform.hpp>
#include <eve/views/backward.hpp>
#include <eve/views/convert.hpp>
#include <eve/views/iota.hpp>
#include <eve/views/map.hpp>
#include <eve/views/reverse.hpp>
#include <eve/views/zip.hpp>
