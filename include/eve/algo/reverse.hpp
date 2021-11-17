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
  //================================================================================================
  //! @addtogroup eve.algo
  //! @{
  //!  @var reverse_copy
  //!
  //!  @brief version of std::reverse_copy
  //!    * Accepts two things zipping together to range of pair.
  //!    * Also can accept a `zipped_range_pair`.
  //!    * returns void.
  //!    * default unrolling is 1.
  //!    * will align by default.
  //!    * will do conversions if necessary.
  //!
  //!  NOTE: `reverese_copy(it, range)` works but it's the same as
  //!        `reverse_copy(views::zip(it, range))`, so `it` will be
  //!        treated as `first` not `last`.
  //!
  //!   **Required header:** `#include <eve/algo/reverse.hpp>`
  //!
  //! @}
  //================================================================================================

  template <typename TraitsSupport>
  struct reverse_copy_ : TraitsSupport
  {
    template <zipped_range_pair R>
    EVE_FORCEINLINE void operator()(R r) const
    {
      auto [from, to] = r;
      return eve::algo::copy[TraitsSupport::get_traits()](views::reverse(from), to);
    }

    template <typename R1, typename R2>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE void operator()(R1&& r1, R2&& r2) const
    {
      return operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)));
    }
  };

  inline constexpr auto reverse_copy = function_with_traits<reverse_copy_>[algo::unroll<1>];
}
