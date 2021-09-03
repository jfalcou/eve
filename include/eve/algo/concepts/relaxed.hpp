//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/detail.hpp>
#include <eve/algo/detail/preprocess_range.hpp>

namespace eve::algo
{
  template <typename I>
  concept relaxed_iterator =
    std::invocable<preprocess_range_, decltype(eve::algo::traits{}), I, I>;

  template <typename R>
  concept relaxed_range =
    detail::has_begin_end<R> &&
    std::invocable<preprocess_range_, decltype(eve::algo::traits{}), R>;
}
