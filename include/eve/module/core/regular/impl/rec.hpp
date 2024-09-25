//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/div.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/regular/prev.hpp>
#include <eve/module/core/regular/div.hpp>

namespace eve::detail
{

  template<value T, callable_options O>
  constexpr T  rec_(EVE_REQUIRES(cpu_), O const& o, T const& a) noexcept
  {
    if constexpr( floating_value<T> )
    {
      auto num = T{1};
      if constexpr( O::contains(lower) || O::contains(upper))
      {
       if constexpr(O::contains(strict))
       {
         auto d = rec[o.drop(lower, upper)](a);
         if constexpr(O::contains(upper))
           return next(d);
         else
           return prev(d);
       }
        else
        {
          auto d = minus[is_negative(a)](rec[o.drop(lower, upper)](abs(a)));
          auto [r, e] = two_prod(d, a);
          if constexpr(O::contains(upper))
            return next[r < num || ((r == num) && is_ltz(e))](d);
          else
            return prev[r > num || ((r == num) && is_gtz(e))](d);
        }
      }
      else
      {
        return num/a;
      }
    }
    else if( integral_value<T> )
    {
      if constexpr( scalar_value<T> )
      {
        // Generates a branch-less rec by triggering the use of conditional moves
        if( std::is_unsigned_v<T> )
        {
          auto b = a > 1 ? 0 : 1;
          return (a ? 1 : valmax(eve::as(a))) * b;
        }
        else
        {
          auto b1 = a > 1 ? 0 : 1;
          auto b2 = a < -1 ? 0 : 1;
          b2 *= b1;

          return (a ? a : valmax(eve::as(a))) * b2;
        }
      }
      else // constexpr( simd_value<T> )
      {
        if( std::is_unsigned_v<T> )
          return if_else(is_eqz(a), valmax(eve::as(a)), if_else(eve::abs(a) == one(eve::as(a)), a, eve::zero));
        else
          return map(eve::rec, a);
      }
    }
  }
}
