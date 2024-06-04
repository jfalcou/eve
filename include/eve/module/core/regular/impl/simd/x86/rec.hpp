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
#include <eve/module/core/decorator/raw.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> rec_(EVE_REQUIRES(sse2_),
                                  O const&,
                                  wide<T, N> const& v) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(raw2))
    {
      constexpr auto c = categorize<wide<T, N>>();
      if      constexpr( c == category::float32x16 ) return _mm512_rcp14_ps(v);
      else if constexpr( c == category::float64x8 ) return _mm512_rcp14_pd(v);
      else if constexpr( c == category::float32x8 )
      {
        if constexpr( current_api >= avx512 ) return _mm256_rcp14_ps(v);
        else return _mm256_rcp_ps(v);
      }
      else if constexpr( c == category::float64x4 )
      {
        if constexpr( current_api >= avx512 ) return _mm256_rcp14_pd(v);
        else return _mm256_cvtps_pd(_mm_rcp_ps(_mm256_cvtpd_ps(v)));
      }
      else if constexpr( c == category::float32x4 )
      {
        if constexpr( current_api >= avx512 ) return _mm_rcp14_ps(v);
        else return _mm_rcp_ps(v);
      }
      else if constexpr( c == category::float64x2 )
      {
        if constexpr( current_api >= avx512 ) return _mm_rcp14_pd(v);
        else return _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(v)));
      }
    }
    else if constexpr(O::contains(pedantic2))
    {
      auto x = rec[raw2](v);
      x = fma(fnma(x, v, one(eve::as(v))), x, x);
      if constexpr(std::same_as<T, double>)
        x =  fma(fnma(x, v, one(eve::as(v))), x, x);
      return if_else(is_eqz(v),
                     v | inf(eve::as(v)),
                     if_else(is_infinite(v),
                             v & mzero(eve::as(v)),
                             x)
                    );
    }
    else
    {
      auto x = rec[raw2](v);
      if constexpr(std::same_as<T, double>)
        x =  fma(fnma(x, v, one(eve::as(v))), x, x);
       return fma(fnma(x, v, one(eve::as(v))), x, x);
    }

  }

// -----------------------------------------------------------------------------------------------
// Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> rec_(EVE_REQUIRES(sse2_),
                                  C const                & mask,
                                  O const                &,
                                  wide<T, N> const       & a0) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    auto src = alternative(mask, a0, as(a0));

    if constexpr( C::is_complete )                  return src;
    else
    {
      auto m   = expand_mask(mask, as(a0)).storage().value;
      if constexpr(O::contains(raw2))
      {
        if      constexpr( c == category::float32x16) return _mm512_mask_rcp14_ps(src, m, a0);
        else if constexpr( c == category::float64x8 ) return _mm512_mask_rcp14_pd(src, m, a0);
        else if constexpr( c == category::float32x8 ) return _mm256_mask_rcp14_ps(src, m, a0);
        else if constexpr( c == category::float64x4 ) return _mm256_mask_rcp14_pd(src, m, a0);
        else if constexpr( c == category::float32x4 ) return _mm_mask_rcp14_ps(src, m, a0);
        else if constexpr( c == category::float64x2 ) return _mm_mask_rcp14_pd(src, m, a0);
      }
      else  if constexpr(O::contains(pedantic2))
      {
        auto x = rec[mask][raw2](a0);
        x = if_else(mask, fma(fnma(x, a0, one(eve::as(a0))), x, x), a0);
        if constexpr(std::same_as<T, double>)
          x =  fma(fnma(x, a0, one(eve::as(a0))), x, x);
        auto x0    = a0 | inf(eve::as(a0));
        auto xinf  = a0 &  mzero(eve::as(a0));
        x = if_else(is_eqz(a0) && m, x0, x);
        x = if_else(is_infinite(a0) && m , xinf, x);
        return if_else(m, x, a0);
      }
      else
      {
        auto x = rec[mask][raw2](a0);
        x = if_else(mask, fma(fnma(x, a0, one(eve::as(a0))), x, x), a0);
        if constexpr(std::same_as<T, double>)
          x =  if_else(mask,fma(fnma(x, a0, one(eve::as(a0))), x, x), a0);;
        return x;
     }
    }
  }
}
