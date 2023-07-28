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

template<typename T, typename N, std::ptrdiff_t S>
EVE_FORCEINLINE auto
vshl_n(eve::wide<T, N> x, eve::index_t<S>)
{
  if constexpr( sizeof(T) == 8 && N() == 1 ) return vshl_n_u64(x, S);
  else if constexpr( sizeof(T) == 4 && N() == 2 ) return vshl_n_u32(x, S);
  else if constexpr( sizeof(T) == 2 && N() == 4 ) return vshl_n_u16(x, S);
  else if constexpr( sizeof(T) == 1 && N() == 8 ) return vshl_n_u8(x, S);
}

template<typename T, typename N, std::ptrdiff_t S>
EVE_FORCEINLINE auto
vshr_n(eve::wide<T, N> x, eve::index_t<S>)
{
  if constexpr( sizeof(T) == 8 && N() == 1 ) return vshr_n_u64(x, S);
  else if constexpr( sizeof(T) == 4 && N() == 2 ) return vshr_n_u32(x, S);
  else if constexpr( sizeof(T) == 2 && N() == 4 ) return vshr_n_u16(x, S);
  else if constexpr( sizeof(T) == 1 && N() == 8 ) return vshr_n_u8(x, S);
}

template<typename T, typename N, std::ptrdiff_t S>
EVE_FORCEINLINE auto
vext(eve::wide<T, N> x, eve::wide<T, N> y, eve::index_t<S>)
{
  if constexpr( sizeof(T) * N() == 8 )
  {
    if constexpr( sizeof(T) == 8 ) return vext_u64(x, y, S);
    else if constexpr( sizeof(T) == 4 ) return vext_u32(x, y, S);
    else if constexpr( sizeof(T) == 2 ) return vext_u16(x, y, S);
    else return vext_u8(x, y, S);
  }
  else
  {
    if constexpr( sizeof(T) == 8 ) return vextq_u64(x, y, S);
    else if constexpr( sizeof(T) == 4 ) return vextq_u32(x, y, S);
    else if constexpr( sizeof(T) == 2 ) return vextq_u16(x, y, S);
    else return vextq_u8(x, y, S);
  }
}

template<typename T, typename N, std::ptrdiff_t To, std::ptrdiff_t From>
EVE_FORCEINLINE auto
vcopy_lane(eve::wide<T, N> x, eve::index_t<To>, eve::wide<T, N> y, eve::index_t<From>)
{
  if constexpr( sizeof(T) * N() == 8 )
  {
    if constexpr( sizeof(T) == 8 ) return vcopy_lane_u64(x, To, y, From);
    else if constexpr( sizeof(T) == 4 ) return vcopy_lane_u32(x, To, y, From);
    else if constexpr( sizeof(T) == 2 ) return vcopy_lane_u16(x, To, y, From);
    else return vcopy_lane_u8(x, To, y, From);
  }
  else
  {
    if constexpr( sizeof(T) == 8 ) return vcopy_laneq_u64(x, To, y, From);
    else if constexpr( sizeof(T) == 4 ) return vcopy_laneq_u32(x, To, y, From);
    else if constexpr( sizeof(T) == 2 ) return vcopy_laneq_u16(x, To, y, From);
    else return vcopy_laneq_u8(x, To, y, From);
  }
}

