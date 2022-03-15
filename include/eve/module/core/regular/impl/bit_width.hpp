//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/countl_zero.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/countl_zero.hpp>

#include <bit>

namespace eve::detail
{
  template<unsigned_value T> EVE_FORCEINLINE T bit_width_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    using elt_t = element_type_t<T>;
    return T(sizeof(elt_t) * 8 - countl_zero(v));
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, unsigned_value U>
  EVE_FORCEINLINE auto bit_width_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op(  cond, eve::bit_width, t);
  }

}
