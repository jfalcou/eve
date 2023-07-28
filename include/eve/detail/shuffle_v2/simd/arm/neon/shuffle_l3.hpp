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

template<typename N, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
neon_vtbl(wide<std::uint8_t, N> x, pattern_t<I...> p)
{
  if constexpr( N::value == 8 ) return vtbl1_u8(x, wide<std::uint8_t, N> {I...});
  else return vqtbl1q_u8(x, wide<std::uint8_t, N> {I...});
}

template<typename N, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
neon_vtbl(wide<std::uint8_t, N> x, wide<std::uint8_t, N> y, pattern_t<I...> p)
{
  if constexpr( N::value == 8 ) return vtbx1_u8(x, wide<std::uint8_t, N> {I...});
  else return vqtbx1_u8(x, wide<std::uint8_t, N> {I...});
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_neon_tbl(pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr std::array idxs {I...};

  if constexpr( sizeof(T) * N::value == 16 && current_api < asimd ) return no_matching_shuffle;
  else
  {
    using u8xN = wide<std::uint8_t, eve::fixed<N::value * sizeof(T)>>;
    auto bytes = eve::bit_cast(x, eve::as<u8xN> {});

    constexpr auto no_we = idxm::replace_we(idxs, 0);

    if constexpr( !idxm::has_zeroes(idxs) )
    {
      constexpr auto expanded   = idxm::expand_group<G * sizeof(T)>(no_we);
      constexpr auto table_idxs = idxm::to_pattern<expanded>();

      return neon_vtbl(bytes, table_idxs);
    }
    else
    {
      constexpr auto no_na      = idxm::replace_na(no_we, N::value);
      constexpr auto expanded   = idxm::expand_group<G * sizeof(T)>(no_na);
      constexpr auto table_idxs = idxm::to_pattern<expanded>();

      return neon_vtbl(bytes, u8xN{0}, table_idxs);
    }
  }
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(neon128_), pattern_t<I...> p, fixed<G> g, wide<T, N> x)
  requires (pattern_t<I...>::size() * G == N::value)
{
  constexpr std::array idxs {I...};

  if constexpr( auto r = shuffle_l3_and_0(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else if constexpr( auto r = shuffle_l2_neon_tbl(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else return no_matching_shuffle_t {};
}

}
