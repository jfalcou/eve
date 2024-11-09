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
  EVE_FORCEINLINE upgrade_t<wide<T, N>> sub_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  requires (x86_abi<abi_t<T, N>> && O::contains(widen))
  {
    return sub.behavior(cpu_{}, opts, v, w);
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> sub_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr(O::contains(left))
    {
      return sub[opts.drop(left)](b, a);
    }
    else if constexpr(floating_value<T> && (O::contains(lower) || O::contains(upper)))
    {
      if (!O::contains(strict))
      {
        if constexpr(current_api >= avx512)
        {
          auto constexpr dir =(O::contains(lower) ? _MM_FROUND_TO_NEG_INF : _MM_FROUND_TO_POS_INF) |_MM_FROUND_NO_EXC;
          if      constexpr  ( c == category::float64x8  ) return  _mm512_sub_round_pd (a, b, dir);
          else if constexpr  ( c == category::float32x16 ) return  _mm512_sub_round_ps (a, b, dir);
          else if constexpr  ( c == category::float64x4 ||  c == category::float64x2 ||
                               c == category::float32x8 ||  c == category::float32x4 || c == category::float32x2)
          {
            auto aa = eve::combine(a, a);
            auto bb = eve::combine(b, b);
            auto aapbb = sub[opts](aa, bb);
            return slice(aapbb, eve::upper_);
          }
          else                                             return sub.behavior(cpu_{}, opts, a, b);
        }
        else                                               return sub.behavior(cpu_{}, opts, a, b);
      }
      else                                                 return sub.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr(O::contains(saturated))
    {
      constexpr auto sup_avx2 = current_api >= avx2;

      if      constexpr( c == category::int16x32  )             return _mm512_subs_epi16(a, b);
      else if constexpr( c == category::uint16x32 )             return _mm512_subs_epu16(a, b);
      else if constexpr( c == category::int8x64   )             return _mm512_subs_epi8 (a, b);
      else if constexpr( c == category::uint8x64  )             return _mm512_subs_epu8 (a, b);
      else if constexpr( sup_avx2 && c == category::int16x16  ) return _mm256_subs_epi16(a, b);
      else if constexpr( sup_avx2 && c == category::uint16x16 ) return _mm256_subs_epu16(a, b);
      else if constexpr( sup_avx2 && c == category::int8x32   ) return _mm256_subs_epi8 (a, b);
      else if constexpr( sup_avx2 && c == category::uint8x32  ) return _mm256_subs_epu8 (a, b);
      else if constexpr( c == category::int16x8   )             return _mm_subs_epi16   (a, b);
      else if constexpr( c == category::uint16x8  )             return _mm_subs_epu16   (a, b);
      else if constexpr( c == category::int8x16   )             return _mm_subs_epi8    (a, b);
      else if constexpr( c == category::uint8x16  )             return _mm_subs_epu8    (a, b);
      else                                                      return sub.behavior(cpu_{}, opts, a, b);
    }
    else
    {
            if constexpr  ( c == category::float64x8  ) return _mm512_sub_pd(a, b);
      else  if constexpr  ( c == category::float32x16 ) return _mm512_sub_ps(a, b);
      else  if constexpr  ( c == category::int64x8    ) return _mm512_sub_epi64(a, b);
      else  if constexpr  ( c == category::int32x16   ) return _mm512_sub_epi32(a, b);
      else  if constexpr  ( c == category::int16x32   ) return _mm512_sub_epi16(a, b);
      else  if constexpr  ( c == category::int8x64    ) return _mm512_sub_epi8(a, b);
      else  if constexpr  ( c == category::uint64x8   ) return _mm512_sub_epi64(a, b);
      else  if constexpr  ( c == category::uint32x16  ) return _mm512_sub_epi32(a, b);
      else  if constexpr  ( c == category::uint16x32  ) return _mm512_sub_epi16(a, b);
      else  if constexpr  ( c == category::uint8x64   ) return _mm512_sub_epi8(a, b);
      else  if constexpr  ( c == category::float64x2  ) return _mm_sub_pd(a, b);
      else  if constexpr  ( c == category::float32x4  ) return _mm_sub_ps(a, b);
      else  if constexpr  ( c == category::int64x2    ) return _mm_sub_epi64(a, b);
      else  if constexpr  ( c == category::int32x4    ) return _mm_sub_epi32(a, b);
      else  if constexpr  ( c == category::int16x8    ) return _mm_sub_epi16(a, b);
      else  if constexpr  ( c == category::int8x16    ) return _mm_sub_epi8(a, b);
      else  if constexpr  ( c == category::uint64x2   ) return _mm_sub_epi64(a, b);
      else  if constexpr  ( c == category::uint32x4   ) return _mm_sub_epi32(a, b);
      else  if constexpr  ( c == category::uint16x8   ) return _mm_sub_epi16(a, b);
      else  if constexpr  ( c == category::uint8x16   ) return _mm_sub_epi8(a, b);
      else  if constexpr  ( c == category::float64x4  ) return _mm256_sub_pd(a, b);
      else  if constexpr  ( c == category::float32x8  ) return _mm256_sub_ps(a, b);
      else  if constexpr  ( current_api >= avx2 )
      {
              if constexpr  ( c == category::int64x4  ) return _mm256_sub_epi64(a, b);
        else  if constexpr  ( c == category::uint64x4 ) return _mm256_sub_epi64(a, b);
        else  if constexpr  ( c == category::int32x8  ) return _mm256_sub_epi32(a, b);
        else  if constexpr  ( c == category::uint32x8 ) return _mm256_sub_epi32(a, b);
        else  if constexpr  ( c == category::int16x16 ) return _mm256_sub_epi16(a, b);
        else  if constexpr  ( c == category::uint16x16) return _mm256_sub_epi16(a, b);
        else  if constexpr  ( c == category::int8x32  ) return _mm256_sub_epi8(a, b);
        else  if constexpr  ( c == category::uint8x32 ) return _mm256_sub_epi8(a, b);
      }
      else
      {
        auto [s1, s2] = a.slice();
        auto [o1, o2] = b.slice();
        return wide<T, N>{sub(s1, o1), sub(s2, o2)};
      }
    }
  }

  template<conditional_expr C, typename T, typename N, callable_options O>
  EVE_FORCEINLINE
  wide<T, N> sub_(EVE_REQUIRES(avx512_), C cx, O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if (O::contains(left))
    {
      return sub.behavior(cpu_{}, opts, v, w);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      auto src = alternative(cx, v, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      if constexpr(floating_value<T> &&( O::contains(lower) || O::contains(upper)) && !O::contains(strict))
      {
        if constexpr(current_api >= avx512)
        {
          auto constexpr dir =(O::contains(lower) ? _MM_FROUND_TO_NEG_INF : _MM_FROUND_TO_POS_INF) |_MM_FROUND_NO_EXC;
          if      constexpr  ( c == category::float64x8  ) return  _mm512_mask_sub_round_pd (src, m, v, w, dir);
          else if constexpr  ( c == category::float32x16 ) return  _mm512_mask_sub_round_ps (src, m, v, w, dir);
          else if constexpr  ( c == category::float64x4 ||  c == category::float64x2 ||
                               c == category::float32x8 ||  c == category::float32x4 || c == category::float32x2)
          {
            auto vv = eve::combine(v, w);
            auto ww = eve::combine(w, v);
            auto vvpww = sub[opts.drop(condition_key)](vv, ww);
            auto s =  slice(vvpww, eve::upper_);
            return if_else(cx,s,src);
          }
          else                                             return add.behavior(cpu_{}, opts, v, w);
        }
        else                                               return add.behavior(cpu_{}, opts, v, w);
      }
      else if constexpr(O::contains(saturated))
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
}
