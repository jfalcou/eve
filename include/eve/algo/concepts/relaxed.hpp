//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/detail/preprocess_range.hpp>
#include <eve/algo/concepts/detail.hpp>

#include <concepts>

namespace eve::algo
{
  template <typename I>
  concept relaxed_iterator =
    std::invocable<preprocess_range_, decltype(eve::algo::traits{}), I, I>;

  template <typename S, typename I>
  concept relaxed_sentinel_for = std::totally_ordered_with<S, I> &&
   std::invocable<preprocess_range_, decltype(eve::algo::traits{}), I, S> &&
   requires(I i, S s) {
      { s - i } -> std::same_as<std::ptrdiff_t>;
   };

  template <typename I, typename S>
  concept relaxed_iterator_sentinel = relaxed_sentinel_for<S, I>;

  template <typename R>
  concept relaxed_range =
    detail::has_begin_end<R> &&
    std::invocable<preprocess_range_, decltype(eve::algo::traits{}), R>;
}
