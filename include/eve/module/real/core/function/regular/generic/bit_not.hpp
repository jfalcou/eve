//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto bit_not_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr(floating_scalar_value<T>)  return bit_cast( ~bit_cast(v, as_<as_integer_t<T>>{}), as(v));
    else                                    return T(~v);
  }

  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto bit_not_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::bit_not, t);
  }
}
