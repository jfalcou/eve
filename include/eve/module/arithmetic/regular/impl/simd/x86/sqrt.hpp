//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> sqrt_(EVE_SUPPORTS(sse2_), wide<T, N> a0) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

         if constexpr ( c == category::float64x8  ) return _mm512_sqrt_pd(a0);
    else if constexpr ( c == category::float32x16 ) return _mm512_sqrt_ps(a0);
    else if constexpr ( c == category::float64x4  ) return _mm256_sqrt_pd(a0);
    else if constexpr ( c == category::float32x8  ) return _mm256_sqrt_ps(a0);
    else if constexpr ( c == category::float64x2  ) return _mm_sqrt_pd   (a0);
    else if constexpr ( c == category::float32x4  ) return _mm_sqrt_ps   (a0);
  }


  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> sqrt_(EVE_SUPPORTS(sse2_), C const &cx, wide<T, N> const &a0) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return sqrt_(EVE_RETARGET(cpu_),cx,a0);
    }
    else
    {
      auto src  = alternative(cx,a0,as<wide<T, N>>{});
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;

            if constexpr(c == category::float32x16 )  return _mm512_mask_sqrt_ps(src,m, a0);
      else  if constexpr(c == category::float64x8  )  return _mm512_mask_sqrt_pd(src,m, a0);
      else  if constexpr(c == category::float32x8  )  return _mm256_mask_sqrt_ps(src,m, a0);
      else  if constexpr(c == category::float64x4  )  return _mm256_mask_sqrt_pd(src,m, a0);
      else  if constexpr(c == category::float32x4  )  return _mm_mask_sqrt_ps(src,m, a0);
      else  if constexpr(c == category::float64x2  )  return _mm_mask_sqrt_pd(src,m, a0);
    }
  }
}
