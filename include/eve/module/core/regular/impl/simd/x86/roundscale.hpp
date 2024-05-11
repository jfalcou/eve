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

#include <type_traits>

namespace eve::detail
{

  template<auto S, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>roundscale_(EVE_SUPPORTS(avx512_),
                                        O const          &o,
                                        wide<T, N> const &a0,
                                        std::integral_constant<int, S> const & ) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    constexpr auto s = ((S) << 4) + rounding_mode<O>(toward_zero2);

    if      constexpr( c == category::float32x16) return _mm512_roundscale_ps(a0, s);
    else if constexpr( c == category::float64x8 ) return _mm512_roundscale_pd(a0, s);
    else if constexpr( c == category::float32x8 ) return _mm256_roundscale_ps(a0, s);
    else if constexpr( c == category::float64x4 ) return _mm256_roundscale_pd(a0, s);
    else if constexpr( c == category::float32x4 ) return _mm_roundscale_ps(a0, s);
    else if constexpr( c == category::float64x2 ) return _mm_roundscale_pd(a0, s);
    else return fracscale.behavior(cpu_{}, o, a0);
  }

  template<auto S, conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> roundscale_(EVE_SUPPORTS(avx512_),
                                        C const          &cx,
                                        O const          &o,
                                        wide<T, N> const &a0,
                                        std::integral_constant<int, S>  const &) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr( C::is_complete) return a0;
    else
    {
      constexpr auto c = categorize<wide<T, N>>();
      auto src = alternative(cx, a0, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;
      constexpr auto s = ((S) << 4) + rounding_mode<O>(toward_zero2);

      if      constexpr( c == category::float32x16) return _mm512_mask_roundscale_ps(src, m, a0, s);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_roundscale_pd(src, m, a0, s);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_roundscale_ps(src, m, a0, s);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_roundscale_pd(src, m, a0, s);
      else if constexpr( c == category::float32x4 ) return _mm_mask_roundscale_ps(src, m, a0, s);
      else if constexpr( c == category::float64x2 ) return _mm_mask_roundscale_pd(src, m, a0, s);
      else return fracscale.behavior(cpu_{}, o, a0);

    }
  }
}
