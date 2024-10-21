//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/true.hpp>

namespace eve::detail
{


  template<auto S, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fracscale_(EVE_REQUIRES(avx512_), O const& o, wide<T, N> w, eve::index_t<S>) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr int spv = ((S) << 4) + (eve::rounding_mode<O>(eve::to_nearest) & 3);

    constexpr auto c = categorize<wide<T, N>>();
    if constexpr(S > 15)                          return fracscale.behavior(as<wide<T, N>>{}, o, w, S);
    else if constexpr( c == category::float32x16) return _mm512_reduce_ps(w, spv);
    else if constexpr( c == category::float64x8 ) return _mm512_reduce_pd(w, spv);
    else if constexpr( c == category::float32x8 ) return _mm256_reduce_ps(w, spv);
    else if constexpr( c == category::float64x4 ) return _mm256_reduce_pd(w, spv);
    else if constexpr( c == category::float32x4 ) return _mm_reduce_ps(w, spv);
    else if constexpr( c == category::float64x2 ) return _mm_reduce_pd(w, spv);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case

  template<auto S, conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fracscale_(EVE_REQUIRES(avx512_), C const& mask, O const& o, wide<T, N> w, eve::index_t<S>) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    auto const alt = alternative(mask, w, as{w});
    if constexpr( C::is_complete)  return alt;
    else if constexpr(S > 15)      return fracscale.behavior(as<wide<T, N>>{}, o, w, S);
    else
    {
      auto          src = alternative(mask, w, as<wide<T, N>> {});
      auto          m   = expand_mask(mask, as<wide<T, N>> {}).storage().value;
      constexpr int spv = ((S) << 4) + (eve::rounding_mode<O>(eve::to_nearest) & 3);
      constexpr auto c = categorize<wide<T, N>>();

      if      constexpr( c == category::float32x16) return _mm512_mask_reduce_ps(src, m, w, spv);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_reduce_pd(src, m, w, spv);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_reduce_ps(src, m, w, spv);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_reduce_pd(src, m, w, spv);
      else if constexpr( c == category::float32x4 ) return _mm_mask_reduce_ps(src, m, w, spv);
      else if constexpr( c == category::float64x2 ) return _mm_mask_reduce_pd(src, m, w, spv);
    }
  }
}
