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

#include <iostream>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> mantissa_(EVE_SUPPORTS(avx512_),
                                       O          const&,
                                       wide<T, N> const& a0) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    std::cout << "icitte" << std::endl;
    constexpr auto        c = categorize<wide<T, N>>();
    constexpr auto interval = _MM_MANT_NORM_1_2;
    constexpr auto sign     = _MM_MANT_SIGN_src;

    if      constexpr( c == category::float32x16) return _mm512_getmant_ps(a0, interval, sign);
    else if constexpr( c == category::float64x8 ) return _mm512_getmant_pd(a0, interval, sign);
    else if constexpr( c == category::float64x4 ) return _mm256_getmant_pd(a0, interval, sign);
    else if constexpr( c == category::float32x8 ) return _mm256_getmant_ps(a0, interval, sign);
    else if constexpr( c == category::float64x2 ) return _mm_getmant_pd(a0, interval, sign);
    else if constexpr( c == category::float32x4 ) return _mm_getmant_ps(a0, interval, sign);
  }

// -----------------------------------------------------------------------------------------------
// Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> mantissa_(EVE_SUPPORTS(avx512_),
                                       C          const &cx,
                                       O          const &,
                                       wide<T, N> const &v) noexcept
  requires x86_abi<abi_t<T, N>>
  {

    auto src                  = alternative(cx, v, as<wide<T, N>> {});
    if constexpr( C::is_complete ) return src;
    else
    {
      constexpr auto        c = categorize<wide<T, N>>();
      auto mm                 = expand_mask(cx, as<wide<T, N>> {});
      mm                      = logical_and(mm, is_nez(v) && is_finite(v));
      auto           m        = mm.storage().value;
      constexpr auto interval = _MM_MANT_NORM_1_2;
      constexpr auto sign     = _MM_MANT_SIGN_src;

      if      constexpr( c == category::float32x16) return _mm512_mask_getmant_ps(src, m, v, interval, sign);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_getmant_pd(src, m, v, interval, sign);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_getmant_pd(src, m, v, interval, sign);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_getmant_ps(src, m, v, interval, sign);
      else if constexpr( c == category::float64x2 ) return _mm_mask_getmant_pd(src, m, v, interval, sign);
      else if constexpr( c == category::float32x4 ) return _mm_mask_getmant_ps(src, m, v, interval, sign);
    }
  }
}
