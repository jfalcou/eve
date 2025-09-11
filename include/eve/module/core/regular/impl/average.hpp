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
#include <eve/module/core/regular/two_fma_approx.hpp>

namespace eve::detail
{

  template<value T0, value ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  average_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts const &... args) noexcept
  {
    using r_t =  eve::common_value_t<T0, Ts...>;
    using e_t =  eve::element_type_t<r_t>;
    if constexpr(O::contains(widen))
    {
      return average[o.drop(widen)](upgrade(a0), upgrade(args)...);
    }
    else if constexpr(sizeof...(Ts) == 0)
      return a0;
    else if constexpr(sizeof...(Ts) == 1)
    {
      const auto b = r_t(args...);
      const auto a = r_t(a0);
      if constexpr(integral_value<r_t>)
      {
       if constexpr(O::contains(upper))
          return (a | b) - ((a ^ b) >> 1);   //compute ceil( (a+b)/2 )
        else
          return (a & b) + ((a ^ b) >> 1);   //compute floor( a+b)/2 )  default
      }
      else
      {
        const auto h = eve::half(eve::as<e_t>());
        return fma[o][pedantic](a, h, b*h);
      }
    }
    else
    {
      constexpr auto N = sizeof...(Ts)+1;
      constexpr e_t invn = 1/(e_t(N));
      if constexpr(O::contains(raw))
      {
        if constexpr(integral_value<r_t>)
        {
          return add[o.drop(raw)](a0, args...)/N;
        }
        else
        {
          return eve::mul[o](add[o.drop(raw)](a0, args...), invn);
        }
      }
      else if constexpr(O::contains(kahan))
      {
        auto pair_add = [invn](auto pair0, auto r1){
          auto [r, e0] = pair0;
          auto [s, e1] = eve::two_fma_approx(r1, invn, r);
          return zip(s, e0+e1);
        };
        auto p0 = two_prod(r_t(a0), invn);
        ((p0 = pair_add(p0,args)),...);
        auto [r, e] = p0;
        return r+e;
      }
      else
      {
        r_t that(a0 * invn);
        auto lfma = fma[o];
        auto  next = [invn, lfma](auto avg, auto x) { return lfma(x, invn, avg); };
        ((that = next(that, r_t(args))), ...);
        return that;
      }
    }
  }
}
