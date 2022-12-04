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
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
template<integral_value T>
EVE_FORCEINLINE constexpr as_logical_t<T>
is_pow2_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return is_gtz(a) && is_eqz(a & dec(a)); }
  else return apply_over(is_pow2, a);
}

// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
is_pow2_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
{
  return logical_mask_op(cond, is_pow2, u);
}
}
