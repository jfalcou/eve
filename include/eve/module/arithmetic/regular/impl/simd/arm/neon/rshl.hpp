//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/arithmetic/regular/impl/simd/arm/neon/detail/shift.hpp>

namespace eve::detail
{
  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I>
  EVE_FORCEINLINE wide<T, N> rshl_(EVE_SUPPORTS(neon128_),
                                        wide<T, N> const &v0,
                                        wide<I, N> const &v1) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return neon_shifter(v0, v1);
  }

  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I>
  EVE_FORCEINLINE wide<T, N> rshl_(EVE_SUPPORTS(neon128_),
                                        wide<T, N> const &v0,
                                        I const &v1) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    using i_t = wide<as_integer_t<T, signed>, N>;
    return eve::rshl(v0, i_t(v1));
  }
}
