//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/module/core/regular/broadcast.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
// Find the proper broadcast group shape. If none is found, returns {-1,-1}
template<std::size_t Cardinal, std::size_t Size>
constexpr inline auto
find_broadcast_group(std::array<std::ptrdiff_t, Size> const& pattern)
{
  struct bg
  {
    std::ptrdiff_t group = -1, index = -1;
  };

  for( std::ptrdiff_t g = Cardinal; g > 0; g /= 2 )
  {
    std::ptrdiff_t nb_idx = Cardinal / g;

    for( std::ptrdiff_t idx = 0; idx < nb_idx; idx++ )
    {
      // Compute what we expect
      std::array<std::ptrdiff_t, Size> expected;
      for( std::size_t i = 0; i < Size; ++i ) expected[i] = idx * g + (i % g);

      // Is it what we want ?
      if( pattern == expected ) return bg {g, idx};
    }
  }

  return bg {};
}

// Compute the expected broadcast group if any
template<std::ptrdiff_t Sz, std::ptrdiff_t... Is>
inline constexpr auto is_broadcast_group = []()
{
  constexpr std::array<std::ptrdiff_t, sizeof...(Is)> p      = {Is...};
  constexpr auto                                      result = detail::find_broadcast_group<Sz>(p);

  if constexpr( result.group != -1 )
    return std::optional {std::pair {lane<result.group>, index<result.index>}};
  else return std::optional<int> {};
}();

template<simd_value Wide, std::ptrdiff_t Group, std::ptrdiff_t Index, std::ptrdiff_t Size>
requires((Group > 0) && (Group <= std::min(cardinal_v<Wide>, Size)) && (Index >= 0)
         && (Index < cardinal_v<Wide> / Group)) EVE_FORCEINLINE
    auto broadcast_group_(EVE_SUPPORTS(cpu_),
                          Wide           w,
                          fixed<Group>   g,
                          index_t<Index> i,
                          fixed<Size>    sz)
{
  using that_t        = as_wide_t<Wide, fixed<Size>>;
  using v_t           = element_type_t<Wide>;
  constexpr auto card = cardinal_v<Wide>;

  if constexpr( is_bundle_v<typename Wide::abi_type> )
  {
    return Wide(kumi::map([=](auto m) { return broadcast_group(m, g, i, sz); }, w));
  }
  else
  {
    // If the output size is equal to the group size and the cardinal, we just return the input
    if constexpr( Size == Group && Size == card ) { return w; }
    // If the input wide is not aggregated and we don't bcast more than 64 bits
    else if constexpr( sizeof(v_t) * Group <= 8 )
    {
      using outer_type = detail::make_integer_t<sizeof(v_t) * Group>;
      using w_t        = as_wide_t<outer_type, fixed<card / Group>>;
      return bit_cast(broadcast(bit_cast(w, as<w_t>()), i, lane<Size / Group>), as<that_t>());
    }
    // If the output Greater than the Group size, we slice by half
    else if constexpr( Size > Group )
    {
      auto const r = broadcast_group(w, g, i, lane<Size / 2>);
      return eve::combine(r, r);
    }
    else
    {
      // If the beginning of the indexed group is beyond half the cardinal
      if constexpr( Index * Group >= card / 2 )
      {
        // We recompute the index and broadcast something from the upper slice of w
        return broadcast_group(w.slice(upper_), g, index<Index - card / (Group * 2)>, sz);
      }
      else
      {
        // Else we broadcast something from the lower slice of w
        return broadcast_group(w.slice(lower_), g, i, sz);
      }
    }
  }
}

template<simd_value Wide, std::ptrdiff_t Group, std::ptrdiff_t Index, std::ptrdiff_t Size>
requires((Group > 0) && (Group <= std::min(cardinal_v<Wide>, Size)) && (Index >= 0)
         && (Index < cardinal_v<Wide> / Group)) EVE_FORCEINLINE
    auto broadcast_group_(EVE_SUPPORTS(cpu_),
                          logical<Wide>  w,
                          fixed<Group>   g,
                          index_t<Index> i,
                          fixed<Size>    sz)
{
  using abi_t = typename logical<Wide>::abi_type;
  if constexpr( !abi_t::is_wide_logical )
  {
    // Reconstruct mask, swag then turn to mask again
    auto const m  = w.mask();
    auto const bg = broadcast_group(m, g, i, sz);
    return to_logical(bg);
  }
  else
  {
    // Use the common implementation
    return bit_cast(broadcast_group(w.mask(), g, i, sz), as(w));
  }
}

template<simd_value Wide, std::ptrdiff_t Group, std::ptrdiff_t Index>
requires((Group > 0) && (Group <= cardinal_v<Wide>)&&(Index >= 0)
         && (Index < cardinal_v<Wide> / Group)) EVE_FORCEINLINE
    auto broadcast_group_(EVE_SUPPORTS(cpu_), Wide w, fixed<Group> g, index_t<Index> i)
{
  return broadcast_group(w, g, i, cardinal_t<Wide> {});
}
}
