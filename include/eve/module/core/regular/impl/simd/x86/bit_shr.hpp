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
  // bit_shr[mask](wide_val, wide_mask)
  template<conditional_expr C, integral_scalar_value T, typename S, typename N, callable_options O>
  EVE_FORCEINLINE wide<T,N> bit_shr_(EVE_REQUIRES(avx512_), C const& cx, O const&, wide<T, N> v, wide<S, N> s) noexcept
  requires((sizeof(T) >= 2) && x86_abi<abi_t<T, N>>)
  {
      constexpr auto c = categorize<wide<T, N>>();
      auto src = alternative(cx, v, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      // perform a logical shift right for the ints, arithmetic shift is defined in eve::shr[mask]
      if      constexpr( c == category::int16x32 ) return _mm512_mask_srlv_epi16 (src, m, v, s);
      else if constexpr( c == category::int16x16 ) return _mm256_mask_srlv_epi16 (src, m, v, s);
      else if constexpr( c == category::int16x8  ) return _mm_mask_srlv_epi16    (src, m, v, s);

      else if constexpr( c == category::int32x16 ) return _mm512_mask_srlv_epi32 (src, m, v, s);
      else if constexpr( c == category::int32x8  ) return _mm256_mask_srlv_epi32 (src, m, v, s);
      else if constexpr( c == category::int32x4  ) return _mm_mask_srlv_epi32    (src, m, v, s);

      else if constexpr( c == category::int64x8  ) return _mm512_mask_srlv_epi64 (src, m, v, s);
      else if constexpr( c == category::int64x4  ) return _mm256_mask_srlv_epi64 (src, m, v, s);
      else if constexpr( c == category::int64x2  ) return _mm_mask_srlv_epi64    (src, m, v, s);

      else if constexpr( c == category::uint16x32) return _mm512_mask_srlv_epi16 (src, m, v, s);
      else if constexpr( c == category::uint16x16) return _mm256_mask_srlv_epi16 (src, m, v, s);
      else if constexpr( c == category::uint16x8 ) return _mm_mask_srlv_epi16    (src, m, v, s);

      else if constexpr( c == category::uint32x16) return _mm512_mask_srlv_epi32 (src, m, v, s);
      else if constexpr( c == category::uint32x8 ) return _mm256_mask_srlv_epi32 (src, m, v, s);
      else if constexpr( c == category::uint32x4 ) return _mm_mask_srlv_epi32    (src, m, v, s);

      else if constexpr( c == category::uint64x8 ) return _mm512_mask_srlv_epi64 (src, m, v, s);
      else if constexpr( c == category::uint64x4 ) return _mm256_mask_srlv_epi64 (src, m, v, s);
      else if constexpr( c == category::uint64x2 ) return _mm_mask_srlv_epi64    (src, m, v, s);
  }

  // bit_shr[mask](wide_val, imm_mask)
  template<conditional_expr C, integral_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T,N> bit_shr_(EVE_REQUIRES(avx512_), C const& cx, O const&, wide<T, N> v, unsigned int s) noexcept
  requires((sizeof(T) >= 2) && x86_abi<abi_t<T, N>>)
  {
      constexpr auto c = categorize<wide<T, N>>();
      auto src = alternative(cx, v, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      if      constexpr( c == category::int16x32 ) return _mm512_mask_srli_epi16 (src, m, v, s);
      else if constexpr( c == category::int16x16 ) return _mm256_mask_srli_epi16 (src, m, v, s);
      else if constexpr( c == category::int16x8  ) return _mm_mask_srli_epi16    (src, m, v, s);

      else if constexpr( c == category::int32x16 ) return _mm512_mask_srli_epi32 (src, m, v, s);
      else if constexpr( c == category::int32x8  ) return _mm256_mask_srli_epi32 (src, m, v, s);
      else if constexpr( c == category::int32x4  ) return _mm_mask_srli_epi32    (src, m, v, s);

      else if constexpr( c == category::int64x8  ) return _mm512_mask_srli_epi64 (src, m, v, s);
      else if constexpr( c == category::int64x4  ) return _mm256_mask_srli_epi64 (src, m, v, s);
      else if constexpr( c == category::int64x2  ) return _mm_mask_srli_epi64    (src, m, v, s);

      // perform a logical shift right for the uints too, arithmetic shift is defined in eve::shr[mask]
      else if constexpr( c == category::uint16x32) return _mm512_mask_srli_epi16 (src, m, v, s);
      else if constexpr( c == category::uint16x16) return _mm256_mask_srli_epi16 (src, m, v, s);
      else if constexpr( c == category::uint16x8 ) return _mm_mask_srli_epi16    (src, m, v, s);

      else if constexpr( c == category::uint32x16) return _mm512_mask_srli_epi32 (src, m, v, s);
      else if constexpr( c == category::uint32x8 ) return _mm256_mask_srli_epi32 (src, m, v, s);
      else if constexpr( c == category::uint32x4 ) return _mm_mask_srli_epi32    (src, m, v, s);

      else if constexpr( c == category::uint64x8 ) return _mm512_mask_srli_epi64 (src, m, v, s);
      else if constexpr( c == category::uint64x4 ) return _mm256_mask_srli_epi64 (src, m, v, s);
      else if constexpr( c == category::uint64x2 ) return _mm_mask_srli_epi64    (src, m, v, s);
  }
}
