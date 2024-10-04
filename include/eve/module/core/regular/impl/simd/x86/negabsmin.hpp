//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> negabsmin_(EVE_REQUIRES(avx512_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(numeric) || O::contains(pedantic) || O::contains(saturated))
      return negabsmin.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    else
    {
      constexpr auto cat  = categorize<wide<T, N>>();
      constexpr auto ctrl = range_ctrl::min | range_ctrl::sign_set;
      // float
      if constexpr( cat == category::float32x4 ) return _mm_range_ps(a, b, ctrl);
      else if constexpr( cat == category::float32x8 ) return _mm256_range_ps(a, b, ctrl);
      else if constexpr( cat == category::float32x16 ) return _mm512_range_ps(a, b, ctrl);
      // double
      else if constexpr( cat == category::float64x2 ) return _mm_range_pd(a, b, ctrl);
      else if constexpr( cat == category::float64x4 ) return _mm256_range_pd(a, b, ctrl);
      else if constexpr( cat == category::float64x8 ) return _mm512_range_pd(a, b, ctrl);
      else return negabsmin.behavior(as<wide<T, N>>{}, cpu_{}, a, b);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  negabsmin_(EVE_REQUIRES(avx512_), C const& cx, O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(numeric) || O::contains(pedantic) || O::contains(saturated))
      return negabsmin.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    else
    {
      constexpr auto c = categorize<wide<T, N>>();
      auto           src  = alternative(cx, a, as<wide<T, N>> {});
      auto           m    = expand_mask(cx, as<wide<T, N>> {}).storage().value;
      constexpr auto ctrl = range_ctrl::min | range_ctrl::sign_set;

      if constexpr( c == category::float32x16 ) return _mm512_mask_range_ps(src, m, a, b, ctrl);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_range_pd(src, m, a, b, ctrl);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_range_ps(src, m, a, b, ctrl);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_range_pd(src, m, a, b, ctrl);
      else if constexpr( c == category::float32x4 ) return _mm_mask_range_ps(src, m, a, b, ctrl);
      else if constexpr( c == category::float64x2 ) return _mm_mask_range_pd(src, m, a, b, ctrl);
      else return negabsmin.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    }
  }
}
