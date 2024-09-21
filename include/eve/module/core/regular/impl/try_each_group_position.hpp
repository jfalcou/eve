//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/rotate.hpp>

namespace eve::detail
{

template<simd_value T, std::ptrdiff_t G>
EVE_FORCEINLINE auto
try_each_group_position_aggregation(T x, eve::fixed<G> g) noexcept
{
  auto [l, h] = x.slice();
  auto l_pos  = try_each_group_position(l, g);
  auto h_pos  = try_each_group_position(h, g);
  auto lh     = kumi::map([](auto vx, auto vy) { return T{vx, vy}; }, l_pos, h_pos);
  auto hl     = kumi::map([](auto vx, auto vy) { return T{vy, vx}; }, l_pos, h_pos);
  return kumi::cat(lh, hl);
}

template<simd_value T, std::ptrdiff_t G>
EVE_FORCEINLINE auto
try_each_group_position_(EVE_SUPPORTS(cpu_), T x, eve::fixed<G> g) noexcept
{
       if constexpr( T::size() == G ) { return kumi::tuple<T> {x}; }
  else if constexpr( logical_value<T> && T::abi_type::is_wide_logical )
  {
    auto bits = try_each_group_position(x.bits(), g);
    return kumi::map([](auto y) { return bit_cast(y, as<T> {}); }, bits);
  }
  else if constexpr( has_aggregated_abi_v<T> ) return try_each_group_position_aggregation(x, g);
  else
  {
    // Doubling the group size is likely to yield better shuffles
    // over rotating many times by one.
    return kumi::cat(
      try_each_group_position(x,                        eve::lane<G * 2>),
      try_each_group_position(rotate(x, eve::index<G>), eve::lane<G * 2>)
    );
  }
}

}
