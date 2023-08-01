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
shuffle_l3_(EVE_SUPPORTS(vmx_), pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr std::array idxs {I...};
  if constexpr( idxm::has_zeroes(idxs) ) return no_matching_shuffle;
  else
  {
    constexpr auto table_idxs =
        idxm::to_pattern<idxm::expand_group<G * sizeof(T)>(idxm::replace_we(idxs, 0))>();
    using u8x16 = wide<std::uint8_t, eve::fixed<16>>;
    auto bytes  = eve::bit_cast(x, eve::as<u8x16> {});

    return ppc_vec_perm(bytes, bytes, table_idxs);
  }
}

}

//     return vec_perm(what.storage(), what.storage(), pattern.storage());
