//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/preprocess_range.hpp>

namespace eve::algo
{
  template <typename I>
  concept relaxed_iterator =
    std::invocable<preprocess_range_, decltype(eve::algo::traits{}), I, I>;

  template <typename I, typename S>
  concept relaxed_iterator_sentinel =
    std::invocable<preprocess_range_, decltype(eve::algo::traits{}), I, S>;

  namespace detail
  {
    template <typename R>
    concept has_begin_end = requires (R&& r) {
        { r.begin() };
        { r.end() };
    };
  }

  template <typename R>
  concept relaxed_range =
    detail::has_begin_end<R> &&
    std::invocable<preprocess_range_, decltype(eve::algo::traits{}), R>;
}
