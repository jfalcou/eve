//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/transform.hpp>
#include <eve/algo/traits.hpp>

#include <eve/function/zip.hpp>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup algo
  //! @{
  //!  @var swap_ranges
  //!
  //!  @brief SIMD version of std::swap_ranges
  //!    * Accepts two things zipping together to range of pair.
  //!    * Also can accept a `zipped_range_pair`.
  //!    * returns void.
  //!    * default unrolling is 4.
  //!    * will align by default.
  //!    * will do conversions if necessary.
  //!
  //!   **Required header:** `#include <eve/algo/swap_ranges.hpp>`
  //!
  //! @}
  //================================================================================================

  template <typename TraitsSupport>
  struct swap_ranges_ : TraitsSupport
  {
    struct op
    {
      EVE_FORCEINLINE auto operator()(auto in) const
      {
        return eve::zip(get<1>(in), get<0>(in));
      }
    };

    template <zipped_range_pair R>
    EVE_FORCEINLINE void operator()(R r) const
    {
      auto rezipped = r[common_type];
      transform_inplace[TraitsSupport::get_traits()](rezipped, op{});
    }

    template <typename R1, typename R2>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE void operator()(R1&& r1, R2&& r2) const
    {
      operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)));
    }
  };

  inline constexpr auto swap_ranges = function_with_traits<swap_ranges_>[default_simple_algo_traits];
}
