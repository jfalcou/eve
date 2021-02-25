//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/real/core/function/regular/simd/arm/neon/detail/shift.hpp>

namespace eve::detail
{
  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rshl_(EVE_SUPPORTS(neon128_),
                                        wide<T, N, ABI> const &v0,
                                        wide<I, N, ABI> const &v1) noexcept
  {
    return neon_shifter(v0, v1);
  }

  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rshl_(EVE_SUPPORTS(neon128_),
                                        wide<T, N, ABI> const &v0,
                                        I const &v1) noexcept
  {
    using i_t = wide<as_integer_t<T, signed>, N>;
    return eve::rshl(v0, i_t(v1));
  }
}
