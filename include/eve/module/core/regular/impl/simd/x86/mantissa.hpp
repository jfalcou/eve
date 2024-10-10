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
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/regular/is_finite.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/logical_and.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> mantissa_(EVE_REQUIRES(avx512_), O const&, wide<T, N> w) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    using r_t = wide<T, N>;
    constexpr auto        c = categorize<r_t>();
    constexpr auto interval = _MM_MANT_NORM_1_2;
    constexpr auto sign     = _MM_MANT_SIGN_src;

    r_t r;

    if      constexpr( c == category::float32x16) r = _mm512_getmant_ps(w, interval, sign);
    else if constexpr( c == category::float64x8 ) r = _mm512_getmant_pd(w, interval, sign);
    else if constexpr( c == category::float64x4 ) r = _mm256_getmant_pd(w, interval, sign);
    else if constexpr( c == category::float32x8 ) r = _mm256_getmant_ps(w, interval, sign);
    else if constexpr( c == category::float64x2 ) r = _mm_getmant_pd(w, interval, sign);
    else if constexpr( c == category::float32x4 ) r = _mm_getmant_ps(w, interval, sign);
    if constexpr(O::contains(raw))
      return r;
    else
      return if_else(is_nan(w)||is_eqz(w), w, r);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> mantissa_(EVE_REQUIRES(avx512_), C const& cx, O const& o, wide<T, N> w) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(raw))
    {
      auto src                  = alternative(cx, w, as<wide<T, N>> {});
      if constexpr (C::is_complete) return src;
      else
      {
        constexpr auto        c = categorize<wide<T, N>>();
        auto mm                 = expand_mask(cx, as<wide<T, N>> {});
        mm                      = logical_and(mm, is_nez(w) && is_finite(w));
        auto           m        = mm.storage().value;
        constexpr auto interval = _MM_MANT_NORM_1_2;
        constexpr auto sign     = _MM_MANT_SIGN_src;

        if      constexpr( c == category::float32x16) return _mm512_mask_getmant_ps(src, m, w, interval, sign);
        else if constexpr( c == category::float64x8 ) return _mm512_mask_getmant_pd(src, m, w, interval, sign);
        else if constexpr( c == category::float64x4 ) return _mm256_mask_getmant_pd(src, m, w, interval, sign);
        else if constexpr( c == category::float32x8 ) return _mm256_mask_getmant_ps(src, m, w, interval, sign);
        else if constexpr( c == category::float64x2 ) return _mm_mask_getmant_pd(src, m, w, interval, sign);
        else if constexpr( c == category::float32x4 ) return _mm_mask_getmant_ps(src, m, w, interval, sign);
      }
    }
    else
      return mantissa.behavior(as<wide<T, N>>{}, cpu_{}, o, w);
  }
}
