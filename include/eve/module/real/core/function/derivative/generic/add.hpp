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
#include <eve/function/add.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N, unsigned_value P>
  EVE_FORCEINLINE constexpr T add_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , T y
                                   , N n
                                   , P p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto np = n+p;
      return if_else(np == 0, x+y, if_else(np == 1,  one(as(x)), zero));
    }
    else
      return apply_over(derivative_1st(add), x, y, n, p);
  }

  template<auto N, floating_real_value T, floating_real_value... Ts>
  EVE_FORCEINLINE constexpr T add_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<N> const &
                                    , T x, Ts ... args ) noexcept
  {
    using r_t = decltype(add(x, args...));   //compatibility_t <T, Ts...>;
    return (N > sizeof...(Ts)+1) ? zero(as < r_t>()) : one(as<r_t>());
  }
}
