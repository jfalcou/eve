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

namespace eve::detail
{
  template<typename T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fsnm_(EVE_REQUIRES(sse2_),
                                   O const& opts,
                                   wide<T, N> const& a,
                                   wide<T, N> const& b,
                                   wide<T, N> const& c) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    return fsm[opts](a, minus(b), c);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fsnm_(EVE_REQUIRES(avx512_),
                                   C          const &mask,
                                   O          const &opts,
                                   wide<T, N> const &v,
                                   wide<T, N> const &w,
                                   wide<T, N> const &x) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    // NOTE: As those masked version are at the AVX512 level, they will always uses a variant of
    // hardware VMADD, thus ensuring the pedantic behavior by default, hence why we don't care about
    // PEDANTIC. As usual, we don't care about PROMOTE as we only accept similar types.

    if      constexpr( C::is_complete )               return alternative(mask, v, as{v});
    else if constexpr( !C::has_alternative )
    {
      constexpr auto              c = categorize<wide<T, N>>();
      [[maybe_unused]] auto const m = expand_mask(mask, as{v}).storage().value;
      if ((O::contains(lower) || O::contains(upper))&& floating_value<T>) return if_else(mask, eve::fsnm[opts.drop(condition_key)](v, w, x), v);
      else if constexpr( c == category::float32x16) return _mm512_mask3_fnmsub_ps(w, x, v, m);
      else if constexpr( c == category::float64x8 ) return _mm512_mask3_fnmsub_pd(w, x, v, m);
      else if constexpr( c == category::float32x8 ) return _mm256_mask3_fnmsub_ps(w, x, v, m);
      else if constexpr( c == category::float64x4 ) return _mm256_mask3_fnmsub_pd(w, x, v, m);
      else if constexpr( c == category::float32x8 ) return _mm128_mask3_fnmsub_ps(w, x, v, m);
      else if constexpr( c == category::float64x4 ) return _mm128_mask3_fnmsub_pd(w, x, v, m);
      // No rounding issue with integers, so we just mask over regular FSNM
      else                                          return if_else(mask, eve::fsnm(v, w, x), v);
    }
    else                                            return if_else(mask, eve::fsnm[opts.drop(condition_key)](v, w, x), alternative(mask, v, as{v}));
  }
}
