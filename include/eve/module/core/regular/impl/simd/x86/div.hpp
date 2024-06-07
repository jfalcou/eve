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

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> div_(EVE_REQUIRES(avx512_),
                                  C const          &cx,
                                  O const          &o,
                                  wide<T, N> const &v,
                                  wide<T, N> const &w) noexcept requires x86_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(toward_zero2) || O::contains(upward2) || O::contains(downward2) || O::contains(to_nearest2))
      return round[o](div[cx](v, w));
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      auto src = alternative(cx, v, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      if      constexpr( C::is_complete ) return src;
      else if constexpr( c == category::float32x16) return _mm512_mask_div_ps(src, m, v, w);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_div_pd(src, m, v, w);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_div_ps(src, m, v, w);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_div_pd(src, m, v, w);
      else if constexpr( c == category::float32x4 ) return _mm_mask_div_ps(src, m, v, w);
      else if constexpr( c == category::float64x2 ) return _mm_mask_div_pd(src, m, v, w);
      else return abs.behavior(cpu_{}, o, v, w);
    }
  }
}
