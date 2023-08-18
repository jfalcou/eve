//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/bit_select.hpp>

namespace eve::detail
{

template<typename N, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
neon_vtbl(wide<std::uint8_t, N> x, pattern_t<I...>)
{
  if constexpr( N::value == 8 ) return vtbl1_u8(x, wide<std::uint8_t, N> {I...});
  else return vqtbl1q_u8(x, wide<std::uint8_t, N> {I...});
}

template<typename N, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
neon_vtbl(wide<std::uint8_t, N> x, wide<std::uint8_t, N> y, pattern_t<I...>)
{
  if constexpr( N::value == 8 ) return vtbx1_u8(x, y, wide<std::uint8_t, N> {I...});
  else return vqtbx1_u8(x, y, wide<std::uint8_t, N> {I...});
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_neon_tbl(P, fixed<G>, wide<T, N> x)
{
  if constexpr( P::reg_size == 16 && current_api < asimd ) return no_matching_shuffle;
  else
  {
    using u8xN = wide<std::uint8_t, eve::fixed<N::value * sizeof(T)>>;
    auto bytes = eve::bit_cast(x, eve::as<u8xN> {});

    constexpr auto no_we = idxm::replace_we(P::idxs, 0);

    if constexpr( !P::has_zeroes )
    {
      constexpr auto expanded   = idxm::expand_group<P::g_size>(no_we);
      constexpr auto table_idxs = idxm::to_pattern<expanded>();

      return neon_vtbl(bytes, table_idxs);
    }
    else
    {
      constexpr auto no_na      = idxm::replace_na(no_we, N::value);
      constexpr auto expanded   = idxm::expand_group<P::g_size>(no_na);
      constexpr auto table_idxs = idxm::to_pattern<expanded>();

      return neon_vtbl(u8xN{0}, bytes, table_idxs);
    }
  }
}


template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_neon_bit_select(P, fixed<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr ( !idxm::is_blend(P::idxs, N::value / G) ) return no_matching_shuffle_t{};
  else
  {
    eve::logical<wide<T, N>> m([](int i, int size) { return P::idxs[i / G] >= size / G; });
    return eve::bit_select(m, y, x);
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(neon128_), P p, fixed<G> g, wide<T, N> x)
  requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l3_and_0(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else if constexpr( auto r = shuffle_l3_neon_tbl(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else return no_matching_shuffle_t {};
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(neon128_), P p, fixed<G> g, wide<T, N> x,  wide<T, N> y)
  requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l3_neon_bit_select(p, g, x, y); matched_shuffle<decltype(r)> ) return r;
  else return no_matching_shuffle_t {};
}

}
