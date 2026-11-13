//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/shuffle_v2/native_shuffle_helpers.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

#include <cstdint>

namespace eve::_
{
  // Any one-register permutation, as a vrgather on the lanes reinterpreted as unsigned integers.
  template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
  auto shuffle_l3_rvv_gather(P, lanes_t<G>, wide<T, N> x)
  {
    constexpr auto idxs = idxm::expand_group<G>(idxm::replace_we(P::idxs, 0));

    // The driver masks the na_ lanes of a one-register shuffle before it reaches this level.
    if constexpr( idxm::has_zeroes(idxs) || idxs.size() != N ) return no_matching_shuffle;
    // Do not gather more than 256 8-bit lanes with 8-bit indices, which cannot address them.
    else if constexpr( sizeof(T) == 1 && N > 256 )
    {
      if constexpr( !rvv_abi<abi_t<std::uint16_t, N>> ) return no_matching_shuffle;
      else
      {
        using u_t = wide<std::uint8_t, N>;
        auto table = [&]<std::size_t... i>(std::index_sequence<i...>)
        { return wide<std::uint16_t, N> {static_cast<std::uint16_t>(idxs[i])...}; }(std::make_index_sequence<N> {});
        return bit_cast(u_t(__riscv_vrgatherei16(bit_cast(x, as<u_t> {}), table, N)), as(x));
      }
    }
    else
    {
      using e_t  = as_integer_t<T, unsigned>;
      using u_t  = wide<e_t, N>;
      auto table = [&]<std::size_t... i>(std::index_sequence<i...>)
      { return u_t {static_cast<e_t>(idxs[i])...}; }(std::make_index_sequence<N> {});
      return bit_cast(u_t(__riscv_vrgather(bit_cast(x, as<u_t> {}), table, N)), as(x));
    }
  }

  template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
  auto shuffle_l3_(EVE_SUPPORTS(rvv_), P p, lanes_t<G> g, wide<T, N> x)
  requires rvv_abi<abi_t<T, N>>
  {
    return shuffle_l3_rvv_gather(p, g, x);
  }
}
