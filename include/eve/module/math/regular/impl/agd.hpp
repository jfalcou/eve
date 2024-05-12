//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/regular/asinh.hpp>
#include <eve/module/math/regular/tan.hpp>

namespace eve::detail
{

template<ordered_value T>
EVE_FORCEINLINE constexpr auto
agd_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    return 2*atanh(tan(x*half(as(x))));
  }
  else return apply_over(agd, x);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
agd_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::agd, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
agd_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::agd), t);
}
}
