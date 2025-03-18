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
#include <type_traits>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  sqrt_(EVE_REQUIRES(sse2_),
        O const& opts,
        wide<T, N> a0) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr(O::contains(lower) || O::contains(upper)) return sqrt.behavior(cpu_{}, opts, a0);
    else if constexpr( c == category::float64x8 ) return _mm512_sqrt_pd(a0);
    else if constexpr( c == category::float32x16) return _mm512_sqrt_ps(a0);
    else if constexpr( c == category::float64x4 ) return _mm256_sqrt_pd(a0);
    else if constexpr( c == category::float32x8 ) return _mm256_sqrt_ps(a0);
    else if constexpr( c == category::float64x2 ) return _mm_sqrt_pd(a0);
    else if constexpr( c == category::float32x4 ) return _mm_sqrt_ps(a0);
  }

// -----------------------------------------------------------------------------------------------
// Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> sqrt_(EVE_REQUIRES(avx512_),
                                   C          const& cx,
                                   O          const& opts,
                                   wide<T, N> const& a0) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    auto src = alternative(cx, a0, as<wide<T, N>> {});

    if constexpr( C::is_complete) return src;
    else
    {
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      if constexpr(O::contains(lower) || O::contains(upper)) return sqrt[opts][cx].retarget(cpu_{}, a0);
      else if constexpr( c == category::float32x16) return _mm512_mask_sqrt_ps(src, m, a0);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_sqrt_pd(src, m, a0);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_sqrt_ps(src, m, a0);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_sqrt_pd(src, m, a0);
      else if constexpr( c == category::float32x4 ) return _mm_mask_sqrt_ps(src, m, a0);
      else if constexpr( c == category::float64x2 ) return _mm_mask_sqrt_pd(src, m, a0);
    }
  }
}
