//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/sqrtvalmax.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/saturated/abs.hpp>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE constexpr auto
sqr_(EVE_SUPPORTS(cpu_), saturated_type const&, T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( floating_value<T> ) { return sqr(a0); }
    else if constexpr( scalar_value<T> )
    {
      return (eve::saturated(eve::abs)(a0) > sqrtvalmax(eve::as(a0))) ? valmax(eve::as(a0))
                                                                      : sqr(a0);
    }
    else
    {
      return if_else((saturated(abs)(a0) > sqrtvalmax(eve::as(a0))), valmax(eve::as(a0)), sqr(a0));
    }
  }
  else { return apply_over(saturated(sqr), a0); }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
sqr_(EVE_SUPPORTS(cpu_), C const& cond, saturated_type const&, U const& t) noexcept
{
  return mask_op(cond, saturated(eve::sqr), t);
}
}
