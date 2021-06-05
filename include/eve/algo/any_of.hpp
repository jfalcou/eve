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
#include <eve/algo/one_range_algorithm_adapter.hpp>
#include <eve/algo/traits.hpp>

#include <eve/function/any.hpp>
#include <eve/function/logical_or.hpp>

#include <array>

namespace eve::algo
{
  struct any_of_ : one_range_algorithm_adapter<any_of_>
  {
    static constexpr auto default_traits()
    {
      return algo::traits(algo::unroll<4>);
    };

    template <typename P>
    struct delegate
    {
      explicit delegate(P p) : p(p) {}

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore)
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

    template <instance_of<algo::traits> Traits, iterator I, sentinel_for<I> S, typename P>
    EVE_FORCEINLINE bool impl(Traits traits, I f, S l, P p) const
    {
      if (f == l) return false;

      delegate d{p};
      algo::for_each_iteration(traits, f, l)(d);
      return d.res;
    }
  } inline constexpr any_of;
}
