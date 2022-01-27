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
#include <eve/module/math/regular/cos.hpp>
#include <eve/module/math/regular/trigo_tags.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_), quarter_circle_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) )
          return bit_or(a0, inf(eve::as(a0)));
        auto x = abs(a0);
        if( is_not_less_equal(x, T(0.25)) )
          return nan(eve::as<T>());
        return rec(tancot_eval(pi(eve::as<T>()) * a0));
      }
      else
      {
        auto x = eve::abs(a0);
        return if_else(
            is_eqz(a0),
            bit_or(a0, inf(eve::as(a0))),
            if_else(is_not_less_equal(x, T(0.25)), eve::allbits, rec(tancot_eval(pi(eve::as<T>()) * a0))));
      }
    }
    else
      return apply_over(quarter_circle(cotpi), a0);
  }

  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  requires(is_one_of<D>(types<half_circle_type, full_circle_type, medium_type, big_type> {}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) )
          return bit_or(a0, inf(eve::as(a0)));
        if( is_not_finite(a0) || is_flint(a0) )
          return nan(eve::as<T>());
      }
      auto x = abs(a0);
      if constexpr( simd_value<T> )
      {
        x = if_else(is_not_finite(a0) || is_flint(x), eve::allbits, x);
      }
      auto [fn, xr, dxr] = rem2(x);
      return cot_finalize(a0 * pi(eve::as<T>()), quadrant(fn), xr, dxr);
    }
    else
      return apply_over(D()(cotpi), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = abs(a0);
      if( eve::all(eve::abs(x) <= T(0.25)) )
        return quarter_circle(cotpi)(a0);
      else
        return big(cotpi)(a0);
    }
    else
      return apply_over(cotpi, a0);
  }
}
