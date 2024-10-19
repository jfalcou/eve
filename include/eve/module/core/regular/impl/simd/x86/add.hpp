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
#include <eve/module/core/regular/combine.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE upgrade_t<wide<T, N>> add_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires (x86_abi<abi_t<T, N>> && O::contains(widen))
  {
    return add.behavior(as<upgrade_t<wide<T, N>>>{}, cpu_{}, opts, a, b);
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> add_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr(floating_value<T> && (O::contains(lower) || O::contains(upper)))
    {
      if (!O::contains(strict))
      {
        if constexpr(current_api >= avx512)
        {
          auto constexpr dir =(O::contains(lower) ? _MM_FROUND_TO_NEG_INF : _MM_FROUND_TO_POS_INF) |_MM_FROUND_NO_EXC;
          if      constexpr  ( c == category::float64x8  ) return  _mm512_add_round_pd(a, b, dir);
          else if constexpr  ( c == category::float32x16 ) return  _mm512_add_round_ps(a, b, dir);
          else if constexpr  ( c == category::float64x4 ||  c == category::float64x2 ||
                               c == category::float32x8 ||  c == category::float32x4 || c == category::float32x2)
          {
            auto aa = eve::combine(a, a);
            auto bb = eve::combine(b, b);
            auto aapbb = add[opts](aa, bb);
            return slice(aapbb, eve::upper_);
          }
          else                                             return add.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
        }
        else                                               return add.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
      }
      else                                                 return add.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    }
    else if constexpr(O::contains(saturated) && std::integral<T>)
    {
      constexpr auto sup_avx2 = current_api >= avx2;

      if      constexpr( c == category::int16x32  )             return _mm512_adds_epi16(a, b);
      else if constexpr( c == category::uint16x32 )             return _mm512_adds_epu16(a, b);
      else if constexpr( c == category::int8x64   )             return _mm512_adds_epi8 (a, b);
      else if constexpr( c == category::uint8x64  )             return _mm512_adds_epu8 (a, b);
      else if constexpr( sup_avx2 && c == category::int16x16  ) return _mm256_adds_epi16(a, b);
      else if constexpr( sup_avx2 && c == category::uint16x16 ) return _mm256_adds_epu16(a, b);
      else if constexpr( sup_avx2 && c == category::int8x32   ) return _mm256_adds_epi8 (a, b);
      else if constexpr( sup_avx2 && c == category::uint8x32  ) return _mm256_adds_epu8 (a, b);
      else if constexpr( c == category::int16x8   )             return _mm_adds_epi16   (a, b);
      else if constexpr( c == category::uint16x8  )             return _mm_adds_epu16   (a, b);
      else if constexpr( c == category::int8x16   )             return _mm_adds_epi8    (a, b);
      else if constexpr( c == category::uint8x16  )             return _mm_adds_epu8    (a, b);
      else                                                      return add.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    }
    else
    {
      if constexpr  ( c == category::float64x8  ) return _mm512_add_pd(a, b);
      else  if constexpr  ( c == category::float32x16 ) return _mm512_add_ps(a, b);
      else  if constexpr  ( c == category::int64x8    ) return _mm512_add_epi64(a, b);
      else  if constexpr  ( c == category::int32x16   ) return _mm512_add_epi32(a, b);
      else  if constexpr  ( c == category::int16x32   ) return _mm512_add_epi16(a, b);
      else  if constexpr  ( c == category::int8x64    ) return _mm512_add_epi8(a, b);
      else  if constexpr  ( c == category::uint64x8   ) return _mm512_add_epi64(a, b);
      else  if constexpr  ( c == category::uint32x16  ) return _mm512_add_epi32(a, b);
      else  if constexpr  ( c == category::uint16x32  ) return _mm512_add_epi16(a, b);
      else  if constexpr  ( c == category::uint8x64   ) return _mm512_add_epi8(a, b);
      else  if constexpr  ( c == category::float64x2  ) return _mm_add_pd(a, b);
      else  if constexpr  ( c == category::float32x4  ) return _mm_add_ps(a, b);
      else  if constexpr  ( c == category::int64x2    ) return _mm_add_epi64(a, b);
      else  if constexpr  ( c == category::int32x4    ) return _mm_add_epi32(a, b);
      else  if constexpr  ( c == category::int16x8    ) return _mm_add_epi16(a, b);
      else  if constexpr  ( c == category::int8x16    ) return _mm_add_epi8(a, b);
      else  if constexpr  ( c == category::uint64x2   ) return _mm_add_epi64(a, b);
      else  if constexpr  ( c == category::uint32x4   ) return _mm_add_epi32(a, b);
      else  if constexpr  ( c == category::uint16x8   ) return _mm_add_epi16(a, b);
      else  if constexpr  ( c == category::uint8x16   ) return _mm_add_epi8(a, b);
      else  if constexpr  ( c == category::float64x4  ) return _mm256_add_pd(a, b);
      else  if constexpr  ( c == category::float32x8  ) return _mm256_add_ps(a, b);
      else  if constexpr  ( current_api >= avx2 )
      {
        if constexpr  ( c == category::int64x4  ) return _mm256_add_epi64(a, b);
        else  if constexpr  ( c == category::uint64x4 ) return _mm256_add_epi64(a, b);
        else  if constexpr  ( c == category::int32x8  ) return _mm256_add_epi32(a, b);
        else  if constexpr  ( c == category::uint32x8 ) return _mm256_add_epi32(a, b);
        else  if constexpr  ( c == category::int16x16 ) return _mm256_add_epi16(a, b);
        else  if constexpr  ( c == category::uint16x16) return _mm256_add_epi16(a, b);
        else  if constexpr  ( c == category::int8x32  ) return _mm256_add_epi8(a, b);
        else  if constexpr  ( c == category::uint8x32 ) return _mm256_add_epi8(a, b);
      }
      else
      {
        auto [s1, s2] = a.slice();
        auto [o1, o2] = b.slice();
        s1 += o1;
        s2 += o2;
        return wide<T, N>{s1, s2};
      }
    }
  }

  template<conditional_expr C, typename T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> add_(EVE_REQUIRES(avx512_), C cx, O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    auto src = alternative(cx, a, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr(floating_value<T> &&( O::contains(lower) || O::contains(upper)) && !O::contains(strict))
    {
      auto constexpr dir =(O::contains(lower) ? _MM_FROUND_TO_NEG_INF : _MM_FROUND_TO_POS_INF) |_MM_FROUND_NO_EXC;
      if      constexpr  ( c == category::float64x8  ) return  _mm512_mask_add_round_pd (src, m, a, b, dir);
      else if constexpr  ( c == category::float32x16 ) return  _mm512_mask_add_round_ps (src, m, a, b, dir);
      else if constexpr  ( c == category::float64x4 ||  c == category::float64x2 ||
                          c == category::float32x8 ||  c == category::float32x4 || c == category::float32x2)
      {
        auto aa = eve::combine(a, a);
        auto bb = eve::combine(b, b);
        auto aapbb = add[opts.drop(condition_key)](aa, bb);
        auto s =  slice(aapbb, eve::upper_);
        return if_else(cx, s, src);
      }
      else                                             return add.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    }
    else if constexpr(O::contains(saturated))
    {
      constexpr auto sup_avx2 = current_api >= avx2;

      if      constexpr( floating_value<T>        )             return add[cx](a, b);
      else if constexpr( c == category::int16x32  )             return _mm512_mask_adds_epi16(src, m, a, b);
      else if constexpr( c == category::uint16x32 )             return _mm512_mask_adds_epu16(src, m, a, b);
      else if constexpr( c == category::int8x64   )             return _mm512_mask_adds_epi8(src, m, a, b);
      else if constexpr( c == category::uint8x64  )             return _mm512_mask_adds_epu8(src, m, a, b);
      else if constexpr( sup_avx2 && c == category::int16x16  ) return _mm256_mask_adds_epi16(src, m, a, b);
      else if constexpr( sup_avx2 && c == category::uint16x16 ) return _mm256_mask_adds_epu16(src, m, a, b);
      else if constexpr( sup_avx2 && c == category::int8x32   ) return _mm256_mask_adds_epi8(src, m, a, b);
      else if constexpr( sup_avx2 && c == category::uint8x32  ) return _mm256_mask_adds_epu8(src, m, a, b);
      else if constexpr( c == category::int16x8   )             return _mm_mask_adds_epi16(src, m, a, b);
      else if constexpr( c == category::uint16x8  )             return _mm_mask_adds_epu16(src, m, a, b);
      else if constexpr( c == category::int8x16   )             return _mm_mask_adds_epi8(src, m, a, b);
      else if constexpr( c == category::uint8x16  )             return _mm_mask_adds_epu8(src, m, a, b);
      else                                                      return add.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    }
    else
    {
      if      constexpr( c == category::float32x16) return _mm512_mask_add_ps   (src, m, a, b);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_add_ps   (src, m, a, b);
      else if constexpr( c == category::float32x4 ) return _mm_mask_add_ps      (src, m, a, b);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_add_pd   (src, m, a, b);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_add_pd   (src, m, a, b);
      else if constexpr( c == category::float64x2 ) return _mm_mask_add_pd      (src, m, a, b);
      else if constexpr( match(c,category::int64x8 , category::uint64x8)  ) return _mm512_mask_add_epi64(src, m, a, b);
      else if constexpr( match(c,category::int64x4 , category::uint64x4)  ) return _mm256_mask_add_epi64(src, m, a, b);
      else if constexpr( match(c,category::int64x2 , category::uint64x2)  ) return _mm_mask_add_epi64   (src, m, a, b);
      else if constexpr( match(c,category::int32x16, category::uint32x16) ) return _mm512_mask_add_epi32(src, m, a, b);
      else if constexpr( match(c,category::int32x8 , category::uint32x8 ) ) return _mm256_mask_add_epi32(src, m, a, b);
      else if constexpr( match(c,category::int32x4 , category::uint32x4 ) ) return _mm_mask_add_epi32   (src, m, a, b);
      else if constexpr( match(c,category::int64x2 , category::uint64x2)  ) return _mm_mask_add_epi64   (src, m, a, b);
      else if constexpr( match(c,category::int16x32, category::uint16x32) ) return _mm512_mask_add_epi16(src, m, a, b);
      else if constexpr( match(c,category::int16x16, category::uint16x16) ) return _mm256_mask_add_epi16(src, m, a, b);
      else if constexpr( match(c,category::int16x8 , category::uint16x8 ) ) return _mm_mask_add_epi16   (src, m, a, b);
      else if constexpr( match(c,category::int8x64 , category::uint8x64 ) ) return _mm512_mask_add_epi8 (src, m, a, b);
      else if constexpr( match(c,category::int8x32 , category::uint8x32 ) ) return _mm256_mask_add_epi8 (src, m, a, b);
      else if constexpr( match(c,category::int8x16 , category::uint8x16 ) ) return _mm_mask_add_epi8    (src, m, a, b);
      else                                                                  return add.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    }
  }
}
