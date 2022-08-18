//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/sin.hpp>

namespace eve::detail
{

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
sinc_(EVE_SUPPORTS(cpu_), T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> )
    {
      if( is_eqz(a0) ) return one(eve::as(a0));
      if constexpr( eve::platform::supports_infinites )
        if( is_infinite(a0) ) return zero(eve::as<T>());
      if constexpr( eve::platform::supports_denormals )
        return eve::abs(a0) < eps(as<T>()) ? one(eve::as<T>()) : sin(a0) / a0;
      else return sin(a0) / a0;
    }
    else
    {
      auto r1 = sin(a0) / a0;
      if constexpr( eve::platform::supports_denormals )
      {
        r1 = if_else(eve::abs(a0) < eps(as<T>()), one(eve::as<T>()), r1);
      }
      else r1 = if_else(is_eqz(a0), one(eve::as<T>()), r1);
      if constexpr( eve::platform::supports_infinites )
        r1 = if_else(is_infinite(a0), eve::zero, r1);
      return r1;
    }
  }
  else { return apply_over(sinc, a0); }
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
sinc_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::sinc, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
sinc_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::sinc), t);
}
}
