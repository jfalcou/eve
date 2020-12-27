//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_notand.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> abs_(EVE_SUPPORTS(sse2_), wide<T, N, ABI> const &v) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();

          if constexpr(c && category::unsigned_  )  return v;
    else  if constexpr(c == category::float32x16 )  return _mm512_abs_ps(v);
    else  if constexpr(c == category::float64x8  )  return _mm512_abs_pd(v);
    else  if constexpr(c && category::float_     )  return bit_notand(mzero(as(v)), v);
    else  if constexpr(c == category::int64x8 )     return _mm512_abs_epi64(v);
    else  if constexpr(c && category::size64_ )     return map(eve::abs, v);
    else  if constexpr(c == category::int32x16)     return _mm512_abs_epi32(v);
    else  if constexpr(c == category::int32x8 )
    {
      if constexpr(current_api >= avx2 )            return _mm256_abs_epi32(v);
      else                                          return aggregate(eve::abs, v);
    }
    else  if constexpr(c == category::int32x4 )
    {
      if constexpr(current_api >= ssse3 )           return _mm_abs_epi32(v);
      else                                          return map(eve::abs, v);
    }
    else  if constexpr(c == category::int16x32)     return _mm512_abs_epi16(v);
    else  if constexpr(c == category::int16x16 )
    {
      if constexpr(current_api >= avx2 )            return _mm256_abs_epi32(v);
      else                                          return aggregate(eve::abs, v);
    }
    else  if constexpr(c == category::int16x8 )
    {
      if constexpr(current_api >= ssse3 )           return _mm_abs_epi16(v);
      else                                          return map(eve::abs, v);
    }
    else  if constexpr(c == category::int8x64 )     return _mm512_abs_epi8(v);
    else  if constexpr(c == category::int8x32 )
    {
      if constexpr(current_api >= avx2 )            return _mm256_abs_epi8(v);
      else                                          return aggregate(eve::abs, v);
    }
    else  if constexpr(c == category::int8x16 )
    {
      if constexpr(current_api >= ssse3 )           return _mm_abs_epi8(v);
      else                                          return map(eve::abs, v);
    }
  }
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE
  wide<T, N, ABI> abs_(EVE_SUPPORTS(sse2_), C const &cx, wide<T, N, ABI> const &v) noexcept
  {
    if constexpr( !ABI::is_wide_logical )
    {
      auto m_abs = [&](auto m, auto src, auto a0)
      {
        constexpr auto c = categorize<wide<T, N, ABI>>();

              if constexpr(c && category::unsigned_ ) return if_else(cx,src,a0);
        else  if constexpr(c == category::float32x16) return _mm512_mask_abs_ps(src,m,a0);
        else  if constexpr(c == category::float64x8 ) return _mm512_mask_abs_pd(src,m,a0);
        else  if constexpr(c && category::float_    ) return if_else(cx,src,a0);
        else  if constexpr(c == category::int64x8   ) return _mm512_mask_abs_epi64(src,m,a0);
        else  if constexpr(c == category::int64x8   ) return _mm256_mask_abs_epi64(src,m,a0);
        else  if constexpr(c == category::int64x8   ) return _mm_mask_abs_epi64(src,m,a0);
        else  if constexpr(c == category::int32x16  ) return  _mm512_mask_abs_epi32(src,m,a0);
        else  if constexpr(c == category::int32x8   ) return  _mm256_mask_abs_epi32(src,m,a0);
        else  if constexpr(c == category::int32x4   ) return  _mm_mask_abs_epi32(src,m,a0);
        else  if constexpr(c == category::int16x32  ) return _mm512_mask_abs_epi16(src,m,a0);
        else  if constexpr(c == category::int16x16  ) return _mm256_mask_abs_epi16(src,m,a0);
        else  if constexpr(c == category::int16x8   ) return _mm_mask_abs_epi16(src,m,a0);
        else  if constexpr(c == category::int8x64   ) return _mm512_mask_abs_epi8(src,m,a0);
        else  if constexpr(c == category::int8x32   ) return _mm256_mask_abs_epi8(src,m,a0);
        else  if constexpr(c == category::int8x16   ) return _mm_mask_abs_epi8(src,m,a0);
      };

      return mask_op( x86_512_{}, cx, eve::abs, m_abs, v );
    }
    else
    {
      return mask_op( cpu_{}, cx, eve::abs, v);
    }
  }
}
