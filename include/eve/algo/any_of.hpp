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

namespace eve::algo
{
  struct any_of_
  {
    static constexpr traits default_traits{unroll<4>};

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

    template <typename Traits, typename I, typename S, typename P>
    EVE_FORCEINLINE bool operator()(Traits _traits, I _f, S _l, P p) const
    {
      if (_f == _l) return false;

      delegate d{p};

      auto [traits, f, l] = preprocess_range(default_to(_traits, default_traits), _f, _l);
      for_each_iteration(traits, f, l, d);
      return d.res;
    }

    template <typename I, typename S, typename P>
    EVE_FORCEINLINE bool operator()(I f, S l, P p) const
    {
      return operator()(default_traits, f, l, p);
    }

  } inline constexpr any_of;
}
