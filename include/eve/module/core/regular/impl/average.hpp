//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/rec.hpp>


namespace eve::detail
{
  template<typename T, typename U, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T, U>
  average_(EVE_REQUIRES(cpu_), O const &, T const &aa,  U const &bb) noexcept
  {
    using r_t =  common_value_t<T, U>;
    auto a = r_t(aa);
    auto b = r_t(bb);
    if constexpr(integral_value <r_t>)
    {
      if constexpr(O::contains(upward2))
      {
        return (a | b) - ((a ^ b) >> 1);   //compute ceil( (x+y)/2 )
      }
      else
        return (a & b) + ((a ^ b) >> 1);   //compute floor( (x+y)/2 )
    }
    else
    {
      const auto h = eve::half(eve::as<r_t>());
      return fma(a, h, b*h);
    }
  }

  template<typename T0, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, Ts...>
  average_(EVE_REQUIRES(cpu_), O const &, T0 const &r0, Ts const &... args) noexcept
  {
    if constexpr(sizeof...(Ts) == 0)
      return r0;
    else
    {
      if constexpr(O::contains(raw2))
      {
        return add(r0, args...)/(sizeof...(args) + 1);
      }
      else
      {
        using r_t   = common_value_t<T0, Ts...>;
        r_t invn  = rec(r_t(sizeof...(args) + 1u));
        r_t   that(r0 * invn);
        auto  next = [invn](auto avg, auto x) { return fma(x, invn, avg); };
        ((that = next(that, r_t(args))), ...);
        return that;
      }
    }
  }
}
