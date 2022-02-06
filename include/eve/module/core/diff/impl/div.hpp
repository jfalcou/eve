//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/rec.hpp>
#include <eve/module/arithmetic/regular/sqr.hpp>

namespace eve::detail
{
  template<int N, real_value T, real_value U>
  EVE_FORCEINLINE auto
  div_(EVE_SUPPORTS(cpu_), diff_type<N> const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(diff_type<N>()(div), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T , T y ) noexcept
  {
    return rec(y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                    , diff_type<2> const &
                                    , T x, T y ) noexcept
  {

    return -rec(sqr(y))*x;
  }

  template<int N, typename T0, typename T1, typename... Ts>
  EVE_FORCEINLINE auto div_(EVE_SUPPORTS(cpu_), diff_type<N>
                           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0,T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
    else
    {
      r_t h = mul(r_t(arg1), r_t(args)...);
      if constexpr(N==1) return  rec(h);
      else {
        h = -r_t(arg0)/h;
        if constexpr(N==2) return  h/r_t(arg1);
        else
        {
          auto getNth = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
            {
              auto iff = [&that]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
              {
                if constexpr(J==N) that = val;
              };

              ((iff(vs, std::integral_constant<std::size_t,I+3>{})),...);
            };
          r_t that(0);
          getNth(std::make_index_sequence<sizeof...(args)>{},that,r_t(args)...);
          return h/that;
        }
      }
    }
  }
}
