//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <iterator>

namespace eve::algo
{

//================================================================================================
//! @addtogroup algo_concepts
//! @{
//!    @typedef iterator for a relaxed range
//!
//!    @tparam R - relaxed range to process
//!
//! **Required header:** `#include <eve/module/algo/algo/concepts.hpp>`
//!
//!   @code{.cpp}
//!   template <relaxed_range R>
//!   using iterator_t = decltype(std::declval<R>().begin());
//!   @endcode
//! @}
//================================================================================================
template <typename R>
using iterator_t = decltype(std::declval<R>().begin());

//================================================================================================
//! @addtogroup algo_concepts
//! @{
//!    @typedef iterator for a relaxed range
//!
//!    @tparam R - relaxed range to process
//!
//! **Required header:** `#include <eve/module/algo/algo/concepts.hpp>`
//!
//!   @code{.cpp}
//!   template <relaxed_range R>
//!   using sentinel_t = decltype(std::declval<R>().end());
//!   @endcode
//! @}
//================================================================================================
template <typename R>
using sentinel_t = decltype(std::declval<R>().end());

//================================================================================================
//! @addtogroup algo_concepts
//! @{
//!    @typedef unalgined_iterator_t for a relaxed range
//!
//!    @tparam R - relaxed range to process
//!
//!    @brief an iterator that can represent every position in the range
//!
//! **Required header:** `#include <eve/module/algo/algo/concepts.hpp>`
//!
//!   @code{.cpp}
//!   template <typename R>
//!   using unaligned_iterator_t = unaligned_t<iterator_t<R>>;
//!   @endcode
//! @}
//================================================================================================
template <typename R>
using unaligned_iterator_t = unaligned_t<iterator_t<R>>;
}
