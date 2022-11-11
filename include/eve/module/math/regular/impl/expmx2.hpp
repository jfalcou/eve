//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/math/regular/expx2.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// regular case
template<value T>
EVE_FORCEINLINE constexpr T
expmx2_(EVE_SUPPORTS(cpu_), T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    return rec(expx2(a0));
  }
  else return apply_over(expmx2, a0);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
exmpx2_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::expmx2, t);
}

}
