//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/func/conditional.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto bit_not_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr(floating_scalar_value<T>)  return bit_cast( ~bit_cast(v, as<as_integer_t<T>>{}), as(v));
    else                                    return T(~v);
  }

  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto bit_not_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op(  cond, eve::bit_not, t);
  }

}
