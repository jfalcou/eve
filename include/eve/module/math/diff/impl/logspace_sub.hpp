//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/exp.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T logspace_sub_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return rec(oneminus(exp(y-x)));
  }

   template<floating_real_value T>
  EVE_FORCEINLINE constexpr T logspace_sub_(EVE_SUPPORTS(cpu_)
                                   , diff_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return  rec(oneminus(exp(x-y)));
  }


  //===============================================================================================
  // Multi case
  //================================================================================================
  template<int N, typename T0, typename T1, typename... Ts>
  auto logspace_sub_(EVE_SUPPORTS(cpu_), diff_type<N>
                    , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0,T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
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
      if constexpr(N == 1) that = arg0;
      else if constexpr(N == 2) that = arg1;
      else
      {
        getNth(std::make_index_sequence<sizeof...(args)>{},that,args...);
      }
      auto z = exp(arg0-that)-exp(arg1-that);
      z = eve::rec(z-(...+exp(args-that)));
      return (N == 1) ? z : -z;
    }
  }
}
