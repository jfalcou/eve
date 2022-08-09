//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/as_range.hpp>
#include <eve/algo/copy.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/swap_ranges.hpp>
#include <eve/algo/views/reverse.hpp>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup algorithms
  //! @{
  //!  @var reverse
  //!
  //!  @brief SIMD version of std::reverse
  //!    * default unrolling is 1.
  //!    * will won't align because it makes the logic more complex and does not win.
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
      using Traits = typename TraitsSupport::traits_type;
      static_assert(Traits::contains(no_aligning));

      if (rng.begin() == rng.end()) return;

      // To utilize extra information from range prerprocessing.
      auto processed = eve::algo::preprocess_range(TraitsSupport::get_traits(), EVE_FWD(rng));
      auto f  = processed.begin();
      auto l  = processed.end();
      auto rl = views::reverse(l);

      std::ptrdiff_t const n        = l - f;
      std::ptrdiff_t const cardinal = iterator_cardinal_v<decltype(f)>;

      std::ptrdiff_t two_register_steps = n / (2 * cardinal);
      std::ptrdiff_t left = n - cardinal * 2 * two_register_steps;

      // We will read the overlapping middle twice if we can
      // [          (  m  )          ]
      // This way we can treat the range as divisible by cardinal

      if (left >= cardinal) ++two_register_steps;
      else
      {
        auto f_m      = f  + two_register_steps * cardinal;
        auto rl_m     = rl + two_register_steps * cardinal;
        auto loaded   = load[keep_first(left)](f_m);
        eve::store[keep_first(left)](loaded, rl_m);
      }

      auto m = f + two_register_steps * cardinal;

      swap_ranges[processed.traits()][divisible_by_cardinal](as_range(f, m), rl);
    }
  };

  inline constexpr auto reverse = function_with_traits<reverse_>[algo::unroll<1>][no_aligning];

  //================================================================================================
  //! @addtogroup algorithms
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
