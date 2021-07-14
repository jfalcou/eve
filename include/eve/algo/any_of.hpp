//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/algo/array_utils.hpp>
#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>

#include <eve/function/any.hpp>
#include <eve/function/logical_or.hpp>

#include <array>
#include <utility>

namespace eve::algo
{
  template <instance_of<algo::traits> Traits>
  struct any_of_
  {
    Traits tr_;

    constexpr explicit any_of_(Traits tr) : tr_(tr) {}

    template <typename Settings>
    constexpr auto operator[](algo::traits<Settings> tr) const
    {
      auto sum = default_to(tr, tr_);
      return any_of_<decltype(sum)>{sum};
    }

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
        auto tests = array_map(arr, [&](I it) { return p(eve::load(it)); });
        auto overall = array_reduce(tests, eve::logical_or);
        res = eve::any(overall);
        return res;
      }

      P p;
      bool res = false;
    };

    template <typename Rng, typename P>
    EVE_FORCEINLINE bool operator()(Rng&& rng, P p) const
    {
      auto processed = preprocess_range(tr_, std::forward<Rng>(rng));

      if (processed.begin() == processed.end()) return false;

      delegate<P> d{p};
      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return d.res;
    }
  };
  inline constexpr any_of_ any_of{default_simple_algo_traits};
}
