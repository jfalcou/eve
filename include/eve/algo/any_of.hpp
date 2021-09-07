//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/array_utils.hpp>
#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>

#include <eve/function/any.hpp>
#include <eve/function/logical_or.hpp>

#include <array>
#include <utility>

namespace eve::algo
{
  template <typename TraitsSupport>
  struct any_of_ : TraitsSupport
  {
    template <typename P>
    struct delegate
    {
      explicit delegate(P p) : p(p) {}

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
      {
        eve::logical test = p(eve::load[ignore](it));
        res = eve::any[ignore](test);
        return res;
      }

      template <typename I, std::size_t size>
      EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
      {
        auto tests = array_map(arr, load_and_apply{p});
        auto overall = array_reduce(tests, eve::logical_or);
        res = eve::any(overall);
        return res;
      }

      P p;
      bool res = false;
    };

    template <relaxed_range Rng, typename P>
    EVE_FORCEINLINE bool operator()(Rng&& rng, P p) const
    {
      auto processed = preprocess_range(TraitsSupport::get_traits(), std::forward<Rng>(rng));

      if (processed.begin() == processed.end()) return false;

      delegate<P> d{p};
      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return d.res;
    }
  };
  inline constexpr auto any_of = function_with_traits<any_of_>[default_simple_algo_traits];
}
