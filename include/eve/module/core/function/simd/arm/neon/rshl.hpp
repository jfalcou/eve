//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_RSHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_RSHL_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/function/simd/arm/neon/detail/shift.hpp>

#include <type_traits>

namespace eve::detail
{
  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I>
  EVE_FORCEINLINE wide<T, N, neon64_> rshl_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon64_> const &v0,
                                            wide<I, N, neon64_> const &v1) noexcept
  {
    return neon_shifter(v0, v1);
  }

  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I>
  EVE_FORCEINLINE wide<T, N, neon64_>
                  rshl_(EVE_SUPPORTS(neon128_), wide<T, N, neon64_> const &v0, I v1) noexcept
  {
    using i_t = wide<as_integer_t<T, signed>, N>;
    return eve::rshl(v0, i_t(v1));
  }

  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I>
  EVE_FORCEINLINE auto rshl_(EVE_SUPPORTS(neon128_),
                             wide<T, N, neon128_> const &v0,
                             wide<I, N, neon128_> const &v1) noexcept
  {
    return neon_shifter(v0, v1);
  }

  template<integral_real_scalar_value T, typename N, integral_real_scalar_value I>
  EVE_FORCEINLINE auto rshl_(EVE_SUPPORTS(neon128_), wide<T, N, neon128_> const &v0, I v1) noexcept
  {
    using i_t = wide<as_integer_t<T, signed>, N>;
    return eve::rshl(v0, i_t(v1));
  }
}

#endif
