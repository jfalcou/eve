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

// Have to do the template, otherwise there is some PCH weirdness
template<typename U8x16, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
ppc_vec_perm(U8x16 x, U8x16 y, pattern_t<I...>)
{
  U8x16 table {I...};
  return vec_perm(x.storage(), y.storage(), table.storage());
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(vmx_), P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( auto r = shuffle_l3_and_0(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else
  {
    using u8x16 = wide<std::uint8_t, eve::fixed<16>>;
    auto bytes  = eve::bit_cast(x, eve::as<u8x16> {});

    constexpr auto no_we = idxm::replace_we(P::idxs, 0);

    if constexpr( P::has_zeroes )
    {
      constexpr auto expanded   = idxm::expand_group<P::g_size>(no_we);
      constexpr auto table_idxs = idxm::to_pattern<expanded>();

      return ppc_vec_perm(bytes, bytes, table_idxs);
    }
    else
    {
      constexpr auto no_na      = idxm::replace_na(no_we, N::value);
      constexpr auto expanded   = idxm::expand_group<P::g_size>(no_na);
      constexpr auto table_idxs = idxm::to_pattern<expanded>();

      return ppc_vec_perm(bytes, u8x16(0), table_idxs);
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_ppc_vec_sel(P, fixed<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( !idxm::is_blend(P::idxs, N::value / G) ) return no_matching_shuffle;
  else
  {
    eve::logical<wide<T, N>> m([](int i, int size) { return P::idxs[i / G] >= size / G; });
    return vec_sel(x.storage(), y.storage(), m.storage());
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(vmx_), P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l3_ppc_vec_sel(p, g, x, y); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle_t {};
}

}

//     return vec_perm(what.storage(), what.storage(), pattern.storage());
