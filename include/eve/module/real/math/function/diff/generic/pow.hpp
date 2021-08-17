//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/pow.hpp>

#include <eve/function/dec.hpp>
#include <eve/function/log.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T pow_(EVE_SUPPORTS(cpu_)
                                   , diff_type<2> const &
                                   , T x, T y, N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return pow(x, y)*pow(log(x), n);
    }
    else
      return apply_over(diff_1st(pow), x, y, n);
  }

  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T pow_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x, T y, N p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t =  element_type_t<T>;
      auto yp1 = inc(y);
      auto fp = to_<elt_t>(p);
      return (tgamma(yp1)/tgamma(yp1-fp))*pow(x, y-fp); // TO DO better eval
    }
    else
      return apply_over(diff_2nd(pow), x, y, p);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T pow_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return pow(x, dec(y))*y;
  }

   template<floating_real_value T>
  EVE_FORCEINLINE constexpr T pow_(EVE_SUPPORTS(cpu_)
                                   , diff_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return pow(x, y)*log(x);
  }
}
