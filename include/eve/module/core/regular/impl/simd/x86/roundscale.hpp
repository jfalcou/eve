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
#include <eve/module/core/decorator/roundings.hpp>

namespace eve::detail
{

  template<auto S, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> roundscale_(EVE_REQUIRES(avx512_),
                                         O          const & o,
                                         wide<T, N> const & a0,
                                         eve::index_t<S> const & s) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    return roundscale[true_(as(a0))][o](a0, s);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case

  template<auto S, conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> roundscale_(EVE_REQUIRES(avx512_),
                                        C          const &mask,
                                        O          const &o,
                                        wide<T, N> const &a0,
                                        eve::index_t<S> const & ) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    auto const alt = alternative(mask, a0, as(a0));

    if constexpr( C::is_complete)  return alt;
    else if constexpr(S > 15)      return roundscale.behavior(o, a0, S);
    else
    {
      auto          src = alternative(mask, a0, as<wide<T, N>> {});
      auto          m   = expand_mask(mask, as<wide<T, N>> {}).storage().value;
      constexpr int s   = ((S) << 4);

      constexpr auto c = categorize<wide<T, N>>();
      int constexpr V = eve::rounding_mode<O>(eve::to_nearest2) & 3;

      if      constexpr( c == category::float32x16) return _mm512_mask_roundscale_ps(src, m, a0, s+V);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_roundscale_pd(src, m, a0, s+V);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_roundscale_ps(src, m, a0, s+V);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_roundscale_pd(src, m, a0, s+V);
      else if constexpr( c == category::float32x4 ) return _mm_mask_roundscale_ps(src, m, a0, s+V);
      else if constexpr( c == category::float64x2 ) return _mm_mask_roundscale_pd(src, m, a0, s+V);
    }
  }
}
