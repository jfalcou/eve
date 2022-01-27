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
  EVE_FORCEINLINE wide<T, N> nearest_(EVE_SUPPORTS(sse4_1_), wide<T, N> a0) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr(std::is_same_v<T, double>)
    {
           if constexpr (std::same_as<abi_t<T, N>, x86_512_>) return _mm512_roundscale_pd(a0, _MM_FROUND_TO_NEAREST_INT);
      else if constexpr (std::same_as<abi_t<T, N>, x86_256_>) return _mm256_round_pd     (a0, _MM_FROUND_TO_NEAREST_INT);
      else                                                    return _mm_round_pd        (a0, _MM_FROUND_TO_NEAREST_INT);
    }
    else
    {
           if constexpr (std::same_as<abi_t<T, N>, x86_512_>) return _mm512_roundscale_ps(a0, _MM_FROUND_TO_NEAREST_INT);
      else if constexpr (std::same_as<abi_t<T, N>, x86_256_>) return _mm256_round_ps     (a0, _MM_FROUND_TO_NEAREST_INT);
      else                                                    return _mm_round_ps        (a0, _MM_FROUND_TO_NEAREST_INT);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> nearest_(EVE_SUPPORTS(sse2_), C const &cx, wide<T, N> const &v) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return nearest_(EVE_RETARGET(cpu_),cx,v);
    }
    else
    {
      auto src  = alternative(cx,v,as<wide<T, N>>{});
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;

            if constexpr(c == category::float32x16) return _mm512_mask_roundscale_ps(src,m,v, _MM_FROUND_TO_NEAREST_INT);
      else  if constexpr(c == category::float64x8 ) return _mm512_mask_roundscale_pd(src,m,v, _MM_FROUND_TO_NEAREST_INT);
      else  if constexpr(c == category::float32x8 ) return _mm256_mask_roundscale_pd(src,m,v, _MM_FROUND_TO_NEAREST_INT);
      else  if constexpr(c == category::float64x4 ) return _mm256_mask_roundscale_pd(src,m,v, _MM_FROUND_TO_NEAREST_INT);
      else  if constexpr(c == category::float32x4 ) return _mm_mask_roundscale_pd(src,m,v, _MM_FROUND_TO_NEAREST_INT);
      else  if constexpr(c == category::float64x2 ) return _mm_mask_roundscale_pd(src,m,v, _MM_FROUND_TO_NEAREST_INT);
      else  return if_else(cx,v,src);
    }
  }
}
