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
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr auto
  average_(EVE_REQUIRES(cpu_), O const &, T const &a,  T const &b) noexcept
  {
    if constexpr(integral_value <T>)
    {
      if constexpr(O::contains(upward2))
        return (a | b) - ((a ^ b) >> 1);   //compute ceil( (x+y)/2 )
      else
        return (a & b) + ((a ^ b) >> 1);   //compute floor( (x+y)/2 )
    }
    else
    {
      const auto h = eve::half(eve::as<T>());
      return fma(a, h, b*h);
    }
  }

  template<typename T, std::same_as<T>... Ts, callable_options O>
  EVE_FORCEINLINE constexpr T
  average_(EVE_REQUIRES(cpu_), O const &, T const &r0, Ts const &... args) noexcept
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
        T invn  = rec[pedantic2](T(sizeof...(args) + 1u));
        T that(r0 * invn);
        auto  next = [invn](auto avg, auto x) { return fma(x, invn, avg); };
        ((that = next(that, args)), ...);
        return that;
      }
    }
  }
}
