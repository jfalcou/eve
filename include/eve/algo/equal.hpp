//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/all_of.hpp>
#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/views/zip.hpp>


#include <utility>

namespace eve::algo
{
  template <typename TraitsSupport>
  struct equal_ : TraitsSupport
  {
    template <zipped_range_pair R, typename P>
    EVE_FORCEINLINE bool operator()(R&& r, P p) const
    {
      return algo::all_of[TraitsSupport::get_traits()](EVE_FWD(r),
                                                       apply_to_zip_pair{p});
    }

    template <zipped_range_pair R>
    EVE_FORCEINLINE bool operator()(R&& r) const
    {
      return operator()(r[common_type], eve::is_equal);
    }

    template <typename R1, typename R2, typename P>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE bool operator()(R1&& r1, R2&& r2, P p) const
    {
      return operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)), p);
    }

    template <typename R1, typename R2>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2) const
    {
      return operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)));
    }
  };

  inline constexpr auto equal = function_with_traits<equal_>[all_of.get_traits()];
}
