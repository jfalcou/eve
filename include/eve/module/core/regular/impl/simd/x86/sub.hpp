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
  template< typename T, typename N, callable_options O>
  EVE_FORCEINLINE
  wide<T, N> sub_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr(O::contains(saturated2))
    {
      constexpr auto sup_avx2 = current_api >= avx2;

      if      constexpr( c == category::int16x32  )             return _mm512_subs_epi16(v, w);
      else if constexpr( c == category::uint16x32 )             return _mm512_subs_epu16(v, w);
      else if constexpr( c == category::int8x64   )             return _mm512_subs_epi8 (v, w);
      else if constexpr( c == category::uint8x64  )             return _mm512_subs_epu8 (v, w);
      else if constexpr( sup_avx2 && c == category::int16x16  ) return _mm256_subs_epi16(v, w);
      else if constexpr( sup_avx2 && c == category::uint16x16 ) return _mm256_subs_epu16(v, w);
      else if constexpr( sup_avx2 && c == category::int8x32   ) return _mm256_subs_epi8 (v, w);
      else if constexpr( sup_avx2 && c == category::uint8x32  ) return _mm256_subs_epu8 (v, w);
      else if constexpr( c == category::int16x8   )             return _mm_subs_epi16   (v, w);
      else if constexpr( c == category::uint16x8  )             return _mm_subs_epu16   (v, w);
      else if constexpr( c == category::int8x16   )             return _mm_subs_epi8    (v, w);
      else if constexpr( c == category::uint8x16  )             return _mm_subs_epu8    (v, w);
      else                                                      return sub.behavior(cpu_{}, opts, v, w);
    }
    else
    {
      return sub.behavior(cpu_{}, opts, v, w);
    }
  }

  template<conditional_expr C, typename T, typename N, callable_options O>
  EVE_FORCEINLINE
  wide<T, N> sub_(EVE_REQUIRES(avx512_), C cx, O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    auto src = alternative(cx, v, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr(O::contains(saturated2))
    {
      constexpr auto sup_avx2 = current_api >= avx2;

      if      constexpr( floating_value<T>        )             return sub[cx](v, w);
      else if constexpr( c == category::int16x32  )             return _mm512_mask_subs_epi16(src, m, v, w);
      else if constexpr( c == category::uint16x32 )             return _mm512_mask_subs_epu16(src, m, v, w);
      else if constexpr( c == category::int8x64   )             return _mm512_mask_subs_epi8(src, m, v, w);
      else if constexpr( c == category::uint8x64  )             return _mm512_mask_subs_epu8(src, m, v, w);
      else if constexpr( sup_avx2 && c == category::int16x16  ) return _mm256_mask_subs_epi16(src, m, v, w);
      else if constexpr( sup_avx2 && c == category::uint16x16 ) return _mm256_mask_subs_epu16(src, m, v, w);
      else if constexpr( sup_avx2 && c == category::int8x32   ) return _mm256_mask_subs_epi8(src, m, v, w);
      else if constexpr( sup_avx2 && c == category::uint8x32  ) return _mm256_mask_subs_epu8(src, m, v, w);
      else if constexpr( c == category::int16x8   )             return _mm_mask_subs_epi16(src, m, v, w);
      else if constexpr( c == category::uint16x8  )             return _mm_mask_subs_epu16(src, m, v, w);
      else if constexpr( c == category::int8x16   )             return _mm_mask_subs_epi8(src, m, v, w);
      else if constexpr( c == category::uint8x16  )             return _mm_mask_subs_epu8(src, m, v, w);
      else                                                      return sub.behavior(cpu_{}, opts, v, w);
    }
    else
    {
      if      constexpr( c == category::float32x16) return _mm512_mask_sub_ps   (src, m, v, w);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_sub_ps   (src, m, v, w);
      else if constexpr( c == category::float32x4 ) return _mm_mask_sub_ps      (src, m, v, w);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_sub_pd   (src, m, v, w);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_sub_pd   (src, m, v, w);
      else if constexpr( c == category::float64x2 ) return _mm_mask_sub_pd      (src, m, v, w);
      else if constexpr( match(c,category::int64x8 , category::uint64x8)  ) return _mm512_mask_sub_epi64(src, m, v, w);
      else if constexpr( match(c,category::int64x4 , category::uint64x4)  ) return _mm256_mask_sub_epi64(src, m, v, w);
      else if constexpr( match(c,category::int64x2 , category::uint64x2)  ) return _mm_mask_sub_epi64   (src, m, v, w);
      else if constexpr( match(c,category::int32x16, category::uint32x16) ) return _mm512_mask_sub_epi32(src, m, v, w);
      else if constexpr( match(c,category::int32x8 , category::uint32x8 ) ) return _mm256_mask_sub_epi32(src, m, v, w);
      else if constexpr( match(c,category::int32x4 , category::uint32x4 ) ) return _mm_mask_sub_epi32   (src, m, v, w);
      else if constexpr( match(c,category::int64x2 , category::uint64x2)  ) return _mm_mask_sub_epi64   (src, m, v, w);
      else if constexpr( match(c,category::int16x32, category::uint16x32) ) return _mm512_mask_sub_epi16(src, m, v, w);
      else if constexpr( match(c,category::int16x16, category::uint16x16) ) return _mm256_mask_sub_epi16(src, m, v, w);
      else if constexpr( match(c,category::int16x8 , category::uint16x8 ) ) return _mm_mask_sub_epi16   (src, m, v, w);
      else if constexpr( match(c,category::int8x64 , category::uint8x64 ) ) return _mm512_mask_sub_epi8 (src, m, v, w);
      else if constexpr( match(c,category::int8x32 , category::uint8x32 ) ) return _mm256_mask_sub_epi8 (src, m, v, w);
      else if constexpr( match(c,category::int8x16 , category::uint8x16 ) ) return _mm_mask_sub_epi8    (src, m, v, w);
      else                                                                  return sub.behavior(cpu_{}, opts, v, w);
    }
  }

}

