//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/if_else.hpp>

#include <type_traits>

namespace eve::detail
{
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                fma_(EVE_SUPPORTS(avx2_),
                     wide<T, N> const                &a,
                     wide<T, N> const                &b,
                     wide<T, N> const                &c) noexcept requires x86_abi<abi_t<T, N>>
{
  if constexpr( std::is_integral_v<T> ) { return fma_(EVE_RETARGET(cpu_), a, b, c); }
  else
  {
    constexpr auto cat = categorize<wide<T, N>>();

    if constexpr( cat == category::float64x8 ) return _mm512_fmadd_pd(a, b, c);
    else if constexpr( cat == category::float32x16 ) return _mm512_fmadd_ps(a, b, c);
    else if constexpr( supports_fma3 )
    {
      if constexpr( cat == category::float64x4 ) return _mm256_fmadd_pd(a, b, c);
      else if constexpr( cat == category::float64x2 ) return _mm_fmadd_pd(a, b, c);
      else if constexpr( cat == category::float32x8 ) return _mm256_fmadd_ps(a, b, c);
      else if constexpr( cat == category::float32x4 ) return _mm_fmadd_ps(a, b, c);
    }
    else return fma_(EVE_RETARGET(cpu_), a, b, c);
  }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                fma_(EVE_SUPPORTS(avx512_),
                     C const                         &cx,
                     wide<T, N> const                &v,
                     wide<T, N> const                &w,
                     wide<T, N> const                &x) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
  {
    return fma_(EVE_RETARGET(cpu_), cx, v, w, x);
  }
  else
  {
    auto m = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr( !C::has_alternative )
    {
      if constexpr( c == category::float32x16 ) return _mm512_mask_fmadd_ps(v, m, w, x);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_fmadd_pd(v, m, w, x);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_fmadd_ps(v, m, w, x);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_fmadd_pd(v, m, w, x);
      else if constexpr( c == category::float32x4 ) return _mm_mask_fmadd_ps(v, m, w, x);
      else if constexpr( c == category::float64x2 ) return _mm_mask_fmadd_pd(v, m, w, x);
      else return if_else(cx, eve::fma(v, w, x), v);
    }
    else
    {
      auto src = alternative(cx, v, as<wide<T, N>> {});
      return fma_(EVE_RETARGET(cpu_), cx, v, w, x);
    }
  }
}
}
