//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/detail/flags.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>> is_nez_(EVE_REQUIRES(avx512_),
                                              O          const &opts,
                                              wide<T, N> const &a) noexcept
  requires (x86_abi<abi_t<T, N>> && (sizeof(T) >= 4))
  {
    using l_t        = logical<wide<T, N>>;
    constexpr auto c = categorize<wide<T, N>>();
    constexpr auto f = (eve::poszero | eve::negzero).value;

    using s_t = typename l_t::storage_type;

    if constexpr( c == category::float64x8 ) return ~s_t {_mm512_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float64x4 ) return ~s_t {_mm256_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float64x2 ) return ~s_t {_mm_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float32x16) return ~s_t {_mm512_fpclass_ps_mask(a, f)};
    else if constexpr( c == category::float32x8 ) return ~s_t {_mm256_fpclass_ps_mask(a, f)};
    else if constexpr( c == category::float32x4 ) return ~s_t {_mm_fpclass_ps_mask(a, f)};
    else if constexpr (match(c, category::float16))
    {
      if      constexpr(!detail::supports_fp16_vector_ops) return is_nez.behavior(cpu_{}, opts, a);
      else if constexpr( c == category::float16x32 )       return ~s_t {_mm512_fpclass_ph_mask(a, f)};
      else if constexpr( c == category::float16x16 )       return ~s_t {_mm256_fpclass_ph_mask(a, f)};
      else if constexpr( c == category::float16x8  )       return ~s_t {_mm_fpclass_ph_mask(a, f)};
    }
  }
}
