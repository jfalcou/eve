//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/binarize.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<integral_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> sign_(EVE_SUPPORTS(ssse3_), wide<T, N> a) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

         if constexpr ( current_api >= avx2 && c == category::int32x8   ) return _mm256_sign_epi32(one(eve::as(a)), a);
    else if constexpr ( current_api >= avx2 && c == category::int16x16  ) return _mm256_sign_epi16(one(eve::as(a)), a);
    else if constexpr ( current_api >= avx2 && c == category::int8x32   ) return _mm256_sign_epi8 (one(eve::as(a)), a);
    else if constexpr ( c == category::int32x4                          ) return _mm_sign_epi32   (one(eve::as(a)), a);
    else if constexpr ( c == category::int16x8                          ) return _mm_sign_epi16   (one(eve::as(a)), a);
    else if constexpr ( c == category::int8x16                          ) return _mm_sign_epi8    (one(eve::as(a)), a);
    else                                                                  return sign_(EVE_RETARGET(cpu_), a);
  }
}
