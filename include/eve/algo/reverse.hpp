//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/as_range.hpp>
#include <eve/algo/copy.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/swap_ranges.hpp>
#include <eve/algo/views/reverse.hpp>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup algo
  //! @{
  //!  @var reverse
  //!
  //!  @brief SIMD version of std::reverse
  //!    * default unrolling is 1.
  //!    * will align by default.
  //!
  //!   **Required header:** `#include <eve/algo/reverse.hpp>`
  //!
  //! @}
  //================================================================================================

  template <typename TraitsSupport>
  struct reverse_ : TraitsSupport
  {
    template <relaxed_range Rng>
    EVE_FORCEINLINE void operator()(Rng&& rng) const
    {
      if (rng.begin() == rng.end()) return;

      // To utilize extra information from range prerprocessing.
      auto processed = eve::algo::preprocess_range(TraitsSupport::get_traits(), EVE_FWD(rng));
      auto f = processed.begin();
      auto l = processed.end();

      std::ptrdiff_t n = l - f;
      auto m = unalign(f) + n / 2;

      // Just because the whole thing is divisible_by_cardinal does not mean
      // the halve will be.
      auto tr = drop_key(divisible_by_cardinal, processed.traits());
      swap_ranges[tr](as_range(f, m), views::reverse(l));
    }
  };

  inline constexpr auto reverse = function_with_traits<reverse_>[algo::unroll<1>];

  //================================================================================================
  //! @addtogroup algo
  //! @{
  //!  @var reverse_copy
  //!
  //!  @brief SIMD version of std::reverse_copy
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
