//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/if_else.hpp>
#include <eve/function/derivative.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{

  template<int N, typename F, typename T0, typename T1, typename... Ts>
  auto minmax_kernel(F const & op, T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0,T1, Ts...>;
    auto getNth = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
      {
        auto iff = [&that]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
        {
          if constexpr(J==N) that = val;
        };

        ((iff(vs, std::integral_constant<std::size_t,I+3>{})),...);
      };
    using r_t = common_compatible_t<T0,T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
    else
    {
      auto m = op(arg0, arg1, args...);
      if constexpr(N==1)
      {
        return if_else(m == arg0, one(as(m)), zero);
      }
      else if constexpr(N==2)
      {
        return  if_else(m == arg1, one(as(m)), zero);
      }
      else
      {
        r_t that(0);
        getNth(std::make_index_sequence<sizeof...(args)>{},that,args...);
        return if_else(m == that, one(as(m)), zero);
      }
    }
  }
}
