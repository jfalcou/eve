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

namespace eve::detail
{
template<floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
rec_(EVE_SUPPORTS(sse2_), raw_type, wide<T, N> const& v) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( c == category::float32x16 ) return _mm512_rcp14_ps(v);
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

template<floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
rec_(EVE_SUPPORTS(sse2_), wide<T, N> const& a0) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( c == category::float32x16 ) return _mm512_div_ps(one(eve::as(a0)), a0);
  else if constexpr( c == category::float64x8 ) return _mm512_div_pd(one(eve::as(a0)), a0);
  else if constexpr( c == category::float32x8 ) return _mm256_div_ps(one(eve::as(a0)), a0);
  else if constexpr( c == category::float64x4 ) return _mm256_div_pd(one(eve::as(a0)), a0);
  else if constexpr( c == category::float32x4 ) return _mm_div_ps(one(eve::as(a0)), a0);
  else if constexpr( c == category::float64x2 ) return _mm_div_pd(one(eve::as(a0)), a0);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                rec_(EVE_SUPPORTS(sse2_),
                     C const                &cx,
                     raw_type,
                     wide<T, N> const                &a0) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
  {
    return rec_(EVE_RETARGET(cpu_), cx, a0);
  }
  else
  {
    auto src = alternative(cx, a0, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr( c == category::float32x16 ) return _mm512_mask_rcp14_ps(src, m, a0);
    else if constexpr( c == category::float64x8 ) return _mm512_mask_rcp14_pd(src, m, a0);
    else if constexpr( c == category::float32x8 ) return _mm256_mask_rcp14_ps(src, m, a0);
    else if constexpr( c == category::float64x4 ) return _mm256_mask_rcp14_pd(src, m, a0);
    else if constexpr( c == category::float32x4 ) return _mm_mask_rcp14_ps(src, m, a0);
    else if constexpr( c == category::float64x2 ) return _mm_mask_rcp14_pd(src, m, a0);
  }
}

template<conditional_expr C, floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
rec_(EVE_SUPPORTS(sse2_), C const& cx, wide<T, N> const& a0) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
  {
    return rec_(EVE_RETARGET(cpu_), cx, a0);
  }
  else
  {
    auto src = alternative(cx, a0, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr( c == category::float32x16 )
      return _mm512_mask_div_ps(src, m, one(eve::as(a0)), a0);
    else if constexpr( c == category::float64x8 )
      return _mm512_mask_div_pd(src, m, one(eve::as(a0)), a0);
    else if constexpr( c == category::float32x8 )
      return _mm256_mask_div_ps(src, m, one(eve::as(a0)), a0);
    else if constexpr( c == category::float64x4 )
      return _mm256_mask_div_pd(src, m, one(eve::as(a0)), a0);
    else if constexpr( c == category::float32x4 )
      return _mm_mask_div_ps(src, m, one(eve::as(a0)), a0);
    else if constexpr( c == category::float64x2 )
      return _mm_mask_div_pd(src, m, one(eve::as(a0)), a0);
  }
}

}
