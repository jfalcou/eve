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

#include <eve/function/pow_abs.hpp>
#include <eve/function/log_abs.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/converter.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T pow_abs_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<2> const &
                                   , T x, T y, N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return pow_abs(x, y)*pow_abs(log_abs(x), n);
    }
    else
      return apply_over(derivative_1st(pow_abs), x, y, n);
  }

  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T pow_abs_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x, T y, N p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t =  element_type_t<T>;
      auto yp1 = inc(y);
      auto fp = to_<elt_t>(p);
      return (tgamma(yp1)/tgamma(yp1-fp))*pow_abs(x, y-fp); // TO DO better eval
    }
    else
      return apply_over(derivative_2nd(pow_abs), x, y, p);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T pow_abs_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return pow_abs(x, dec(y))*y;
  }

   template<floating_real_value T>
  EVE_FORCEINLINE constexpr T pow_abs_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return pow_abs(x, y)*log_abs(x);
  }
}
