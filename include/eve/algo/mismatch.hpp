//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts.hpp>
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
    template <zipped_range_pair R, typename P>
    EVE_FORCEINLINE auto operator()(R&& r, P p) const
    {
      return algo::find_if[TraitsSupport::get_traits()]
        (std::forward<R>(r), [p](auto x_y) {
          auto [x, y] = x_y;
          return !p(x, y);
        }
      );
    }

    template <zipped_range_pair R>
    EVE_FORCEINLINE auto operator()(R&& r) const
    {
      return operator()(r[common_type], eve::is_equal);
    }

    template <typename R1, typename R2, typename P>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, P p) const
    {
      return operator()(zip(std::forward<R1>(r1), std::forward<R2>(r2)), p);
    }

    template <typename R1, typename R2>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2) const
    {
      return operator()(zip(std::forward<R1>(r1), std::forward<R2>(r2)));
    }
  };

  inline constexpr auto mismatch = function_with_traits<mismatch_>[find_if.get_traits()];
}
