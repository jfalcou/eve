//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/any_of.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/traits.hpp>

#include <utility>

namespace eve::algo
{
  template <typename TraitsSupport>
  struct none_of_ : TraitsSupport
  {
    template <relaxed_range Rng, typename P>
    EVE_FORCEINLINE bool operator()(Rng&& rng, P p) const
    {
      return !any_of[TraitsSupport::get_traits()](EVE_FWD(rng), p);
    }
  };

  inline constexpr auto none_of = function_with_traits<none_of_>;
}
