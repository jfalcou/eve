//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
*/
#include <eve/module/core.hpp>
//==================================================================================================
#pragma once


namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> negabsmax_(EVE_SUPPORTS(avx512_),
                                     wide<T, N> const &v0,
                                     wide<T, N> const &v1) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();
    constexpr auto ctrl = range_ctrl::max | range_ctrl::sign_set;
    // float
          if constexpr( cat == category::float32x4 ) return _mm_range_ps(v0, v1, ctrl);
    else  if constexpr( cat == category::float32x8 ) return _mm256_range_ps(v0, v1, ctrl);
    else  if constexpr( cat == category::float32x16) return _mm512_range_ps(v0, v1, ctrl);
    // double
    else  if constexpr( cat == category::float64x2 ) return _mm_range_pd(v0, v1, ctrl);
    else  if constexpr( cat == category::float64x4 ) return _mm256_range_pd(v0, v1, ctrl);
    else  if constexpr( cat == category::float64x8 ) return _mm512_range_pd(v0, v1, ctrl);
    else  return negabsmax_(EVE_RETARGET(cpu_), v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> negabsmax_(EVE_SUPPORTS(avx512_), C const &cx, wide<T, N> const &v, wide<T, N> const &w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return min_(EVE_RETARGET(cpu_),cx,v,w);
    }
    else
    {
      auto src  = alternative(cx,v,as<wide<T, N>>{});
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;
      constexpr auto ctrl = range_ctrl::max | range_ctrl::sign_set;

            if constexpr(c == category::float32x16) return _mm512_mask_range_ps(src,m,v,w,ctrl);
      else  if constexpr(c == category::float64x8 ) return _mm512_mask_range_pd(src,m,v,w,ctrl);
      else  if constexpr(c == category::float32x8)  return _mm256_mask_range_ps(src,m,v,w,ctrl);
      else  if constexpr(c == category::float64x4 ) return _mm256_mask_range_pd(src,m,v,w,ctrl);
      else  if constexpr(c == category::float32x4)  return _mm_mask_range_ps(src,m,v,w,ctrl);
      else  if constexpr(c == category::float64x2 ) return _mm_mask_range_pd(src,m,v,w,ctrl);
      else     return negabsmax_(EVE_RETARGET(cpu_),cx,v,w);
    }
  }
}
