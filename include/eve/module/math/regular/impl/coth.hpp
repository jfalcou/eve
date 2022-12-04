//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/expm1.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE auto
coth_(EVE_SUPPORTS(cpu_), const T& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x = eve::abs(a0 + a0);
    auto t = rec(expm1(x));
    auto r = fma(T(2), t, T(1));
    return copysign(r, a0);
  }
  else return apply_over(coth, a0);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
coth_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::coth, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
coth_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::coth), t);
}
}
