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

#include <eve/function/rec.hpp>
#include <eve/function/derivative.hpp>
#include <eve/concept/compatible.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U, auto N>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , U const &y) noexcept
  requires(compatible_values<T, U>)
  {
    return arithmetic_call(derivative_type<N>()(hypot), x, y);
  }

  template<floating_real_value T, floating_real_value U, floating_real_value V, auto N>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , U const &y
                                   , V const &z) noexcept
  requires(compatible_values<T, U> && compatible_values<T, V>)
  {
    return arithmetic_call(derivative_type<N>()(hypot), x, y, z);
  }

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
   if constexpr( has_native_abi_v<T> )
    {
     auto k = rec(hypot(x, y));
     if constexpr(N == 1) return x*k;
     else if constexpr(N == 2) return y*k;
    }
   else
     return apply_over(derivative_type<N>()(hypot), x, y);
  }

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , T const &y
                                   , T const &z) noexcept
  {
   if constexpr( has_native_abi_v<T> )
    {
     auto k = rec(hypot(x, y, z));
     if constexpr(N == 1) return x*k;
     else if constexpr(N == 2) return y*k;
     else if constexpr(N == 3) return z*k;
    }
   else
     return apply_over(derivative_type<N>()(hypot), x, y, z);
  }

  template<int N, typename T0, typename T1, typename... Ts>
  auto hypot_(EVE_SUPPORTS(cpu_), derivative_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
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
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
    else
    {
      auto h =hypot(arg0, arg1, args...); 
      auto m = op(arg0, arg1, args...);
      if constexpr(N==1)
      {
        return arg0/h; 
      }
      else if constexpr(N==2)
      {
        return  arg1/h;
      }
      else
      {
        r_t that(0);
        getNth(std::make_index_sequence<sizeof...(args)>{},that,args...);
        return that/h
      }   
    }
  }
}