struct
{
  template<std::ptrdiff_t S> EVE_FORCEINLINE auto operator()(auto x, eve::index_t<S>) const
  {
    if constexpr( S < 0 ) return vshr_n(x, eve::index<-S>);
    else return vshl_n(x, eve::index<S>);
  }
} inline constexpr neon_shift_by_const;

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_neon_set_one_zero(pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr std::array idxs {I...};

  constexpr auto pos = eve::detail::idxm::is_just_setting_one_zero(idxs);

  if constexpr( !pos ) return no_matching_shuffle_t {};
  else if constexpr( sizeof(T) * N() == 8 )
  {
    constexpr auto m = *pos;

    if constexpr( sizeof(T) == 4 ) return vset_lane_u32(0, x, m);
    else if constexpr( sizeof(T) == 2 ) return vset_lane_u16(0, x, m);
    else return vset_lane_u8(0, x, m);
  }
  else
  {
    constexpr auto m = *pos;

    if constexpr( sizeof(T) == 8 ) return vsetq_lane_u64(0, x, m);
    else if constexpr( sizeof(T) == 4 ) return vsetq_lane_u32(0, x, m);
    else if constexpr( sizeof(T) == 2 ) return vsetq_lane_u16(0, x, m);
    else return vsetq_lane_u8(0, x, m);
  }
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_neon_rev(pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr std::array idxs = idxm::most_repeated_pattern<I...>;

  if constexpr( G * sizeof(T) * idxs.size() > 8 ) return no_matching_shuffle_t {};
  else if constexpr( !idxm::is_reverse(idxs) ) return no_matching_shuffle_t {};
  else if constexpr( sizeof(T) * N::value == 8 )
  {
    if constexpr( sizeof(T) == 4 && idxs.size() == 2 ) return vrev64_u32(x);
    else if constexpr( sizeof(T) == 2 && idxs.size() == 2 ) return vrev32_u16(x);
    else if constexpr( sizeof(T) == 1 && idxs.size() == 2 ) return vrev16_u8(x);
    else if constexpr( sizeof(T) == 2 && idxs.size() == 4 ) return vrev64_u16(x);
    else if constexpr( idxs.size() == 4 ) return vrev32_u8(x);
    else return vrev64_u8(x);
  }
  else
  {
    if constexpr( sizeof(T) == 4 && idxs.size() == 2 ) return vrevq64_u32(x);
    else if constexpr( sizeof(T) == 2 && idxs.size() == 2 ) return vrevq32_u16(x);
    else if constexpr( sizeof(T) == 1 && idxs.size() == 2 ) return vrevq16_u8(x);
    else if constexpr( sizeof(T) == 2 && idxs.size() == 4 ) return vrevq64_u16(x);
    else if constexpr( idxs.size() == 4 ) return vrevq32_u8(x);
    else return vrevq64_u8(x);
  }
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_neon_dup_lane(pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr std::array idxs {I...};
  constexpr auto       lane       = idxm::is_lane_broadcast(idxs);
  constexpr bool       is_8_bytes = sizeof(T) * N::value == 8;

  if constexpr( !lane ) return no_matching_shuffle_t {};
  else
  {
    constexpr int m = *lane;

    if constexpr( sizeof(T) * N::value == 8 )
    {
      if constexpr( sizeof(T) == 4 ) return vdup_lane_u32(x, m);
      else if constexpr( sizeof(T) == 2 ) return vdup_lane_u16(x, m);
      else return vdup_lane_u8(x, m);
    }
    else
    {
      if constexpr( sizeof(T) == 8 ) return vdup_laneq_u64(x, m);
      else if constexpr( sizeof(T) == 4 ) return vdup_laneq_u32(x, m);
      else if constexpr( sizeof(T) == 2 ) return vdup_laneq_u16(x, m);
      else return vdup_laneq_u8(x, m);
    }
  }
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_neon_ext_self(pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr auto idxs  = std::array {I...};
  constexpr auto point = idxm::is_rotate(idxs);
  if constexpr( !point ) return no_matching_shuffle_t {};
  else return vext(x, x, eve::index<idxs.size() - *point>);
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_neon_copy_lane_self(pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr auto idxs    = std::array {I...};
  constexpr auto to_from = idxm::is_just_setting_one_lane(idxs);
  if constexpr( current_api < asimd || !to_from ) return no_matching_shuffle_t {};
  else return vcopy_lane(x, eve::index<(*to_from)[0]>, x, eve::index<(*to_from)[1]>);
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(neon128_), pattern_t<I...> p, fixed<G> g, wide<T, N> x)
requires (pattern_t<I...>::size() * G == N::value)
{
  constexpr std::array idxs {I...};
  if constexpr( idxs.size() * G != N::value ) return no_matching_shuffle_t {};
  else if constexpr( auto r = shuffle_l2_element_bit_shift(p, g, x, neon_shift_by_const);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_neon_set_one_zero(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_neon_rev(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_neon_dup_lane(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_neon_ext_self(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_neon_copy_lane_self(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle_t {};
}

}
