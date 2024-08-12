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
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/fma.hpp>

#include <type_traits>

namespace eve::detail
{
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fms_(EVE_REQUIRES(avx2_),
                                  O          const  &opts,
                                  wide<T, N> const  &a,
                                  wide<T, N> const  &b,
                                  wide<T, N> const  &c) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    // Integral don't do anything special ----
    if constexpr( std::integral<T> ) return fms.behavior(cpu_{}, opts, a, b, c);
    // PEDANTIC ---
    else if constexpr(O::contains(pedantic) )
    {
      if constexpr( supports_fma3 ) return fms(a, b, c);
      else                          return fms.behavior(cpu_{}, opts, a, b, c);
    }
    // REGULAR ---
    // we don't care about PROMOTE as we only accept similar types.
    else
    {
      constexpr auto cat = categorize<wide<T, N>>();

      if      constexpr( cat == category::float64x8 )  return _mm512_fmsub_pd(a, b, c);
      else if constexpr( cat == category::float32x16 ) return _mm512_fmsub_ps(a, b, c);
      else if constexpr( supports_fma3 )
      {
        if      constexpr( cat == category::float64x4 ) return _mm256_fmsub_pd(a, b, c);
        else if constexpr( cat == category::float64x2 ) return _mm_fmsub_pd(a, b, c);
        else if constexpr( cat == category::float32x8 ) return _mm256_fmsub_ps(a, b, c);
        else if constexpr( cat == category::float32x4 ) return _mm_fmsub_ps(a, b, c);
      }
      else return fma(a, b, -c);
    }
  }

// -----------------------------------------------------------------------------------------------
// Masked case
  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fms_(EVE_REQUIRES(avx512_),
                                  C          const &mask,
                                  O          const &,
                                  wide<T, N> const &v,
                                  wide<T, N> const &w,
                                  wide<T, N> const &x) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    // NOTE: As those masked version are at the AVX512 level, they will always uses a variant of
    // hardware VMADD, thus ensuring the pedantic behavior by default, hence why we don't care about
    // PEDANTIC. As usual, we don't care about PROMOTE as we only accept similar types.

    if      constexpr( C::is_complete )            return alternative(mask, v, as(v));
    else if constexpr( !C::has_alternative )
    {
      constexpr auto              c = categorize<wide<T, N>>();
      [[maybe_unused]] auto const m = expand_mask(mask, as(v)).storage().value;

      if      constexpr( c == category::float32x16) return _mm512_mask_fmsub_ps(v, m, w, x);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_fmsub_pd(v, m, w, x);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_fmsub_ps(v, m, w, x);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_fmsub_pd(v, m, w, x);
      else if constexpr( c == category::float32x4 ) return _mm_mask_fmsub_ps(v, m, w, x);
      else if constexpr( c == category::float64x2 ) return _mm_mask_fmsub_pd(v, m, w, x);
      // No rounding issue with integers, so we just mask over regular FMA
      else                                          return if_else(mask, eve::fms(v, w, x), v);
    }
    else                                            return if_else(mask, eve::fms(v, w, x), alternative(mask, v, as(v)));
  }
}
