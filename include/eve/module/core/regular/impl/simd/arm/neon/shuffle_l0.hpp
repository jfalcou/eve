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

// NOTE: using no_matching_shuffle_t {} because otherwise apple clang crashes.

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l0_impl_(EVE_SUPPORTS(neon128_), wide<T, N> x, fixed<G>, pattern_t<I...>)
requires std::same_as<abi_t<T, N>, arm_64_>
{
  constexpr std::array idxs {I...};
  constexpr bool       is_float = std::same_as<T, float>;

  if constexpr( idx::is_identity(idxs) ) return x;
  else if constexpr( idx::is_zero(idxs) ) return wide<T, N> {0};
  else if constexpr( sizeof(T) == 4 )
  {
    if constexpr( idx::has_zeroes(idxs) )
    {
      if constexpr( idx::matches(idxs, {0, na_}, {na_, 1}) )
      {
        constexpr int m = idxs[0] == na_ ? 0 : 1;
        if constexpr( is_float ) return vset_lane_f32(0, x, m);
        else return vset_lane_u32(0, x, m);
      }
      else
      {
        auto u64 = eve::bit_cast(x, eve::as<uint64x1_t> {});
        if constexpr( idx::matches(idxs, {na_, 0}) ) return vshl_n_u64(u64, 32);
        else return vshr_n_u64(u64, 32);
      }
    }
    else if constexpr( idx::matches(idxs, {1, 0}) )
    {
      if constexpr( is_float ) return vrev64_f32(x);
      else return vrev64_u32(x);
    }
    else // 0, 0 or 1, 1
    {
      constexpr int m = idxs[0] == we_ ? 1 : idxs[0];
      if constexpr( std::same_as<T, float> ) return vdup_lane_f32(x, m);
      else return vdup_lane_u32(x, m);
    }
  }
  else return no_matching_shuffle_t {};
}

}
