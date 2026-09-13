//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup eve_algorithms
//! @{
//!   @defgroup eve_algos Algorithms
//!   @brief SIMD implementations of the standard algorithms.
//!
//!   Each algorithm keeps the name and the meaning of its `std` counterpart, takes ranges, and
//!   calls its operation on SIMD registers. A position comes back as an iterator into the range
//!   given, and a count or a reduction as a value. Where the standard uses one name for the
//!   in-place and the out-of-place forms, this module has two, eve::algo::transform_inplace and
//!   eve::algo::transform_to, because the two loops differ. Every algorithm takes options between
//!   brackets, see @ref eve_algo_traits.
//!
//!   @defgroup eve_views Views
//!   @brief Views that adapt a range for an algorithm without copying it.
//!
//!   A view wraps one or several ranges and presents them as one: eve::algo::views::zip walks
//!   several ranges in step and hands the callable a tuple, eve::algo::views::convert reads a range
//!   as another type, eve::algo::views::reverse walks it backwards, eve::algo::views::map applies a
//!   function on the way in and on the way out, and eve::algo::views::iota is a range of
//!   consecutive values. A view is itself a range an algorithm or another view accepts.
//!
//!   @defgroup eve_algo_concepts Algorithms Concepts
//!   @brief Concepts a range or an iterator satisfies to enter an algorithm, and the types that
//!   model them.
//!
//!   An algorithm accepts a @ref relaxed_range "relaxed_range": a `begin` and an `end` over
//!   contiguous memory, a `std::vector`, a `std::span`, an array, a view of this module, or two
//!   pointers through `eve::algo::as_range`. The relaxed concepts widen the standard ones to what
//!   SIMD needs: an aligned pointer or an `eve::algo::iterator` as iterator, and a
//!   @ref relaxed_sentinel_for "relaxed_sentinel_for" that need not be an iterator of the same
//!   type.
//!
//!   @defgroup eve_algo_traits Options
//!   @brief Options that tune how an algorithm runs.
//! @}
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/algo/algo/concepts/eve_iterator.hpp>
#include <eve/module/algo/algo/concepts/ranges_types.hpp>
#include <eve/module/algo/algo/concepts/nothing.hpp>
#include <eve/module/algo/algo/concepts/relaxed.hpp>
#include <eve/module/algo/algo/concepts/types_to_consider.hpp>
#include <eve/module/algo/algo/concepts/zip_to_range.hpp>
