//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/detail/overload.hpp>
#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/logical_notand.hpp>
#include <eve/detail/select_over.hpp>

// This is a help for programming efiicient horizontal branching
// see dawson .hpp for an example
// the tests can be incompatible or in increasing order when
// using next interval

namespace eve
{

  template <typename F, typename L, typename L1, typename R, typename ...Ts>
  auto next_interval(F const & f, L notdone, L1 test, R& r, Ts ... ts) noexcept
  {
   auto todo = notdone && test;
    if constexpr(eve::scalar_value<R>)
    {
      if(todo) { r =  f(ts...); return false_(as(todo)); }
    }
    else
    {
      if(eve::any(todo))
      {
        r = detail::select_over(todo, f(ts...), r);
        return logical_notand(todo, notdone);
      };
    }
    return  logical_notand(todo, notdone);
  }

  template <typename F, typename L, typename R, typename ...Ts>
  auto last_interval(F const & f, L todo, R& r, Ts ... ts) noexcept
  {
    if constexpr(eve::scalar_value<R>)
    {
      if(todo){ r = f(ts...); return false_(as(r));}
      return false_(as(r));
    }
    else
    {
      if(eve::any(todo))  r = detail::select_over(todo, f(ts...), r);
      return eve::false_(as(r));
    }
  }
}
