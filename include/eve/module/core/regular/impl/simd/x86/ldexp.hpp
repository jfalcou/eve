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
  template<floating_scalar_value T, value U, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> ldexp_(EVE_REQUIRES(avx512_), O const& opts, wide<T, N> a0, U a1)
    requires (x86_abi<abi_t<T, N>> && same_lanes_or_scalar<wide<T, N>, U>)
  {
    if constexpr(integral_value<U>)
    {
      return ldexp.behavior(current_api, opts, a0, wide<T, N> { convert(a1, as<T>{}) });
    }
    else if constexpr (scalar_value<U>)
    {
      return ldexp.behavior(current_api, opts, a0, wide<T, N> { a1 });
    }
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
      else if constexpr (std::same_as<T, eve::float16_t>)
      {
        if      constexpr (!detail::supports_fp16_vector_ops) return apply_fp16_as_fp32(eve::ldexp, a0, a1);
        else if constexpr (c == category::float16x32)         return _mm512_scalef_ph(a0, a1);
        else if constexpr (c == category::float16x16)         return _mm256_scalef_ph(a0, a1);
        else if constexpr (c == category::float16x8)          return _mm_scalef_ph(a0, a1);
      }
      else return ldexp.behavior(cpu_{}, opts, a0, a1);
    }
  }

  template<floating_scalar_value T, value U, typename N, conditional_expr C, callable_options O>
  EVE_FORCEINLINE wide<T, N> ldexp_(EVE_REQUIRES(avx512_), C const& mask, O const& opts, wide<T, N> a0, U a1) noexcept
    requires (x86_abi<abi_t<T, N>> && same_lanes_or_scalar<wide<T, N>, U>)
  {
    if constexpr(integral_value<U>)
    {
      return ldexp[opts][mask].retarget(current_api, a0, wide<T, N> { convert(a1, as<T>{}) });
    }
    else if constexpr (scalar_value<U>)
    {
      return ldexp[opts][mask].retarget(current_api, a0, wide<T, N> { a1 });
    }
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
      else if constexpr (std::same_as<T, eve::float16_t>)
      {
        if      constexpr (!detail::supports_fp16_vector_ops) return apply_fp16_as_fp32_masked(eve::ldexp, mask, a0, a1);
        else if constexpr (c == category::float16x32)         return _mm512_mask_scalef_ph(src, m, a0, a1);
        else if constexpr (c == category::float16x16)         return _mm256_mask_scalef_ph(src, m, a0, a1);
        else if constexpr (c == category::float16x8)          return _mm_mask_scalef_ph   (src, m, a0, a1);
      }
      else return ldexp.behavior(cpu_{}, opts, a0, a1);
    }
  }
}
