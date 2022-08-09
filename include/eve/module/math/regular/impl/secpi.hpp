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
#include <eve/module/math/regular/cospi.hpp>
#include <eve/module/math/regular/quadrant.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto secpi_(EVE_SUPPORTS(cpu_), quarter_circle_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x    = abs(a0);
      auto test = is_not_less_equal(x, T(0.25));
      if constexpr( scalar_value<T> )
      {
        if( test )
          return nan(eve::as<T>());
      }
      else
      {
        a0 = if_else(test, eve::allbits, a0);
      }

      a0 *= pi(eve::as<T>());
      auto x2 = sqr(a0);
      return rec(detail::cos_eval(x2));
    }
    else
    {
      return apply_over(quarter_circle(secpi), a0);
    }
  }

  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto secpi_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      const T x = eve::abs(a0);
      if constexpr( scalar_value<T> )
      {
        if( is_not_finite(x) )
          return nan(eve::as<T>());
        if( x > maxflint(eve::as<T>()) )
          return T(1);
      }

      T z = D()(cospi)(x);
      if constexpr( scalar_value<T> )
      {
        return (z) ? rec(z) : nan(eve::as<T>());
      }
      else
      {
        return if_else(is_nez(z) && is_finite(a0), rec(z), eve::allbits);
      }
    }
    else
    {
      return apply_over(D()(secpi), a0);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto secpi_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return big(secpi)(a0);
    }
    else
    {
      return apply_over(secpi, a0);
    }
  }

}
