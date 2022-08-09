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
#include <eve/detail/apply_over.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
template<floating_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
ldexp_(EVE_SUPPORTS(avx512_), wide<T, N> a0, wide<T, N> a1) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( c == category::float64x8 ) return _mm512_scalef_pd(a0, a1);
  else if constexpr( c == category::float32x16 ) return _mm512_scalef_ps(a0, a1);
  else if constexpr( c == category::float64x4 ) return _mm256_scalef_pd(a0, a1);
  else if constexpr( c == category::float32x8 ) return _mm256_scalef_ps(a0, a1);
  else if constexpr( c == category::float64x2 ) return _mm_scalef_pd(a0, a1);
  else if constexpr( c == category::float32x4 ) return _mm_scalef_ps(a0, a1);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                ldexp_(EVE_SUPPORTS(avx512_),
                       C const                         &cx,
                       wide<T, N> const                &v,
                       wide<T, N> const                &w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
  {
    return ldexp_(EVE_RETARGET(cpu_), cx, v, w);
  }
  else
  {
    auto src = alternative(cx, v, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr( c == category::float64x8 ) return _mm512_mask_scalef_pd(src, m, v, w);
    else if constexpr( c == category::float32x16 ) return _mm512_mask_scalef_ps(src, m, v, w);
    else if constexpr( c == category::float64x4 ) return _mm256_mask_scalef_pd(src, m, v, w);
    else if constexpr( c == category::float32x8 ) return _mm256_mask_scalef_ps(src, m, v, w);
    else if constexpr( c == category::float64x2 ) return _mm_mask_scalef_pd(src, m, v, w);
    else if constexpr( c == category::float32x4 ) return _mm_mask_scalef_ps(src, m, v, w);
  }
}

}
