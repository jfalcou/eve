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
  template<floating_scalar_value T, scalar_value U, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  ldexp_(EVE_REQUIRES(avx512_), O const& opts, wide<T, N> a0, wide<U, N> a1) noexcept requires x86_abi<abi_t<T, N>>
  {
    if constexpr(std::integral<U>)  return ldexp[opts](a0, convert(a1,as<T>{}));
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      // We don't handle pedantic as this is done via the intrinsic
      if      constexpr( c == category::float64x8 ) return _mm512_scalef_pd(a0, a1);
      else if constexpr( c == category::float64x4 ) return _mm256_scalef_pd(a0, a1);
      else if constexpr( c == category::float64x2 ) return _mm_scalef_pd(a0, a1);
      else if constexpr( c == category::float32x16) return _mm512_scalef_ps(a0, a1);
      else if constexpr( c == category::float32x8 ) return _mm256_scalef_ps(a0, a1);
      else if constexpr( c == category::float32x4 ) return _mm_scalef_ps(a0, a1);
    }
  }

  template<floating_scalar_value T, scalar_value U, typename N, conditional_expr C, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  ldexp_(EVE_REQUIRES(avx512_), C const& mask, O const& opts, wide<T, N> a0, wide<U, N> a1) noexcept requires x86_abi<abi_t<T, N>>
  {
    if constexpr(std::integral<U>)  return ldexp[opts](a0, convert(a1,as<T>{}));
    else
    {
      auto src = alternative(mask, a0, as<wide<T, N>> {});
      auto m   = expand_mask(mask, as<wide<T, N>> {}).storage().value;

      constexpr auto c = categorize<wide<T, N>>();
      // We don't handle pedantic as this is done via the intrinsic
      if      constexpr( c == category::float64x8 ) return _mm512_mask_scalef_pd(src, m, a0, a1);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_scalef_pd(src, m, a0, a1);
      else if constexpr( c == category::float64x2 ) return _mm_mask_scalef_pd   (src, m, a0, a1);
      else if constexpr( c == category::float32x16) return _mm512_mask_scalef_ps(src, m, a0, a1);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_scalef_ps(src, m, a0, a1);
      else if constexpr( c == category::float32x4 ) return _mm_mask_scalef_ps   (src, m, a0, a1);
    }
  }
}
