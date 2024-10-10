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
#include <eve/module/core/constant/one.hpp>

#include <type_traits>

namespace eve::detail
{
  template<callable_options O, integral_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> sign_(EVE_REQUIRES(ssse3_), O const&o, wide<T, N> w) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c    = categorize<wide<T, N>>();
    constexpr auto tgt  = as{w};

    if constexpr (std::is_unsigned_v<T>)
    {
      // this provided the best codegen in average, recheck later
      return (w > 0).mask() >> ((sizeof(T) * 8) - 1);
    }
    else
    {
           if constexpr((current_api >= avx512) || (sizeof(T) == 8))        return sign.behavior(as<wide<T, N>>{}, cpu_{}, o, w);
      else if constexpr((current_api >= avx2) && (c == category::int32x8))  return _mm256_sign_epi32(one(tgt), w);
      else if constexpr((current_api >= avx2) && (c == category::int16x16)) return _mm256_sign_epi16(one(tgt), w);
      else if constexpr((current_api >= avx2) && (c == category::int8x32))  return _mm256_sign_epi8 (one(tgt), w);
      else if constexpr((current_api >= avx) && (N::value > 1))
      {
        auto [ l, h ] = w.slice();
        return wide<T,N>(sign(l), sign(h));
      }
      else if constexpr(c == category::int32x4) return _mm_sign_epi32(one(tgt), w);
      else if constexpr(c == category::int16x8) return _mm_sign_epi16(one(tgt), w);
      else if constexpr(c == category::int8x16) return _mm_sign_epi8(one(tgt), w);
      else return sign.behavior(as<wide<T, N>>{}, cpu_{}, o, w);
    }
  }
}
