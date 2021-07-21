//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> sub_(EVE_SUPPORTS(sse2_), wide<T, N> v0, wide<T, N> v1) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    return v0 -= v1;
  }

 // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> sub_(EVE_SUPPORTS(sse2_), C const &cx, wide<T, N> const &v, wide<T, N> const &w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return sub_(EVE_RETARGET(cpu_),cx,v,w);
    }
    else
    {
      auto src  = alternative(cx,v,as<wide<T, N>>{});
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;

            if constexpr(c == category::float32x16) return _mm512_mask_sub_ps   (src,m,v,w);
      else  if constexpr(c == category::float64x8 ) return _mm512_mask_sub_pd   (src,m,v,w);
      else  if constexpr(c == category::int8x64   ) return _mm512_mask_sub_epi8(src,m,v,w);
      else  if constexpr(c == category::int8x32   ) return _mm256_mask_sub_epi8(src,m,v,w);
      else  if constexpr(c == category::int8x16   ) return _mm_mask_sub_epi8(src,m,v,w);
      else  if constexpr(c == category::int16x32  ) return _mm512_mask_sub_epi16(src,m,v,w);
      else  if constexpr(c == category::int16x16  ) return _mm256_mask_sub_epi16(src,m,v,w);
      else  if constexpr(c == category::int16x8   ) return _mm_mask_sub_epi16(src,m,v,w);
      else  if constexpr(c == category::int32x16  ) return _mm512_mask_sub_epi32(src,m,v,w);
      else  if constexpr(c == category::int32x8   ) return _mm256_mask_sub_epi32(src,m,v,w);
      else  if constexpr(c == category::int32x4   ) return _mm_mask_sub_epi32(src,m,v,w);
      else  if constexpr(c == category::int64x8   ) return _mm512_mask_sub_epi64(src,m,v,w);
      else  if constexpr(c == category::int64x4   ) return _mm256_mask_sub_epi64(src,m,v,w);
      else  if constexpr(c == category::int64x2   ) return _mm_mask_sub_epi64(src,m,v,w);
      else    return if_else(cx,eve::sub(v, w),src);
    }
  }

}
