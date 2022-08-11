//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>

#include <concepts>

namespace eve::detail
{

template<real_value T>
EVE_FORCEINLINE constexpr T
abs_(EVE_SUPPORTS(cpu_), saturated_type const&, T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( signed_integral_scalar_value<T> )
    {
      return ((a == valmin(eve::as(a))) ? valmax(eve::as(a)) : eve::abs(a));
    }
    else if constexpr( signed_integral_simd_value<T> )
    {
      return if_else(a == valmin(eve::as(a)), valmax(eve::as(a)), eve::abs(a));
    }
    else if constexpr( floating_value<T> || unsigned_value<T> ) { return eve::abs(a); }
  }
  else { return apply_over(saturated(abs), a); }
}

// -----------------------------------------------------------------------------------------------
// Masked case

template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
abs_(EVE_SUPPORTS(cpu_), C const& cond, saturated_type const&, U const& t) noexcept
{
  return mask_op(cond, saturated(eve::abs), t);
}
}
