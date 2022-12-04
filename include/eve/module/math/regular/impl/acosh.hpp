//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/inv_2eps.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/log1p.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE constexpr auto
acosh_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    const T    t    = dec(x);
    auto const test = is_greater(t, inv_2eps(eve::as<T>()));

    if constexpr( simd_value<T> )
    {
      const T z = if_else(test, x, t + sqrt(fma(t, t, t + t)));
      return add[test](log1p(z), log_2(eve::as<T>()));
    }
    else if constexpr( scalar_value<T> )
    {
      if( test ) { return eve::log(t) + log_2(eve::as<T>()); }
      else { return eve::log1p(t + eve::sqrt(fma(t, t, t + t))); }
    }
  }
  else { return apply_over(acosh, x); }
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
acosh_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::acosh, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
acosh_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::acosh), t);
}
}
