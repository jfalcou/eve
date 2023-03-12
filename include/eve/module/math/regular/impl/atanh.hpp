//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/log1p.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE auto
atanh_(EVE_SUPPORTS(cpu_), const T& x) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto absx = eve::abs(x);
    auto t    = absx + absx;
    auto z1   = oneminus(absx);
    auto test = absx < half(eve::as<T>());
    auto tmp  = if_else(test, absx, t) / z1;
    if constexpr( scalar_value<T> ) tmp = test ? fma(t, tmp, t) : tmp;
    else tmp = if_else(test, fma(t, tmp, t), tmp);
    return signnz(x)*half(eve::as<T>()) * log1p(tmp);
  }
  else return apply_over(atanh, x);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
atanh_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::atanh, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
atanh_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::atanh), t);
}
}