// #include <eve/concept/value.hpp>
// #include <eve/detail/implementation.hpp>

// #include <type_traits>

// namespace eve::detail
// {
// // -----------------------------------------------------------------------------------------------
// // Masked case
// template<conditional_expr C, arithmetic_scalar_value T, typename N>
// EVE_FORCEINLINE wide<T, N>
//                 sub_(EVE_SUPPORTS(sse2_),
//                      C const                         &cx,
//                      wide<T, N> const                &v,
//                      wide<T, N> const                &w) noexcept requires x86_abi<abi_t<T, N>>
// {
//   constexpr auto c = categorize<wide<T, N>>();

//   if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
//   {
//     return sub_(EVE_RETARGET(cpu_), cx, v, w);
//   }
//   else
//   {
//     auto src = alternative(cx, v, as<wide<T, N>> {});
//     auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

//     if constexpr( c == category::float32x16 ) return _mm512_mask_sub_ps(src, m, v, w);
//     else if constexpr( c == category::float64x8 ) return _mm512_mask_sub_pd(src, m, v, w);
//     else if constexpr( c == category::int8x64 ) return _mm512_mask_sub_epi8(src, m, v, w);
//     else if constexpr( c == category::int8x32 ) return _mm256_mask_sub_epi8(src, m, v, w);
//     else if constexpr( c == category::int8x16 ) return _mm_mask_sub_epi8(src, m, v, w);
//     else if constexpr( c == category::int16x32 ) return _mm512_mask_sub_epi16(src, m, v, w);
//     else if constexpr( c == category::int16x16 ) return _mm256_mask_sub_epi16(src, m, v, w);
//     else if constexpr( c == category::int16x8 ) return _mm_mask_sub_epi16(src, m, v, w);
//     else if constexpr( c == category::int32x16 ) return _mm512_mask_sub_epi32(src, m, v, w);
//     else if constexpr( c == category::int32x8 ) return _mm256_mask_sub_epi32(src, m, v, w);
//     else if constexpr( c == category::int32x4 ) return _mm_mask_sub_epi32(src, m, v, w);
//     else if constexpr( c == category::int64x8 ) return _mm512_mask_sub_epi64(src, m, v, w);
//     else if constexpr( c == category::int64x4 ) return _mm256_mask_sub_epi64(src, m, v, w);
//     else if constexpr( c == category::int64x2 ) return _mm_mask_sub_epi64(src, m, v, w);
//     else return sub_(EVE_RETARGET(cpu_), cx, v, w);
//   }
// }

// }
