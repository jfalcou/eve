//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/constant/half.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/diff/sub.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/sign.hpp>
#include <eve/concept/compatible.hpp>

namespace eve::detail
{
  template<auto N, floating_real_value T, floating_real_value... Ts>
  EVE_FORCEINLINE constexpr T manhattan_(EVE_SUPPORTS(cpu_)
                                        , diff_type<N> const &
                                        , T x, Ts ... args ) noexcept
  {
    using r_t = common_compatible_t<T,Ts...>;
    if constexpr(N > sizeof...(Ts)+1) return zero(as < r_t>());
    else if constexpr(N == 1)
    {
      return sign(x);
    }
    else
    {
      auto getNth = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
        {
          auto iff = [&that]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
          {
            if constexpr(J==N) that = val;
          };

          ((iff(vs, std::integral_constant<std::size_t,I+2>{})),...);
        };
      r_t that(0);
      getNth(std::make_index_sequence<sizeof...(args)>{},that,args...);
      return sign(that);
    }
  }

}
