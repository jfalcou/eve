//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/regular/asin.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto acos_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto tmp = pio_2(eve::as(a0)) + (Ieee_constant<T, 0XB33BBD2EU, 0x3c91a62633145c07ll>() - asin(a0));
      return if_else(a0 == T(1), eve::zero, tmp);
    }
    else
    {
      return apply_over(raw(acos), a0);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto acos_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( simd_value<T> )
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto const half  = eve::half(eve::as(a0));
        auto const mhalf = eve::mhalf(eve::as(a0));

        auto x           = eve::abs(a0);
        auto x_larger_05 = (x > half);

        x = if_else(x_larger_05, eve::sqrt(fma(mhalf, x, half)), a0);
        x = asin(x);
        x = add[x_larger_05](x, x);
        x = eve::if_else((a0 < mhalf), eve::pi(eve::as(a0)) - x, x);

        return eve::if_else(x_larger_05, x, eve::pio_2(eve::as(a0)) - x);
      }
      else
      {
        return apply_over(acos, a0);
      }
    }
    else if constexpr( scalar_value<T> )
    {
      if( a0 == T(1) )
      {
        return T(0);
      }

      if( eve::abs(a0) > T(1) )
      {
        return nan(eve::as<T>());
      }

      if constexpr( std::same_as<T, float> )
      {
        if( a0 < -0.5f )
        {
          return pi(eve::as<T>()) - 2.0f * eve::asin(eve::sqrt(inc(a0) * 0.5f));
        }
        else if( a0 > 0.5f )
        {
          return 2.0f * eve::asin(eve::sqrt(oneminus(a0) * 0.5f));
        }
        else
        {
          return pio_2(eve::as<T>()) - eve::asin(a0);
        }
      }
      else if constexpr( std::same_as<T, double> )
      {
        if( a0 > 0.5 )
        {
          return 2.0 * eve::asin(eve::sqrt(fma(-0.5, a0, 0.5)));
        }

        T const pio4 = pio_4(eve::as<T>());

        T z = pio4 - eve::asin(a0);
        z += Constant<T, 0X3C81A62633145C07ULL>(); // Pio_4lo(as<T>());
        z += pio4;

        return z;
      }
    }
  }
}
