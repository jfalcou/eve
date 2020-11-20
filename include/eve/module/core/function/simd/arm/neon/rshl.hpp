//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/function/simd/arm/neon/detail/shift.hpp>

// namespace eve::detail
// {
//   template<integral_real_scalar_value T, typename N, integral_real_scalar_value I, arm_abi ABI>
//   EVE_FORCEINLINE wide<T, N, ABI> rshl_(EVE_SUPPORTS(neon128_),
//                                         wide<T, N, ABI> const &v0,
//                                         wide<I, N, ABI> const &v1) noexcept
//   {
//     return neon_shifter(v0, v1);
//   }

//   template<integral_real_scalar_value T, typename N, integral_real_scalar_value I, arm_abi ABI>
//   EVE_FORCEINLINE wide<T, N, ABI> rshl_(EVE_SUPPORTS(neon128_),
//                                         wide<T, N, ABI> const &v0,
//                                         I const &v1) noexcept
//   {
//     using i_t = wide<as_integer_t<T, signed>, N>;
//     return eve::rshl(v0, i_t(v1));
//   }
// }
#include <type_traits>

namespace eve::detail
{
  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I>
  EVE_FORCEINLINE wide<T, N, arm_64_> rshl_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, arm_64_> const &v0,
                                            wide<I, N, arm_64_> const &v1) noexcept
  {
    return neon_shifter(v0, v1);
  }

  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I>
  EVE_FORCEINLINE wide<T, N, arm_64_>
                  rshl_(EVE_SUPPORTS(neon128_), wide<T, N, arm_64_> const &v0, I v1) noexcept
  {
    using i_t = wide<as_integer_t<T, signed>, N>;
    return eve::rshl(v0, i_t(v1));
  }

  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I>
  EVE_FORCEINLINE auto rshl_(EVE_SUPPORTS(neon128_),
                             wide<T, N, arm_128_> const &v0,
                             wide<I, N, arm_128_> const &v1) noexcept
  {
    return neon_shifter(v0, v1);
  }

  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I>
  EVE_FORCEINLINE auto rshl_(EVE_SUPPORTS(neon128_), wide<T, N, arm_128_> const &v0, I v1) noexcept
  {
    using i_t = wide<as_integer_t<T, signed>, N>;
    return eve::rshl(v0, i_t(v1));
  }
}
