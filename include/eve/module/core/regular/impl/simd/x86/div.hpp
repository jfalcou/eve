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

  template<callable_options O, plain_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> div_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {  
    if constexpr (O::contains(saturated2))
    {
      return div.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr (O::contains(toward_zero) || O::contains(upward) || O::contains(downward) || O::contains(to_nearest))
    {
      return div.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

            if constexpr  ( c == category::float64x8  ) return _mm512_div_pd(a, b);
      else  if constexpr  ( c == category::float64x4  ) return _mm256_div_pd(a, b);
      else  if constexpr  ( c == category::float64x2  ) return _mm_div_pd(a, b);
      else  if constexpr  ( c == category::float32x16 ) return _mm512_div_ps(a, b);
      else  if constexpr  ( c == category::float32x8  ) return _mm256_div_ps(a, b);
      else  if constexpr  ( c == category::float32x4  ) return _mm_div_ps(a, b);
      else  if constexpr  ( c == category::int32x4 && current_api >= avx  )
      {
        auto dividend = _mm256_cvtepi32_pd(a);
        auto divisor  = _mm256_cvtepi32_pd(b);
        return _mm256_cvttpd_epi32(_mm256_div_pd(dividend, divisor));
      }
      else
      {
        auto s = a;
        constexpr auto sdiv = [](auto a, auto b) { return a /= b; };
        if constexpr( N::value >= 2  )  return aggregate(sdiv, s, b);
        else                            return map(sdiv, s, b);
      }
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> div_(EVE_REQUIRES(avx512_),
                                  C const          &cx,
                                  O const          &o,
                                  wide<T, N> v,
                                  wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(saturated2))
    {
      return div.behavior(cpu_{}, o, v, w);
    }
    else if constexpr (O::contains(toward_zero) || O::contains(upward) || O::contains(downward) || O::contains(to_nearest))
    {
      return round[o](div[cx](v, w));
    }
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
