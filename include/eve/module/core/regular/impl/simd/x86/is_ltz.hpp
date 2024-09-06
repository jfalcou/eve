//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  // Generate better code on x86 than just comparing to 0
  template<signed_integral_value T, typename N, callable_options O>
  EVE_FORCEINLINE constexpr auto
  is_ltz_(EVE_REQUIRES(sse2_), O const &, wide<T, N> const& v) noexcept
  requires(sizeof(T) < 8 && x86_abi<abi_t<T, N>> && abi_t<T, N>::is_wide_logical)
  {
    using l_t            = as_logical_t<wide<T, N>>;
    constexpr auto shift = 8 * sizeof(T) - 1;
    return bit_cast(v >> shift, as<l_t> {});
  }

  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>> is_ltz_(EVE_REQUIRES(avx512_),
                                              O          const &,
                                              wide<T, N> const &a) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using l_t        = logical<wide<T, N>>;
    constexpr auto c = categorize<wide<T, N>>();
     using enum fpclass_enum;
     constexpr auto f = neg | neginf;

    using s_t = typename l_t::storage_type;

    if constexpr( c == category::float64x8 ) return s_t {_mm512_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float64x4 ) return s_t {_mm256_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float64x2 ) return s_t {_mm_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float32x16) return s_t {_mm512_fpclass_ps_mask(a, f)};
    else if constexpr( c == category::float32x8 ) return s_t {_mm256_fpclass_ps_mask(a, f)};
    else if constexpr( c == category::float32x4 ) return s_t {_mm_fpclass_ps_mask(a, f)};
  }


// -----------------------------------------------------------------------------------------------
// masked  implementation
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto is_ltz_(EVE_REQUIRES(avx512_),
                               C const& cx,
                               O const& o,
                               wide<T, N> const& v) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::has_alternative || C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return is_ltz.behavior(cpu_{}, o, v, v);
    }
    else
    {
      auto           m = expand_mask(cx, as<wide<T, N>> {}).storage().value;
      using enum fpclass_enum;
      constexpr auto f = neg | neginf;

      if constexpr( c == category::float32x16 )     return mask16 {_mm512_mask_fpclass_ps_mask(m, v, f)};
      else if constexpr( c == category::float64x8 ) return mask8 {_mm512_mask_fpclass_pd_mask(m, v, f)};
      else if constexpr( c == category::float32x8 ) return mask8 {_mm256_mask_fpclass_ps_mask(m, v, f)};
      else if constexpr( c == category::float64x4 ) return mask8 {_mm256_mask_fpclass_pd_mask(m, v, f)};
      else if constexpr( c == category::float32x4 ) return mask8 {_mm_mask_fpclass_ps_mask(m, v, f)};
      else if constexpr( c == category::float64x2 ) return mask8 {_mm_mask_fpclass_pd_mask(m, v, f)};
    }
  }
}
