//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/for_each_iteration.hpp>

#include <eve/function/any.hpp>



namespace eve::algo
{
  struct any_of_
  {
    struct default_traits {};

    template <typename P>
    struct delegate
    {
      explicit delegate(P p) : p(p) {}

      bool step(auto it, eve::relative_conditional_expr auto ignore)
      {
        auto test = p(eve::load[ignore](it));
        res = eve::any[ignore](test);
        return res;
      }

      P p;
      bool res = false;
    };

    template <typename Traits, typename I, typename S, typename P>
    bool operator()(Traits _traits, I _f, S _l, P p) const
    {
      if (_f == _l) return false;

      delegate d{p};

      auto [traits, f, l] = preprocess_range(_traits, _f, _l);
      for_each_iteration(traits, f, l, d);
      return d.res;
    }

    template <typename I, typename S, typename P>
    bool operator()(I f, S l, P p) const
    {
      return operator()(default_traits{}, f, l, p);
    }

  } inline constexpr any_of;
}
