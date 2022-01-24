//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/regular/tan.hpp>
#include <eve/module/math/regular/trigo_tags.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto tanpi_(EVE_SUPPORTS(cpu_), quarter_circle_type const &, T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return eve::quarter_circle(tan)(x * pi(eve::as<T>()));
    }
    else
      return apply_over(quarter_circle(tanpi), x);
  }

  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto tanpi_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  requires(is_one_of<D>(types<half_circle_type, full_circle_type, medium_type, big_type> {}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = eve::abs(a0);
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) )
          return a0;
        if( is_not_finite(x) || (frac(x) == half(eve::as<T>())) )
          return nan(eve::as<T>());
        if( x > maxflint(eve::as<T>()) || is_flint(x) )
          return T(0);
      }
      else
      {
        x = if_else(is_greater(x, maxflint(eve::as(x))) || is_flint(x), eve::zero, x);
        x = if_else(is_not_finite(a0) || (frac(x) == half(eve::as<T>())), eve::allbits, x);
      }
      auto [fn, xr, dxr] = rem2(x);
      return tan_finalize(a0 * pi(eve::as<T>()), fn, xr, dxr);
    }
    else
      return apply_over(D()(tanpi), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto tanpi_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = abs(a0);
      if( eve::all(eve::abs(x) <= T(0.25)) )
        return quarter_circle(tanpi)(a0);
      else
        return big(tanpi)(a0);
    }
    else
      return apply_over(tanpi, a0);
  }

}
