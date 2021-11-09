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

#include <eve/function/all.hpp>
#include <eve/function/logical_and.hpp>

#include <array>
#include <utility>

namespace eve::algo
{
  template <typename TraitsSupport>
  struct all_of_ : TraitsSupport
  {
    template <typename P>
    struct delegate
    {
      explicit delegate(P p) : p(p) {}

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
      {
        eve::logical test = p(eve::load[ignore](it));
        res = eve::all[ignore](test);
        return !res;
      }

      template <typename I, std::size_t size>
      EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
      {
        auto tests = array_map(arr, load_and_apply{p});
        auto overall = array_reduce(tests, eve::logical_and);
        res = eve::all(overall);
        return !res;
      }

      P p;
      bool res = true;
    };

    template <relaxed_range Rng, typename P>
    EVE_FORCEINLINE bool operator()(Rng&& rng, P p) const
    {
      auto processed = preprocess_range(TraitsSupport::get_traits(), EVE_FWD(rng));

      if (processed.begin() == processed.end()) return true;

      delegate<P> d{p};
      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return d.res;
    }
  };

  inline constexpr auto all_of = function_with_traits<all_of_>[default_simple_algo_traits];
}
