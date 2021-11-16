//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/copy.hpp>
#include <eve/algo/views/reverse.hpp>

namespace eve::algo
{
  template <typename TraitsSupport>
  struct reverse_copy_ : TraitsSupport
  {
    template <typename R1, typename R2>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE void operator()(R1&& r1, R2&& r2) const
    {
      return eve::algo::copy[TraitsSupport::get_traits()]
        (views::reverse(EVE_FWD(r1)), EVE_FWD(r2));
    }

    template <zipped_range_pair R>
    EVE_FORCEINLINE void operator()(R r) const
    {
      auto [from, to] = r;
      return operator()(from, to);
    }
  };

  inline constexpr auto reverse_copy = function_with_traits<reverse_copy_>[algo::unroll<1>][algo::no_aligning];
}
