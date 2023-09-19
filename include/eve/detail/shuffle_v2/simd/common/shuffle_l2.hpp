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

// TODO: this probably should not be here
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
up_element_size(wide<T, N> x)
{
  using T1 = detail::make_integer_t<sizeof(T) * 2, unsigned>;
  using N1 = eve::fixed<N::value / 2>;
  return eve::bit_cast(x, eve::as<wide<T1, N1>> {});
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t To>
EVE_FORCEINLINE auto
up_element_size_to(wide<T, N> x, eve::fixed<To>) {
  if constexpr (sizeof(T) == To) return x;
  else return up_element_size_to(up_element_size(x), eve::lane<To>);
}

struct
{
  template<std::ptrdiff_t S> EVE_FORCEINLINE auto operator()(auto x, eve::index_t<S>) const
  {
    if constexpr( S < 0 ) return x >> -S;
    else return x << S;
  }
} inline constexpr default_shift_by_const;

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_element_bit_shift(P, fixed<G>, wide<T, N> x, auto shift_by_const)
{  if constexpr( P::g_size * P::most_repeated.size() > 8 ) return no_matching_shuffle;
  else
  {
    // sizeof(T) < 8 because otherwise that's identity
    // G == 1, because otherwise it'd be simplified
    static_assert(sizeof(T) < 8 && G == 1, "verifying assumptions");

    if constexpr( constexpr auto slide = idxm::is_slide_left(P::most_repeated) )
    {
      return shift_by_const(up_element_size(x), eve::index<-(int)(8 * sizeof(T))>);
    }
    else if constexpr( constexpr auto slide = idxm::is_slide_right(P::most_repeated) )
    {
      return shift_by_const(up_element_size(x), eve::index<sizeof(T) * 8>);
    }
    else return no_matching_shuffle;
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_element_bit_shift(P p, fixed<G> g, wide<T, N> x)
{
  return shuffle_l2_element_bit_shift(p, g, x, default_shift_by_const);
}

}
