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
  EVE_FORCEINLINE wide<T,N> shl_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> v, S s) noexcept
    requires (x86_abi<abi_t<T, N>>)
  {
    constexpr auto c = categorize<wide<T, N>>();
    constexpr bool is_avx2 = current_api >= avx2;

    [[maybe_unused]] auto shft = [](auto a, auto b )
    {
      static constexpr auto half_size = (N::value/2 > 0) ? N::value/2 : 1;
      using i16_t = wide<std::uint16_t, fixed<half_size>>;

      i16_t const masklow(0xff);
      i16_t const maskhi (0xff00);
      auto const xx   =  bit_cast(a, as<i16_t>());
      auto const odd  = (xx << b) & masklow;
      auto const even = ((xx & maskhi) << b) & maskhi;

      return bit_cast(odd + even, as(a));
    };

          if constexpr( c == category::int64x8  ) return _mm512_slli_epi64(v, s);
    else  if constexpr( c == category::int32x16 ) return _mm512_slli_epi32(v, s);
    else  if constexpr( c == category::int16x32 ) return _mm512_slli_epi16(v, s);
    else  if constexpr( c == category::uint64x8 ) return _mm512_slli_epi64(v, s);
    else  if constexpr( c == category::uint32x16) return _mm512_slli_epi32(v, s);
    else  if constexpr( c == category::uint16x32) return _mm512_slli_epi16(v, s);
    else  if constexpr( (c == category::int8x16)  && (N::value != 1)) return shft(v, s);
    else  if constexpr( (c == category::uint8x16) && (N::value != 1)) return shft(v, s);
    else  if constexpr( c == category::int64x2  ) return _mm_slli_epi64(v, s);
    else  if constexpr( c == category::uint64x2 ) return _mm_slli_epi64(v, s);
    else  if constexpr( c == category::int32x4  ) return _mm_slli_epi32(v, s);
    else  if constexpr( c == category::uint32x4 ) return _mm_slli_epi32(v, s);
    else  if constexpr( c == category::int16x8  ) return _mm_slli_epi16(v, s);
    else  if constexpr( c == category::uint16x8 ) return _mm_slli_epi16(v, s);
    else  if constexpr (sizeof(v) == 32)
    {
      if constexpr (is_avx2)
      {
              if constexpr( c == category::int64x4  ) return _mm256_slli_epi64(v, s);
        else  if constexpr( c == category::int32x8  ) return _mm256_slli_epi32(v, s);
        else  if constexpr( c == category::int16x16 ) return _mm256_slli_epi16(v, s);
        else  if constexpr( c == category::int8x32  ) return shft(v, s);
        else  if constexpr( c == category::uint64x4 ) return _mm256_slli_epi64(v, s);
        else  if constexpr( c == category::uint32x8 ) return _mm256_slli_epi32(v, s);
        else  if constexpr( c == category::uint16x16) return _mm256_slli_epi16(v, s);
        else  if constexpr( c == category::uint8x32 ) return shft(v, s);
      }
      else
      {
        auto [ la, ha ] = v.slice();
        return wide<T,N>{ shl(la, s), shl(ha, s) };
      }
    }
    else
    {
      return shl.behavior(as<wide<T, N>>{}, cpu_{}, opts, v, s);
    }
  }

  template<callable_options O, typename T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T,N> shl_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> v, wide<S, N> s) noexcept
    requires (x86_abi<abi_t<T, N>>)
  {
    auto sc = convert(s, as<element_type_t<T>>{});
    constexpr auto c = categorize<wide<T, N>>();
    constexpr bool is_avx2 = current_api >= avx2;

          if constexpr( is_avx2 && c == category::int64x4  ) return _mm256_sllv_epi64(v, sc);
    else  if constexpr( is_avx2 && c == category::int32x8  ) return _mm256_sllv_epi32(v, sc);
    else  if constexpr( is_avx2 && c == category::uint64x4 ) return _mm256_sllv_epi64(v, sc);
    else  if constexpr( is_avx2 && c == category::uint32x8 ) return _mm256_sllv_epi32(v, sc);
    else  if constexpr(            c == category::int64x8  ) return _mm512_sllv_epi64(v, sc);
    else  if constexpr(            c == category::int32x16 ) return _mm512_sllv_epi32(v, sc);
    else  if constexpr(            c == category::int16x32 ) return _mm512_sllv_epi16(v, sc);
    else  if constexpr(            c == category::uint64x8 ) return _mm512_sllv_epi64(v, sc);
    else  if constexpr(            c == category::uint32x16) return _mm512_sllv_epi32(v, sc);
    else  if constexpr(            c == category::uint16x32) return _mm512_sllv_epi16(v, sc);
    else                                                     return shl.behavior(as<wide<T, N>>{}, cpu_{}, opts, v, s);
  }

  // slh[mask](wide_val, wide_mask)
  template<callable_options O, conditional_expr C, integral_scalar_value T, typename S, typename N>
  EVE_FORCEINLINE wide<T,N> shl_(EVE_REQUIRES(avx512_), C const& cx, O const&, wide<T, N> v, wide<S, N> s) noexcept
    requires((sizeof(T) >= 2) && x86_abi<abi_t<T, N>>)
  {
      constexpr auto c = categorize<wide<T, N>>();
      auto src = alternative(cx, v, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;
      auto sc  = convert(s, as<element_type_t<T>>{});

      // perform a logical shift left for ints as it is equivalent to an arithmetic shift left
      if      constexpr( c == category::int16x32 ) return _mm512_mask_sllv_epi16 (src, m, v, sc);
      else if constexpr( c == category::int16x16 ) return _mm256_mask_sllv_epi16 (src, m, v, sc);
      else if constexpr( c == category::int16x8  ) return _mm_mask_sllv_epi16    (src, m, v, sc);

      else if constexpr( c == category::int32x16 ) return _mm512_mask_sllv_epi32 (src, m, v, sc);
      else if constexpr( c == category::int32x8  ) return _mm256_mask_sllv_epi32 (src, m, v, sc);
      else if constexpr( c == category::int32x4  ) return _mm_mask_sllv_epi32    (src, m, v, sc);

      else if constexpr( c == category::int64x8  ) return _mm512_mask_sllv_epi64 (src, m, v, sc);
      else if constexpr( c == category::int64x4  ) return _mm256_mask_sllv_epi64 (src, m, v, sc);
      else if constexpr( c == category::int64x2  ) return _mm_mask_sllv_epi64    (src, m, v, sc);

      else if constexpr( c == category::uint16x32) return _mm512_mask_sllv_epi16 (src, m, v, sc);
      else if constexpr( c == category::uint16x16) return _mm256_mask_sllv_epi16 (src, m, v, sc);
      else if constexpr( c == category::uint16x8 ) return _mm_mask_sllv_epi16    (src, m, v, sc);

      else if constexpr( c == category::uint32x16) return _mm512_mask_sllv_epi32 (src, m, v, sc);
      else if constexpr( c == category::uint32x8 ) return _mm256_mask_sllv_epi32 (src, m, v, sc);
      else if constexpr( c == category::uint32x4 ) return _mm_mask_sllv_epi32    (src, m, v, sc);

      else if constexpr( c == category::uint64x8 ) return _mm512_mask_sllv_epi64 (src, m, v, sc);
      else if constexpr( c == category::uint64x4 ) return _mm256_mask_sllv_epi64 (src, m, v, sc);
      else if constexpr( c == category::uint64x2 ) return _mm_mask_sllv_epi64    (src, m, v, sc);
  }

  // shr[mask](wide_val, imm_mask)
  template<callable_options O, conditional_expr C, integral_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T,N> shl_(EVE_REQUIRES(avx512_), C const& cx, O const&, wide<T, N> v, unsigned int s) noexcept
    requires((sizeof(T) >= 2) && x86_abi<abi_t<T, N>>)
  {
      constexpr auto c = categorize<wide<T, N>>();
      auto src = alternative(cx, v, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      if      constexpr( c == category::int16x32 ) return _mm512_mask_slli_epi16 (src, m, v, s);
      else if constexpr( c == category::int16x16 ) return _mm256_mask_slli_epi16 (src, m, v, s);
      else if constexpr( c == category::int16x8  ) return _mm_mask_slli_epi16    (src, m, v, s);

      else if constexpr( c == category::int32x16 ) return _mm512_mask_slli_epi32 (src, m, v, s);
      else if constexpr( c == category::int32x8  ) return _mm256_mask_slli_epi32 (src, m, v, s);
      else if constexpr( c == category::int32x4  ) return _mm_mask_slli_epi32    (src, m, v, s);

      else if constexpr( c == category::int64x8  ) return _mm512_mask_slli_epi64 (src, m, v, s);
      else if constexpr( c == category::int64x4  ) return _mm256_mask_slli_epi64 (src, m, v, s);
      else if constexpr( c == category::int64x2  ) return _mm_mask_slli_epi64    (src, m, v, s);

      // perform a logical shift left for uints as it is equivalent to an arithmetic shift left
      else if constexpr( c == category::uint16x32) return _mm512_mask_slli_epi16 (src, m, v, s);
      else if constexpr( c == category::uint16x16) return _mm256_mask_slli_epi16 (src, m, v, s);
      else if constexpr( c == category::uint16x8 ) return _mm_mask_slli_epi16    (src, m, v, s);

      else if constexpr( c == category::uint32x16) return _mm512_mask_slli_epi32 (src, m, v, s);
      else if constexpr( c == category::uint32x8 ) return _mm256_mask_slli_epi32 (src, m, v, s);
      else if constexpr( c == category::uint32x4 ) return _mm_mask_slli_epi32    (src, m, v, s);

      else if constexpr( c == category::uint64x8 ) return _mm512_mask_slli_epi64 (src, m, v, s);
      else if constexpr( c == category::uint64x4 ) return _mm256_mask_slli_epi64 (src, m, v, s);
      else if constexpr( c == category::uint64x2 ) return _mm_mask_slli_epi64    (src, m, v, s);
  }
}
