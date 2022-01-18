//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/math/regular/geommean.hpp>

namespace eve::detail
{
  template<auto N, floating_real_value T, floating_real_value... Ts>
  EVE_FORCEINLINE constexpr T geommean_(EVE_SUPPORTS(cpu_)
                                    , diff_type<N> const &
                                    , T y, Ts ... ys ) noexcept
  {
    using r_t = common_compatible_t<T,Ts...>;
    if constexpr(N > sizeof...(Ts)+1) return zero(as < r_t>());
    auto g = geommean(y, ys...);
    auto n = sizeof...(ys)+1;
    if constexpr(N == 1)
    {
      return g/(y*n);
    }
    auto nth = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
      {
        auto iff = [&]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
        {
          if constexpr(J==N) that = r_t(val);
        };

        ((iff(vs, std::integral_constant<std::size_t,I+2>{})),...);
      };
    r_t d(0);
    nth(std::make_index_sequence<sizeof...(ys)>{},d,ys...);
   return g/(d*n);
  }
}
