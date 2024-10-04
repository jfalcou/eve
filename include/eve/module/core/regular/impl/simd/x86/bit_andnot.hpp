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
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/if_else.hpp>

#include <type_traits>

namespace eve ::detail
{
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> bit_andnot_(EVE_REQUIRES(sse2_), O const&, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    constexpr bool i = match(c, category::integer_);

    if constexpr( c == category::float64x8 ) return _mm512_andnot_pd(b, a);
    else if constexpr( c == category::float64x4 ) return _mm256_andnot_pd(b, a);
    else if constexpr( c == category::float64x2 ) return _mm_andnot_pd(b, a);
    else if constexpr( c == category::float32x16 ) return _mm512_andnot_ps(b, a);
    else if constexpr( c == category::float32x8 ) return _mm256_andnot_ps(b, a);
    else if constexpr( c == category::float32x4 ) return _mm_andnot_ps(b, a);
    else if constexpr( i && std::same_as<abi_t<T, N>, x86_128_> ) return _mm_andnot_si128(b, a);
    else if constexpr( i && std::same_as<abi_t<T, N>, x86_256_> )
    {
      if constexpr( current_api >= avx2 ) return _mm256_andnot_si256(b, a);
      else
        return _mm256_castps_si256(
          _mm256_andnot_ps(_mm256_castsi256_ps(b), _mm256_castsi256_ps(a)));
    }
    else if constexpr( i && std::same_as<abi_t<T, N>, x86_512_> ) return _mm512_andnot_si512(b, a);
    else return bit_andnot.behavior(as<wide<T, N>>{}, cpu_{}, b, a);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> bit_andnot_(EVE_REQUIRES(avx512_), C const& cx, O const&, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    auto src = alternative(cx, a, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr( c == category::float32x16 ) return _mm512_mask_andnot_ps(src, m, b, a);
    else if constexpr( c == category::float64x8 ) return _mm512_mask_andnot_pd(src, m, b, a);
    else if constexpr( match(c, category::float_) ) return if_else(cx, eve::bit_andnot(a, b), src);
    else if constexpr( c == category::int64x8 ) return _mm512_mask_andnot_epi64(src, m, b, a);
    else if constexpr( c == category::int64x4 ) return _mm256_mask_andnot_epi64(src, m, b, a);
    else if constexpr( c == category::int64x2 ) return _mm_mask_andnot_epi64(src, m, b, a);
    else if constexpr( c == category::int32x16 ) return _mm512_mask_andnot_epi32(src, m, b, a);
    else if constexpr( c == category::int32x8 ) return _mm256_mask_andnot_epi32(src, m, b, a);
    else if constexpr( c == category::int32x4 ) return _mm_mask_andnot_epi32(src, m, b, a);
    else if constexpr( match(c, category::int_) ) return if_else(cx, eve::bit_andnot(a, b), src);
    else if constexpr( c == category::uint64x8 ) return _mm512_mask_andnot_epi64(src, m, b, a);
    else if constexpr( c == category::uint64x4 ) return _mm256_mask_andnot_epi64(src, m, b, a);
    else if constexpr( c == category::uint64x2 ) return _mm_mask_andnot_epi64(src, m, b, a);
    else if constexpr( c == category::uint32x16 ) return _mm512_mask_andnot_epi32(src, m, b, a);
    else if constexpr( c == category::uint32x8 ) return _mm256_mask_andnot_epi32(src, m, b, a);
    else if constexpr( c == category::uint32x4 ) return _mm_mask_andnot_epi32(src, m, b, a);
    else if constexpr( match(c, category::uint_) ) return if_else(cx, eve::bit_andnot(a, b), src);
  }
}
