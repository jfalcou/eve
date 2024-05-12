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
#include <eve/module/core/regular/if_else.hpp>

#include <type_traits>

namespace eve::detail
{
template<floating_scalar_value T, typename N, callable_options O>
EVE_FORCEINLINE wide<T, N> ceil_(EVE_REQUIRES(sse4_1_),
                                 O           const& o,
                                 wide<T, N> a0) noexcept
requires x86_abi<abi_t<T, N>>
{
  if constexpr(!O::contains(almost))
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( c == category::float64x8 ) return _mm512_roundscale_pd(a0, _MM_FROUND_CEIL);
    else if constexpr( c == category::float32x16) return _mm512_roundscale_ps(a0, _MM_FROUND_CEIL);
    else if constexpr( c == category::float64x4 ) return _mm256_round_pd(a0, _MM_FROUND_CEIL);
    else if constexpr( c == category::float32x8 ) return _mm256_round_ps(a0, _MM_FROUND_CEIL);
    else if constexpr( c == category::float64x2 ) return _mm_round_pd(a0, _MM_FROUND_CEIL);
    else if constexpr( c == category::float32x4 ) return _mm_round_ps(a0, _MM_FROUND_CEIL);
  }
  else
    return ceil.behavior(cpu_{}, o, a0);
}

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> ceil_(EVE_REQUIRES(avx512_),
                                   C          const& cx,
                                   O          const& o,
                                   wide<T, N> const& v) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr(!O::contains(almost))
    {
      constexpr auto c = categorize<wide<T, N>>();
      auto src = alternative(cx, v, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;
      if constexpr( C::is_complete )              return src;
      else if constexpr( match(c, category::integer_)) return if_else(cx, v, src);
      else if constexpr( c == category::float32x16 )   return _mm512_mask_ceil_ps(src, m, v);
      else if constexpr( c == category::float64x8 )    return _mm512_mask_ceil_pd(src, m, v);
      else if constexpr( match(c, category::float_))   return if_else(cx, eve::ceil(v), src);
    }
    else
      return ceil.behavior(cpu_{}, cx, o, v);
  }
}
