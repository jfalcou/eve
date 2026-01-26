//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/wide_forward.hpp>
#include <eve/concept/scalar.hpp>
#include <eve/arch/cardinals.hpp>
#include <eve/module/core/regular/bit_select.hpp>
#include <eve/detail/shuffle_v2/shuffle_v2_driver_fwd.hpp>

namespace eve::detail
{

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_neon_vtbl1(P, fixed<G>, wide<T, N> x)
{
  if constexpr( P::reg_size == 16 && current_api < asimd ) return no_matching_shuffle;
  else
  {
    using u8xN = wide<std::uint8_t, eve::fixed<N::value * sizeof(T)>>;
    auto bytes = eve::bit_cast(x, eve::as<u8xN> {});

    // Out of range idxs become 0
    constexpr auto no_we        = idxm::replace_we(P::idxs, na_);
    constexpr auto no_na        = idxm::replace_na(no_we, N::value);
    constexpr auto expanded     = idxm::expand_group<P::g_size>(no_na);
    auto           shuffle_mask = make_idx_mask<expanded>(as(bytes));

    if constexpr( P::reg_size == 8 ) return vtbl1_u8(bytes, shuffle_mask);
    else return vqtbl1q_u8(bytes, shuffle_mask);
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_neon_bit_select(P, fixed<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( !idxm::is_blend(P::idxs, N::value / G) ) return no_matching_shuffle_t {};
  else
  {
    eve::logical<wide<T, N>> m([](int i, int size) { return P::idxs[i / G] >= size / G; });
    return eve::bit_select(m, y, x);
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_neon_vtbl2(P, fixed<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( P::reg_size == 16 && current_api < asimd ) return no_matching_shuffle;
  else
  {
    using u8xN  = wide<std::uint8_t, eve::fixed<N::value * sizeof(T)>>;
    auto xbytes = eve::bit_cast(x, eve::as<u8xN> {});
    auto ybytes = eve::bit_cast(y, eve::as<u8xN> {});

    // Out of range idxs become 0
    constexpr auto no_we        = idxm::replace_we(P::idxs, na_);
    constexpr auto no_na        = idxm::replace_na(no_we, 2 * N::value);
    constexpr auto expanded     = idxm::expand_group<P::g_size>(no_na);
    auto           shuffle_mask = make_idx_mask<expanded>(as(xbytes));

    if constexpr( P::reg_size == 8 )
    {
      uint8x8x2_t xy = {{xbytes, ybytes}};
      return vtbl2_u8(xy, shuffle_mask);
    }
    else
    {
      uint8x16x2_t xy = {{xbytes, ybytes}};
      return vqtbl2q_u8(xy, shuffle_mask);
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(neon128_), P p, fixed<G> g, wide<T, N> x)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l3_and_0(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else if constexpr( auto r = shuffle_l3_slide_with_0(p, g, x); matched_shuffle<decltype(r)> )
    return r;
  else if constexpr( auto r = shuffle_l3_neon_vtbl1(p, g, x); matched_shuffle<decltype(r)> )
    return r;
  else return no_matching_shuffle_t {};
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(neon128_), P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l3_neon_bit_select(p, g, x, y); matched_shuffle<decltype(r)> )
    return r;
  else if constexpr( auto r = shuffle_l3_neon_vtbl2(p, g, x, y); matched_shuffle<decltype(r)> )
    return r;
  else return no_matching_shuffle_t {};
}

}
