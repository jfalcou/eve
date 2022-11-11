//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/acos.hpp>

namespace eve::detail
{
template<floating_real_value T, decorator D>
EVE_FORCEINLINE constexpr auto
asec_(EVE_SUPPORTS(cpu_), D const&, T const& a) noexcept
    requires(is_one_of<D>(types<regular_type, raw_type> {}))
{
  if constexpr( has_native_abi_v<T> ) { return D()(acos)(rec(a)); }
  else { return apply_over(D()(eve::asec), a); }
}

template<value T>
EVE_FORCEINLINE constexpr auto
asec_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return acos(rec(a)); }
  else { return apply_over(eve::asec, a); }
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
asec_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::asec, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
asec_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::asec), t);
}
}
