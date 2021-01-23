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

#include <eve/constant/one.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/diff/plus.hpp>
#include <eve/function/mul.hpp>
#include <eve/traits/common_compatible.hpp>


namespace eve::detail
{
  template<int N, typename T0, typename T1, typename... Ts>
  auto mul_(EVE_SUPPORTS(cpu_), diff_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    auto mmul = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
      {
        auto iff = []<std::size_t J>(auto acc, auto val, std::integral_constant<std::size_t,J>)
        {
          if constexpr(J==N) return acc; else return acc*val;
        };

        ((that = iff(that,vs, std::integral_constant<std::size_t,I+3>{})),...);
      };
    using r_t = common_compatible_t<T0,T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
    else if constexpr(N== 1)
    {
      return r_t{mul(arg1, args...)};
    }
    else if constexpr(N==2)
    {
      return r_t{mul(arg0, args...)};
    }
    else
    {
      auto that = arg0*arg1;
      mmul(std::make_index_sequence<sizeof...(args)>{},that,args...);
      return that;
    }
  }
}
