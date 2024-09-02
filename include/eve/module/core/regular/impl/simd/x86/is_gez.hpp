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
  template<integral_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE constexpr auto
  is_gez_(EVE_REQUIRES(sse2_), O const &, wide<T, N> const& v) noexcept
  requires(sizeof(T) < 8 && x86_abi<abi_t<T, N>> && abi_t<T, N>::is_wide_logical)
  {
    using l_t            = as_logical_t<wide<T, N>>;
    constexpr auto shift = 8 * sizeof(T) - 1;
    return bit_cast(v >> shift, as<l_t> {});
  }

  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>> is_gez_(EVE_REQUIRES(avx512_),
                                              O          const &,
                                              wide<T, N> const &a) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using l_t        = logical<wide<T, N>>;
    constexpr auto c = categorize<wide<T, N>>();
    constexpr auto f = fpclass::neg | fpclass::qnan | fpclass::snan;

    using s_t = typename l_t::storage_type;

    if constexpr( c == category::float64x8 ) return ~s_t {_mm512_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float64x4 ) return ~s_t {_mm256_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float64x2 ) return ~s_t {_mm_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float32x16) return ~s_t {_mm512_fpclass_ps_mask(a, f)};
    else if constexpr( c == category::float32x8 ) return ~s_t {_mm256_fpclass_ps_mask(a, f)};
    else if constexpr( c == category::float32x4 ) return ~s_t {_mm_fpclass_ps_mask(a, f)};
  }
}
