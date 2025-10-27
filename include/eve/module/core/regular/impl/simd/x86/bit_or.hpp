//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/function/bit_cast.hpp>

#include <type_traits>

namespace eve ::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_or_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    constexpr bool i = match(c, category::integer_);

          if constexpr  ( c == category::float64x8  ) return _mm512_or_pd(a, b);
    else  if constexpr  ( c == category::float64x4  ) return _mm256_or_pd(a, b);
    else  if constexpr  ( c == category::float64x2  ) return _mm_or_pd   (a, b);
    else  if constexpr  ( c == category::float32x16 ) return _mm512_or_ps(a, b);
    else  if constexpr  ( c == category::float32x8  ) return _mm256_or_ps(a, b);
    else  if constexpr  ( c == category::float32x4  ) return _mm_or_ps   (a, b);
    else  if constexpr ( match(c, category::float16) )
    {
      constexpr auto tgt = as<as_uinteger_t<wide<T, N>>>{};
      return bit_cast(bit_or.behavior(current_api, opts, bit_cast(a, tgt), bit_cast(b, tgt)), as<wide<T, N>>{});
    }
    else  if constexpr  ( i && std::same_as<abi_t<T, N>,x86_512_> ) return _mm512_or_si512(a, b);
    else  if constexpr  ( i && std::same_as<abi_t<T, N>,x86_256_> )
    {
      if constexpr  (current_api >= avx2) return _mm256_or_si256(a, b);
      else                                return _mm256_castps_si256
                                                 ( _mm256_or_ps ( _mm256_castsi256_ps(a)
                                                                 , _mm256_castsi256_ps(b)
                                                                 )
                                                 );
    }
    else if constexpr (i && std::same_as<abi_t<T, N>, x86_128_>) return _mm_or_si128(a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<callable_options O, conditional_expr C, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_or_(EVE_REQUIRES(avx512_), C const& cx, O const&, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    auto src = alternative(cx, a, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

         if constexpr (c == category::float32x16)  return _mm512_mask_or_ps(src, m, a, b);
    else if constexpr (c == category::float64x8)   return _mm512_mask_or_pd(src, m, a, b);
    else if constexpr (match(c, category::float_)) return if_else(cx, eve::bit_or(a, b), src);
    else if constexpr (c == category::int64x8)     return _mm512_mask_or_epi64(src, m, a, b);
    else if constexpr (c == category::int64x4)     return _mm256_mask_or_epi64(src, m, a, b);
    else if constexpr (c == category::int64x2)     return _mm_mask_or_epi64(src, m, a, b);
    else if constexpr (c == category::int32x16)    return _mm512_mask_or_epi32(src, m, a, b);
    else if constexpr (c == category::int32x8)     return _mm256_mask_or_epi32(src, m, a, b);
    else if constexpr (c == category::int32x4)     return _mm_mask_or_epi32(src, m, a, b);
    else if constexpr (match(c, category::int_))   return if_else(cx, eve::bit_or(a, b), src);
    else if constexpr (c == category::uint64x8)    return _mm512_mask_or_epi64(src, m, a, b);
    else if constexpr (c == category::uint64x4)    return _mm256_mask_or_epi64(src, m, a, b);
    else if constexpr (c == category::uint64x2)    return _mm_mask_or_epi64(src, m, a, b);
    else if constexpr (c == category::uint32x16)   return _mm512_mask_or_epi32(src, m, a, b);
    else if constexpr (c == category::uint32x8)    return _mm256_mask_or_epi32(src, m, a, b);
    else if constexpr (c == category::uint32x4)    return _mm_mask_or_epi32(src, m, a, b);
    else if constexpr (match(c, category::uint_))  return if_else(cx, eve::bit_or(a, b), src);
  }
}
