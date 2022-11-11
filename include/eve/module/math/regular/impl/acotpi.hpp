//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/acot.hpp>
#include <eve/module/math/regular/radinpi.hpp>

namespace eve::detail
{
template<value T>
EVE_FORCEINLINE constexpr auto
acotpi_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return radinpi(acot(a)); }
  else { return apply_over(acotpi, a); }
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
acotpi_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::acotpi, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
acotpi_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::acotpi), t);
}
}
