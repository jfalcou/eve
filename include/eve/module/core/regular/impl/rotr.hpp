//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/rotl.hpp>

namespace eve::detail
{
  template<unsigned_value T, integral_value U>
  EVE_FORCEINLINE auto rotr_(EVE_SUPPORTS(cpu_), T a0, U n)  noexcept
  {
    return rotl(a0, U(-n));
  }

  template<conditional_expr C, unsigned_value T0, integral_real_value T1>
  auto rotr_(EVE_SUPPORTS(cpu_), C const &cond, T0 a0, T1 a1)
  {
   return mask_op(  cond, eve::rotr, a0, a1);
  }
}
