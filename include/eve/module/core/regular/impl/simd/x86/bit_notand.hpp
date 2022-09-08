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

#include <type_traits>

namespace eve ::detail
{
// -----------------------------------------------------------------------------------------------
// 128 bits implementation
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                bit_notand_(EVE_SUPPORTS(sse2_),
                            wide<T, N> const                &v0,
                            wide<T, N> const                &v1) noexcept requires std::same_as<abi_t<T, N>, x86_128_>
{
  if constexpr( std::is_same_v<T, float> ) return _mm_andnot_ps(v0, v1);
  else if constexpr( std::is_same_v<T, double> ) return _mm_andnot_pd(v0, v1);
  else if constexpr( std::is_integral_v<T> ) return _mm_andnot_si128(v0, v1);
}

// -----------------------------------------------------------------------------------------------
// 256 bits implementation
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                bit_notand_(EVE_SUPPORTS(avx_),
                            wide<T, N> const                &v0,
                            wide<T, N> const                &v1) noexcept requires std::same_as<abi_t<T, N>, x86_256_>
{
  if constexpr( std::is_same_v<T, float> ) return _mm256_andnot_ps(v0, v1);
  else if constexpr( std::is_same_v<T, double> ) return _mm256_andnot_pd(v0, v1);
  else if constexpr( std::is_integral_v<T> )
  {
    if constexpr( current_api >= avx2 ) return _mm256_andnot_si256(v0, v1);
    else
      return _mm256_castps_si256(
          _mm256_andnot_ps(_mm256_castsi256_ps(v0), _mm256_castsi256_ps(v1)));
  }
}

// -----------------------------------------------------------------------------------------------
// 512 bits implementation
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                bit_notand_(EVE_SUPPORTS(avx512_),
                            wide<T, N> const                &v0,
                            wide<T, N> const                &v1) noexcept requires std::same_as<abi_t<T, N>, x86_512_>
{
  if constexpr( std::is_same_v<T, double> ) return _mm512_andnot_pd(v0, v1);
  else if constexpr( std::is_same_v<T, float> ) return _mm512_andnot_ps(v0, v1);
  else if constexpr( sizeof(T) == 8 ) return _mm512_andnot_epi64(v0, v1);
  else if constexpr( sizeof(T) == 4 ) return _mm512_andnot_epi32(v0, v1);
  else return _mm512_andnot_si512(v0, v1);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                bit_notand_(EVE_SUPPORTS(sse2_),
                            C const                         &cx,
                            wide<T, N> const                &v0,
                            wide<T, N> const                &v1) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
  {
    return bit_notand_(EVE_RETARGET(cpu_), cx, v0, v1);
  }
  else
  {
    auto src = alternative(cx, v0, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr( c == category::float32x16 ) return _mm512_mask_andnot_ps(src, m, v0, v1);
    else if constexpr( c == category::float64x8 ) return _mm512_mask_andnot_pd(src, m, v0, v1);
    else if constexpr( match(c, category::float_) ) return if_else(cx, eve::bit_notand(v0, v1), src);
    else if constexpr( c == category::int64x8 ) return _mm512_mask_andnot_epi64(src, m, v0, v1);
    else if constexpr( c == category::int64x4 ) return _mm256_mask_andnot_epi64(src, m, v0, v1);
    else if constexpr( c == category::int64x2 ) return _mm_mask_andnot_epi64(src, m, v0, v1);
    else if constexpr( c == category::int32x16 ) return _mm512_mask_andnot_epi32(src, m, v0, v1);
    else if constexpr( c == category::int32x8 ) return _mm256_mask_andnot_epi32(src, m, v0, v1);
    else if constexpr( c == category::int32x4 ) return _mm_mask_andnot_epi32(src, m, v0, v1);
    else if constexpr( match(c, category::int_) ) return if_else(cx, eve::bit_notand(v0, v1), src);
    else if constexpr( c == category::uint64x8 ) return _mm512_mask_andnot_epi64(src, m, v0, v1);
    else if constexpr( c == category::uint64x4 ) return _mm256_mask_andnot_epi64(src, m, v0, v1);
    else if constexpr( c == category::uint64x2 ) return _mm_mask_andnot_epi64(src, m, v0, v1);
    else if constexpr( c == category::uint32x16 ) return _mm512_mask_andnot_epi32(src, m, v0, v1);
    else if constexpr( c == category::uint32x8 ) return _mm256_mask_andnot_epi32(src, m, v0, v1);
    else if constexpr( c == category::uint32x4 ) return _mm_mask_andnot_epi32(src, m, v0, v1);
    else if constexpr( match(c, category::uint_) ) return if_else(cx, eve::bit_notand(v0, v1), src);
  }
}
}
