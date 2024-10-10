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

namespace eve::detail
{
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> popcount_(EVE_REQUIRES(neon128_),
                                       O const& o,
                                       wide<T, N> v) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();

    auto split_it = []<typename U > (U v){
      using d_t = downgrade_t<U>;
      using t_t = wide<d_t, eve::fixed<N::value*2>>;
      auto z =  bit_cast(v, as<t_t>());
      return  popcount(z);
    };

    if      constexpr( cat == category::uint8x8 ) return vcnt_u8(v);
    else if constexpr( cat == category::uint8x16) return vcntq_u8(v);
    else if constexpr( cat == category::uint16x4) return vpaddl_u8(split_it(v));
    else if constexpr( cat == category::uint16x8) return vpaddlq_u8(split_it(v));
    else if constexpr( cat == category::uint32x2) return vpaddl_u16(split_it(v));
    else if constexpr( cat == category::uint32x4) return vpaddlq_u16(split_it(v));
    else if constexpr( cat == category::uint64x2) return vpaddl_u32(split_it(v));
    else                                          return popcount.behavior(cpu_{}, o, v);

  }
}
