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
  EVE_FORCEINLINE wide<T, N> roundscale_(EVE_REQUIRES(avx512_),
                                         O          const & o,
                                         wide<T, N> const & a0,
                                         eve::index_t<S> const &) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr int spv = ((S) << 4) + (eve::rounding_mode<O>(eve::to_nearest) & 3);

    constexpr auto c = categorize<wide<T, N>>();
    if constexpr(S > 15)                          return roundscale.behavior(cpu_{}, o, a0, S);
    else if constexpr( c == category::float32x16) return _mm512_roundscale_ps(a0, spv);
    else if constexpr( c == category::float64x8 ) return _mm512_roundscale_pd(a0, spv);
    else if constexpr( c == category::float32x8 ) return _mm256_roundscale_ps(a0, spv);
    else if constexpr( c == category::float64x4 ) return _mm256_roundscale_pd(a0, spv);
    else if constexpr( c == category::float32x4 ) return _mm_roundscale_ps(a0, spv);
    else if constexpr( c == category::float64x2 ) return _mm_roundscale_pd(a0, spv);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case

  template<auto S, conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> roundscale_(EVE_REQUIRES(avx512_),
                                        C          const &mask,
                                        O          const &o,
                                        wide<T, N> const &a0,
                                        [[maybe_unused]] eve::index_t<S> const& idx) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    auto const alt = alternative(mask, a0, as(a0));

    if constexpr( C::is_complete)  return alt;
    else if constexpr(S > 15)      return roundscale[o][mask].retarget(cpu_{}, a0, idx);
    else
    {
      auto          src = alternative(mask, a0, as<wide<T, N>> {});
      auto          m   = expand_mask(mask, as<wide<T, N>> {}).storage().value;
      constexpr int spv = ((S) << 4) + (eve::rounding_mode<O>(eve::to_nearest) & 3);

      constexpr auto c = categorize<wide<T, N>>();

      if      constexpr( c == category::float32x16) return _mm512_mask_roundscale_ps(src, m, a0, spv);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_roundscale_pd(src, m, a0, spv);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_roundscale_ps(src, m, a0, spv);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_roundscale_pd(src, m, a0, spv);
      else if constexpr( c == category::float32x4 ) return _mm_mask_roundscale_ps(src, m, a0, spv);
      else if constexpr( c == category::float64x2 ) return _mm_mask_roundscale_pd(src, m, a0, spv);
    }
  }
}
