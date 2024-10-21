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
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/mzero.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_nan.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> rec_(EVE_REQUIRES(sse2_), O const& o, wide<T, N> w) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr(O::contains(lower) || O::contains(upper)) return rec.behavior(as<wide<T, N>>{}, cpu_{}, o, w);
    else if constexpr(O::contains(raw))
    {
     if      constexpr( c == category::float32x16) return _mm512_rcp14_ps(w);
      else if constexpr( c == category::float64x8 ) return _mm512_rcp14_pd(w);
      else if constexpr( c == category::float32x8 )
      {
        if constexpr( current_api >= avx512 ) return _mm256_rcp14_ps(w);
        else return _mm256_rcp_ps(w);
      }
      else if constexpr( c == category::float64x4 )
      {
        if constexpr( current_api >= avx512 ) return _mm256_rcp14_pd(w);
        else
        {
          return _mm256_cvtps_pd(_mm_rcp_ps(_mm256_cvtpd_ps(w)));
        }
      }
      else if constexpr( c == category::float32x4 )
      {
        if constexpr( current_api >= avx512 ) return _mm_rcp14_ps(w);
        else return _mm_rcp_ps(w);
      }
      else if constexpr( c == category::float64x2 )
      {
        if constexpr( current_api >= avx512 ) return _mm_rcp14_pd(w);
        else
        {
          return _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(w)));
        }
      }
    }
    else if constexpr(O::contains(pedantic) || current_api < avx512)
    {
      if (current_api >= avx512)
      {
        if      constexpr( c == category::float32x16) return _mm512_div_ps(one(eve::as{w}), w);
        else if constexpr( c == category::float64x8 ) return _mm512_div_pd(one(eve::as{w}), w);
      }
      if (current_api >= avx)
      {
        if      constexpr( c == category::float32x8 ) return _mm256_div_ps(one(eve::as{w}), w);
        else if constexpr( c == category::float64x4 ) return _mm256_div_pd(one(eve::as{w}), w);
      }
      if (current_api >= sse2)
      {
        if      constexpr( c == category::float32x4 ) return _mm_div_ps(one(eve::as{w}), w);
        else if constexpr( c == category::float64x2 ) return _mm_div_pd(one(eve::as{w}), w);
      }
      return rec.behavior(as<wide<T, N>>{}, cpu_{}, o, w);
    }
    else
    {
      auto x = rec[raw](w);
      x = fma(fnma(x, w, one(eve::as{w})), x, x);
      if constexpr(std::same_as<T, double>)
      {
        x =  fma(fnma(x, w, one(eve::as{w})), x, x);
      }
      x =  if_else (is_not_nan(w) && is_nan(x),  x & inf(eve::as{w}), x);
      return if_else(is_eqz(w),
                     w | inf(eve::as{w}),
                     if_else(is_infinite(w),
                             w & mzero(eve::as{w}),
                             x)
                    );
    }
  }

// -----------------------------------------------------------------------------------------------
// Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> rec_(EVE_REQUIRES(avx512_), C const& mask, O const& opts, wide<T, N> w) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    auto src = alternative(mask, w, as{w});

    if constexpr( C::is_complete )                              return src;
    else if constexpr(O::contains(lower) || O::contains(upper)) return rec.behavior(as<wide<T, N>>{}, cpu_{}, opts, w);
    else
    {
      auto m   = expand_mask(mask, as{w}).storage().value;
      if constexpr(O::contains(raw))
      {
        if      constexpr( c == category::float32x16) return _mm512_mask_rcp14_ps(src, m, w);
        else if constexpr( c == category::float64x8 ) return _mm512_mask_rcp14_pd(src, m, w);
        else if constexpr( c == category::float32x8 ) return _mm256_mask_rcp14_ps(src, m, w);
        else if constexpr( c == category::float64x4 ) return _mm256_mask_rcp14_pd(src, m, w);
        else if constexpr( c == category::float32x4 ) return _mm_mask_rcp14_ps(src, m, w);
        else if constexpr( c == category::float64x2 ) return _mm_mask_rcp14_pd(src, m, w);
      }
      else  if constexpr(O::contains(pedantic))
      {
        if constexpr( c == category::float32x16 )
          return _mm512_mask_div_ps(src, m, one(eve::as{w}), w);
        else if constexpr( c == category::float64x8 )
          return _mm512_mask_div_pd(src, m, one(eve::as{w}), w);
        else if constexpr( c == category::float32x8 )
          return _mm256_mask_div_ps(src, m, one(eve::as{w}), w);
        else if constexpr( c == category::float64x4 )
          return _mm256_mask_div_pd(src, m, one(eve::as{w}), w);
        else if constexpr( c == category::float32x4 )
          return _mm_mask_div_ps(src, m, one(eve::as{w}), w);
        else if constexpr( c == category::float64x2 )
          return _mm_mask_div_pd(src, m, one(eve::as{w}), w);
      }
      else
      {
        auto x = rec[mask][raw](w);
        x = if_else(mask, fma(fnma(x, w, one(eve::as{w})), x, x), w);
        if constexpr(std::same_as<T, double>)
        {
          x =  if_else(mask,fma(fnma(x, w, one(eve::as{w})), x, x), w);
        }
        return if_else(is_eqz(w) && m,
                       w | inf(eve::as{w}),
                       if_else(is_infinite(w) && m,
                               w & mzero(eve::as{w}),
                               x)
                      );
      }
    }
  }
}
