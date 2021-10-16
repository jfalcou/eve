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
#include <eve/algo/views/zip.hpp>

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
      return algo::find_if_not[TraitsSupport::get_traits()]
        (std::forward<R>(r), apply_to_zip_pair{p});
    }

    template <zipped_range_pair R>
    EVE_FORCEINLINE auto operator()(R&& r) const
    {
      auto rezipped = r[common_type];
      auto rezipped_res = operator()(rezipped, eve::is_equal);
      return unalign(r.begin()) + (rezipped_res - rezipped.begin());
    }

    template <typename R1, typename R2, typename P>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, P p) const
    {
      return operator()(views::zip(std::forward<R1>(r1), std::forward<R2>(r2)), p);
    }

    template <typename R1, typename R2>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2) const
    {
      return operator()(views::zip(std::forward<R1>(r1), std::forward<R2>(r2)));
    }
  };

  inline constexpr auto mismatch = function_with_traits<mismatch_>[find_if.get_traits()];
}
