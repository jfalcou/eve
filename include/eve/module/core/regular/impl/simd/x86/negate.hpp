//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// 128 bits implementation
  template<signed_integral_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> negate_(EVE_REQUIRES(ssse3_),
                                     O const& opts,
                                     wide<T, N> a0,
                                     wide<T, N> a1) noexcept
  requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if( sizeof(T) == 8 ) return negate.behavior(as<wide<T, N>>{}, cpu_{}, opts, a0, a1);
    else if( sizeof(T) == 4 ) return _mm_sign_epi32(a0, a1);
    else if( sizeof(T) == 2 ) return _mm_sign_epi16(a0, a1);
    else if( sizeof(T) == 1 ) return _mm_sign_epi8(a0, a1);
  }

// -----------------------------------------------------------------------------------------------
// 256 bits implementation
  template<signed_integral_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> negate_(EVE_REQUIRES(avx2_),
                                     O const& opts,
                                     wide<T, N> a0,
                                     wide<T, N> a1) noexcept
  requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if( sizeof(T) == 8 ) return negate.behavior(as<wide<T, N>>{}, cpu_{}, opts, a0, a1);
    else if( sizeof(T) == 4 ) return _mm256_sign_epi32(a0, a1);
    else if( sizeof(T) == 2 ) return _mm256_sign_epi16(a0, a1);
    else if( sizeof(T) == 1 ) return _mm256_sign_epi8(a0, a1);
  }
}
