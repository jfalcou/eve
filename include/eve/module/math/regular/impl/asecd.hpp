//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/asec.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve::detail
{
template<floating_real_value T, decorator D>
EVE_FORCEINLINE constexpr auto
asecd_(EVE_SUPPORTS(cpu_), D const& d, T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return radindeg(d(eve::asec)(a)); }
  else { return apply_over(d(eve::asecd), a); }
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
asecd_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  return asecd(regular_type(), a);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
asecd_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::asecd, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
asecd_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::asecd), t);
}
}
