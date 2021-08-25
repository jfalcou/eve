//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/find.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/zip.hpp>

#include <eve/function/is_equal.hpp>

#include <utility>

namespace eve::algo
{
  template <typename TraitsSupport>
  struct mismatch_ : TraitsSupport
  {
    template <typename R1, typename R2, typename P>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, P p) const
    {
      auto tr = TraitsSupport::get_traits();
      auto zipped = algo::zip[tr](std::forward<R1>(r1), std::forward<R2>(r2));

      return algo::find_if/*FIX-#880: [tr]*/(zipped, [p](auto x_y) {
        auto [x, y] = x_y;
        return !p(x, y);
      });
    }

    template <typename R1, typename R2>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2) const
    {
      return (*this)[algo::common_type](std::forward<R1>(r1), std::forward<R2>(r2), eve::is_equal);
    }
  };

  inline constexpr auto mismatch = function_with_traits<mismatch_>[find_if.get_traits()];
}
