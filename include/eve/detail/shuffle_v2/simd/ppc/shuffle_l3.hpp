//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{

template<std::ptrdiff_t... I>
EVE_FORCEINLINE auto
ppc_vec_perm(wide<std::uint8_t, eve::fixed<16>> x,
             wide<std::uint8_t, eve::fixed<16>> y,
             pattern_t<I...>)
{
  wide<std::uint8_t, eve::fixed<16>> table {I...};
  return vec_perm(x.storage(), y.storage(), table.storage());
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(vmx_), pattern_t<I...> p, fixed<G> g, wide<T, N> x)
{
  constexpr std::array idxs {I...};

  if constexpr( auto r = shuffle_l3_and_0(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else
  {
    using u8x16 = wide<std::uint8_t, eve::fixed<16>>;
    auto bytes  = eve::bit_cast(x, eve::as<u8x16> {});

    constexpr auto no_we = idxm::replace_we(idxs, 0);

    if constexpr( !idxm::has_zeroes(idxs) )
    {
      constexpr auto expanded   = idxm::expand_group<G * sizeof(T)>(no_we);
      constexpr auto table_idxs = idxm::to_pattern<expanded>();

      return ppc_vec_perm(bytes, bytes, table_idxs);
    }
    else
    {
      constexpr auto no_na      = idxm::replace_na(no_we, N::value);
      constexpr auto expanded   = idxm::expand_group<G * sizeof(T)>(no_na);
      constexpr auto table_idxs = idxm::to_pattern<expanded>();

      return ppc_vec_perm(bytes, u8x16(0), table_idxs);
    }
  }
}

}

//     return vec_perm(what.storage(), what.storage(), pattern.storage());
