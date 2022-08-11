//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorized.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/detail/basic_shuffle.hpp>
#include <eve/module/core/regular/bit_width.hpp>
#include <eve/pattern.hpp>

#include <bit>

namespace eve::detail
{
//==============================================================================================
// Classify a pattern as a swag
template<std::ptrdiff_t... I>
inline constexpr auto is_swag = []()
{
  // List all possible swags for a current size
  constexpr auto sz = sizeof...(I);
  constexpr auto x  = []<std::size_t... N>(std::index_sequence<N...>)
  {
    return kumi::make_tuple(swap_adjacent_groups_pattern<sz / (1 << (N + 1)), sz>...);
  }
  (std::make_index_sequence<std::bit_width(sz) - 1> {});

  // Find the fitting one
  constexpr auto idx = detail::find_index(pattern<I...>, x);
  return fixed<sz / (1 << (idx + 1))> {};
}();

template<simd_value Wide, std::ptrdiff_t G>
EVE_FORCEINLINE auto
swap_adjacent_groups_(EVE_SUPPORTS(cpu_), Wide v, fixed<G>) noexcept requires(G <= Wide::size())
{
  if constexpr( G == Wide::size() ) { return v; }
  else if constexpr( has_aggregated_abi_v<Wide> )
  {
    if constexpr( G == Wide::size() / 2 )
    {
      auto [l, h] = v.slice();
      return Wide {h, l};
    }
    else
    {
      auto [l, h] = v.slice();
      return Wide {swap_adjacent_groups(l, fixed<G> {}), swap_adjacent_groups(h, fixed<G> {})};
    }
  }
  else if constexpr( is_bundle_v<typename Wide::abi_type> )
  {
    return Wide(
        kumi::map([&]<typename T>(T m) { return swap_adjacent_groups(m, fixed<G> {}); }, v));
  }
  else
  {
    // In this case, we don't have anything special to do so we just shuffle
    return basic_shuffle(v, swap_adjacent_groups_pattern<G, Wide::size()>);
  }
}

template<simd_value Wide, std::ptrdiff_t G>
EVE_FORCEINLINE auto
swap_adjacent_groups_(EVE_SUPPORTS(cpu_), logical<Wide> v, fixed<G> f) noexcept
    requires(G <= Wide::size())
{
  if constexpr( logical_value<Wide> && Wide::abi_type::is_wide_logical )
  {
    return bit_cast(swap_adjacent_groups(v.mask(), f), as(v));
  }
  else
  {
    // Reconstruct mask, swag then turn to mask again
    auto const m  = v.mask();
    auto const bg = swap_adjacent_groups(m, f);
    return to_logical(bg);
  }
}
}
