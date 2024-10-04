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

namespace eve::detail
{
  template<callable_options O, typename T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T, N> shr_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> w, S s) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c          = categorize<wide<T, N>>();
    constexpr bool is_avx2    = current_api >= avx2;
    constexpr bool is_avx512  = current_api >= avx512;

          if constexpr(              c == category::int64x8  ) return _mm512_srai_epi64(w, s);
    else  if constexpr(              c == category::int32x16 ) return _mm512_srai_epi32(w, s);
    else  if constexpr(              c == category::int16x32 ) return _mm512_srai_epi16(w, s);
    else  if constexpr(              c == category::uint64x8 ) return _mm512_srli_epi64(w, s);
    else  if constexpr(              c == category::uint32x16) return _mm512_srli_epi32(w, s);
    else  if constexpr(              c == category::uint16x32) return _mm512_srli_epi16(w, s);
    else  if constexpr( is_avx2   && c == category::int32x8  ) return _mm256_srai_epi32(w, s);
    else  if constexpr( is_avx2   && c == category::int16x16 ) return _mm256_srai_epi16(w, s);
    else  if constexpr( is_avx2   && c == category::uint64x4 ) return _mm256_srli_epi64(w, s);
    else  if constexpr( is_avx2   && c == category::uint32x8 ) return _mm256_srli_epi32(w, s);
    else  if constexpr( is_avx2   && c == category::uint16x16) return _mm256_srli_epi16(w, s);
    else  if constexpr( is_avx512 && c == category::int64x2  ) return _mm_srai_epi64(w, s);
    else  if constexpr(              c == category::int32x4  ) return _mm_srai_epi32(w, s);
    else  if constexpr(              c == category::int16x8  ) return _mm_srai_epi16(w, s);
    else  if constexpr(              c == category::uint64x2 ) return _mm_srli_epi64(w, s);
    else  if constexpr(              c == category::uint32x4 ) return _mm_srli_epi32(w, s);
    else  if constexpr(              c == category::uint16x8 ) return _mm_srli_epi16(w, s);
    else                                                       return shr.behavior(as<wide<T, N>>{}, cpu_{}, opts, w, s);
  }

  template<callable_options O, integral_scalar_value T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T, N> shr_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> w, wide<S, N> s) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c         = categorize<wide<T, N>>();
    constexpr bool is_avx2   = current_api >= avx2;
    constexpr bool is_avx512 = current_api >= avx512;
    auto sc                  = convert(s, as<element_type_t<T>>{});

          if constexpr( is_avx512    && c == category::int64x2  ) return _mm_srav_epi64(w, sc);
    else  if constexpr( is_avx2      && c == category::int32x4  ) return _mm_srav_epi32(w, sc);
    else  if constexpr( is_avx512    && c == category::int16x8  ) return _mm_srav_epi16(w, sc);
    else  if constexpr( is_avx2      && c == category::uint64x2 ) return _mm_srlv_epi64(w, sc);
    else  if constexpr( is_avx2      && c == category::uint32x4 ) return _mm_srlv_epi32(w, sc);
    else  if constexpr( is_avx512    && c == category::uint16x8 ) return _mm_srlv_epi16(w, sc);
    else  if constexpr( is_avx512    && c == category::int64x4  ) return _mm256_srav_epi64(w, sc);
    else  if constexpr( is_avx2      && c == category::int32x8  ) return _mm256_srav_epi32(w, sc);
    else  if constexpr( is_avx512    && c == category::int16x16 ) return _mm256_srav_epi16(w, sc);
    else  if constexpr( is_avx2      && c == category::uint64x4 ) return _mm256_srlv_epi64(w, sc);
    else  if constexpr( is_avx2      && c == category::uint32x8 ) return _mm256_srlv_epi32(w, sc);
    else  if constexpr( is_avx512    && c == category::uint16x16) return _mm256_srlv_epi16(w, sc);
    else  if constexpr(                 c == category::int64x8  ) return _mm512_srav_epi64(w, sc);
    else  if constexpr(                 c == category::int32x16 ) return _mm512_srav_epi32(w, sc);
    else  if constexpr(                 c == category::int16x32 ) return _mm512_srav_epi16(w, sc);
    else  if constexpr(                 c == category::uint64x8 ) return _mm512_srlv_epi64(w, sc);
    else  if constexpr(                 c == category::uint32x16) return _mm512_srlv_epi32(w, sc);
    else  if constexpr(                 c == category::uint16x32) return _mm512_srlv_epi16(w, sc);
    else                                                          return shr.behavior(as<wide<T, N>>{}, cpu_{}, opts, w, s);
  }

  // shr[mask](wide_val, wide_mask)
  template<callable_options O, conditional_expr C, integral_scalar_value T, typename S, typename N>
  EVE_FORCEINLINE wide<T,N> shr_(EVE_REQUIRES(avx512_), C const& cx, O const&, wide<T, N> w, wide<S, N> s) noexcept
    requires((sizeof(T) >= 2) && x86_abi<abi_t<T, N>>)
  {
      constexpr auto c = categorize<wide<T, N>>();
      auto src         = alternative(cx, w, as<wide<T, N>> {});
      auto m           = expand_mask(cx, as<wide<T, N>> {}).storage().value;
      auto sc          = convert(s, as<element_type_t<T>>{});

      // perform an arithmetic shift right for the ints
      if      constexpr( c == category::int16x32 ) return _mm512_mask_srav_epi16 (src, m, w, sc);
      else if constexpr( c == category::int16x16 ) return _mm256_mask_srav_epi16 (src, m, w, sc);
      else if constexpr( c == category::int16x8  ) return _mm_mask_srav_epi16    (src, m, w, sc);

      else if constexpr( c == category::int32x16 ) return _mm512_mask_srav_epi32 (src, m, w, sc);
      else if constexpr( c == category::int32x8  ) return _mm256_mask_srav_epi32 (src, m, w, sc);
      else if constexpr( c == category::int32x4  ) return _mm_mask_srav_epi32    (src, m, w, sc);

      else if constexpr( c == category::int64x8  ) return _mm512_mask_srav_epi64 (src, m, w, sc);
      else if constexpr( c == category::int64x4  ) return _mm256_mask_srav_epi64 (src, m, w, sc);
      else if constexpr( c == category::int64x2  ) return _mm_mask_srav_epi64    (src, m, w, sc);

      // it does not matter for the uints, so just perform a logical shift
      else if constexpr( c == category::uint16x32) return _mm512_mask_srlv_epi16 (src, m, w, sc);
      else if constexpr( c == category::uint16x16) return _mm256_mask_srlv_epi16 (src, m, w, sc);
      else if constexpr( c == category::uint16x8 ) return _mm_mask_srlv_epi16    (src, m, w, sc);

      else if constexpr( c == category::uint32x16) return _mm512_mask_srlv_epi32 (src, m, w, sc);
      else if constexpr( c == category::uint32x8 ) return _mm256_mask_srlv_epi32 (src, m, w, sc);
      else if constexpr( c == category::uint32x4 ) return _mm_mask_srlv_epi32    (src, m, w, sc);

      else if constexpr( c == category::uint64x8 ) return _mm512_mask_srlv_epi64 (src, m, w, sc);
      else if constexpr( c == category::uint64x4 ) return _mm256_mask_srlv_epi64 (src, m, w, sc);
      else if constexpr( c == category::uint64x2 ) return _mm_mask_srlv_epi64    (src, m, w, sc);
  }

  // shr[mask](wide_val, imm_mask)
  template<callable_options O, conditional_expr C, integral_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T,N> shr_(EVE_REQUIRES(avx512_), C const& cx, O const&, wide<T, N> w, unsigned int s) noexcept
    requires((sizeof(T) >= 2) && x86_abi<abi_t<T, N>>)
  {
      constexpr auto c = categorize<wide<T, N>>();
      auto src = alternative(cx, w, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      // perform an arithmetic shift right for the uints to preserve the sign bit
      if      constexpr( c == category::int16x32 ) return _mm512_mask_srai_epi16 (src, m, w, s);
      else if constexpr( c == category::int16x16 ) return _mm256_mask_srai_epi16 (src, m, w, s);
      else if constexpr( c == category::int16x8  ) return _mm_mask_srai_epi16    (src, m, w, s);

      else if constexpr( c == category::int32x16 ) return _mm512_mask_srai_epi32 (src, m, w, s);
      else if constexpr( c == category::int32x8  ) return _mm256_mask_srai_epi32 (src, m, w, s);
      else if constexpr( c == category::int32x4  ) return _mm_mask_srai_epi32    (src, m, w, s);

      else if constexpr( c == category::int64x8  ) return _mm512_mask_srai_epi64 (src, m, w, s);
      else if constexpr( c == category::int64x4  ) return _mm256_mask_srai_epi64 (src, m, w, s);
      else if constexpr( c == category::int64x2  ) return _mm_mask_srai_epi64    (src, m, w, s);

      // perform an logical shift right for the ints, as it does not matter
      else if constexpr( c == category::uint16x32) return _mm512_mask_srli_epi16 (src, m, w, s);
      else if constexpr( c == category::uint16x16) return _mm256_mask_srli_epi16 (src, m, w, s);
      else if constexpr( c == category::uint16x8 ) return _mm_mask_srli_epi16    (src, m, w, s);

      else if constexpr( c == category::uint32x16) return _mm512_mask_srli_epi32 (src, m, w, s);
      else if constexpr( c == category::uint32x8 ) return _mm256_mask_srli_epi32 (src, m, w, s);
      else if constexpr( c == category::uint32x4 ) return _mm_mask_srli_epi32    (src, m, w, s);

      else if constexpr( c == category::uint64x8 ) return _mm512_mask_srli_epi64 (src, m, w, s);
      else if constexpr( c == category::uint64x4 ) return _mm256_mask_srli_epi64 (src, m, w, s);
      else if constexpr( c == category::uint64x2 ) return _mm_mask_srli_epi64    (src, m, w, s);
  }
}
