//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/constant/mzero.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/bit_notand.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  abs_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> const& v) noexcept requires x86_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(saturated))
    {
      return abs.behavior(cpu_{}, opts, v);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      if      constexpr( match(c, category::unsigned_)  ) return v;
      else if constexpr( c == category::float32x16      ) return _mm512_abs_ps(v);
      else if constexpr( c == category::float64x8       ) return _mm512_abs_pd(v);
      else if constexpr( match(c, category::float_)     ) return bit_notand(mzero(as(v)), v);
      else if constexpr( c == category::int64x8         ) return _mm512_abs_epi64(v);
      else if constexpr( match(c, category::size64_)    ) return map(eve::abs, v);
      else if constexpr( c == category::int32x16        ) return _mm512_abs_epi32(v);
      else if constexpr( c == category::int32x8 )
      {
        if constexpr( current_api >= avx2 ) return _mm256_abs_epi32(v); else return slice_apply(eve::abs, v);
      }
      else if constexpr( c == category::int32x4 )
      {
        if constexpr( current_api >= ssse3 ) return _mm_abs_epi32(v);
        else
        {
          auto s = _mm_srai_epi32(v, 31);
          return wide<T, N> {_mm_sub_epi32(_mm_xor_si128(v, s), s)};
        }
      }
      else if constexpr( c == category::int16x32 ) return _mm512_abs_epi16(v);
      else if constexpr( c == category::int16x16 )
      {
        if constexpr( current_api >= avx2 ) return _mm256_abs_epi16(v);
        else return slice_apply(eve::abs, v);
      }
      else if constexpr( c == category::int16x8 )
      {
        if constexpr( current_api >= ssse3 ) return _mm_abs_epi16(v); else return _mm_max_epi16(v, -v);
      }
      else if constexpr( c == category::int8x64 ) return _mm512_abs_epi8(v);
      else if constexpr( c == category::int8x32 )
      {
        if constexpr( current_api >= avx2 ) return _mm256_abs_epi8(v); else return slice_apply(eve::abs, v);
      }
      else if constexpr( c == category::int8x16 )
      {
        if constexpr( current_api >= ssse3 ) return _mm_abs_epi8(v); else return _mm_min_epu8(v, -v);
      }
    }
  }

  template<arithmetic_scalar_value T, typename N, conditional_expr C, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  abs_(EVE_REQUIRES(avx512_), C const& mask, O const&,  wide<T, N> const& v) noexcept requires x86_abi<abi_t<T, N>>
  {
    auto const            s = alternative(mask, v, as(v));
    [[maybe_unused]] auto m = expand_mask(mask, as(v)).storage().value;
    constexpr auto        c = categorize<wide<T, N>>();

    if      constexpr( C::is_complete )               return s;
    else if constexpr( match(c, category::unsigned_)) return if_else(mask, v, s);
    else if constexpr( c == category::float32x16    ) return _mm512_mask_abs_ps(s, m, v);
    else if constexpr( c == category::float64x8     ) return _mm512_mask_abs_pd(s, m, v);
    else if constexpr( match(c, category::float_)   ) return if_else(mask, eve::abs(v), s);
    else if constexpr( c == category::int64x8       ) return _mm512_mask_abs_epi64(s, m, v);
    else if constexpr( c == category::int64x4       ) return _mm256_mask_abs_epi64(s, m, v);
    else if constexpr( c == category::int64x2       ) return _mm_mask_abs_epi64   (s, m, v);
    else if constexpr( c == category::int32x16      ) return _mm512_mask_abs_epi32(s, m, v);
    else if constexpr( c == category::int32x8       ) return _mm256_mask_abs_epi32(s, m, v);
    else if constexpr( c == category::int32x4       ) return _mm_mask_abs_epi32   (s, m, v);
    else if constexpr( c == category::int16x32      ) return _mm512_mask_abs_epi16(s, m, v);
    else if constexpr( c == category::int16x16      ) return _mm256_mask_abs_epi16(s, m, v);
    else if constexpr( c == category::int16x8       ) return _mm_mask_abs_epi16   (s, m, v);
    else if constexpr( c == category::int8x64       ) return _mm512_mask_abs_epi8 (s, m, v);
    else if constexpr( c == category::int8x32       ) return _mm256_mask_abs_epi8 (s, m, v);
    else if constexpr( c == category::int8x16       ) return _mm_mask_abs_epi8    (s, m, v);
  }
}
