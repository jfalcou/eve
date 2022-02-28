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
#include <eve/module/math/regular/div_180.hpp>
#include <eve/module/math/detail/generic/rem180.hpp>
#include <eve/module/math/regular/tanpi.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>


namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto tand_(EVE_SUPPORTS(cpu_), quarter_circle_type const &, T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return eve::quarter_circle(tanpi)(div_180(x));
    }
    else
      return apply_over(quarter_circle(tand), x);
  }

  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto tand_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  requires(is_one_of<D>(types<half_circle_type, full_circle_type, medium_type, big_type> {}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = eve::abs(a0);
      auto  a0_180 = div_180(a0);
      auto test   = is_not_flint(a0_180) && is_flint(a0_180+mhalf(eve::as(a0_180)));
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) )          return a0;
        if( test ) return nan(eve::as<T>());
      }
      else
      {
        x = if_else(test, eve::allbits, x);
       }
      auto [fn, xr, dxr] = rem180(x);
      return tan_finalize(deginrad(a0), fn, xr, dxr);
    }
    else
      return apply_over(D()(tand), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto tand_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = abs(a0);
      if( eve::all(eve::abs(x) <= T(45)) )
        return quarter_circle(tand)(a0);
      else
        return big(tand)(a0);
    }
    else
      return apply_over(tand, a0);
  }


}
