//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/detail/overload.hpp>
#include <eve/as.hpp>
#include <eve/function/any.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/logical_not.hpp>

// This is a help for programming efiicient horizontal branching
// see dawson .hpp for an example

namespace eve
{
  template <typename F, typename L, typename L1, typename R, typename ...Ts>
  auto first_interval(F const & f, L  notdone, L1 test, R & r, Ts ... ts) noexcept
  {
    auto todo = notdone && test;
    if constexpr(eve::scalar_value<R>)
    {
      if(todo) { r =  f(ts...);  return false_(as(r)); }
    }
    else
    {
      if(eve::any(todo)) {r = if_else(todo, f(ts...), r); return !todo &&  notdone; };
    }
    return notdone;
  }

  template <typename F, typename L, typename L1, typename R, typename ...Ts>
  auto next_interval(F const & f, L notdone, L1 test, R& r, Ts ... ts) noexcept
  {
    auto todo =  notdone && test;
    if constexpr(eve::scalar_value<R>)
    {
      if(todo) { r =  f(ts...); return false_(as(r)); }
    }
    else
    {
      if(eve::any(todo)){  r = if_else(todo, f(ts...), r); return !todo && notdone; };
    }
    return notdone;
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
      if(eve::any(todo))  r = if_else(todo, f(ts...), r);
      return eve::false_(as(r));
    }
  }
}
