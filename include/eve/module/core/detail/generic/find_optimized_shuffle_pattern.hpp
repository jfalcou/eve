//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/detail/basic_shuffle.hpp>
#include <eve/module/core/regular/broadcast_group.hpp>
#include <eve/module/core/regular/broadcast.hpp>
#include <eve/module/core/regular/deinterleave_groups_shuffle.hpp>
#include <eve/module/core/regular/rotate.hpp>
#include <eve/module/core/regular/slide_left.hpp>
#include <eve/module/core/regular/slide_right.hpp>
#include <eve/module/core/named_shuffles/core.hpp>
#include <eve/pattern.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>

#include <ostream>

namespace eve::detail
{
//================================================================================================
// Detects <-1,...,-1> as zeroing
template<int... I> inline constexpr bool is_zero = ((I == na_) && ...);

//================================================================================================
// Detects <0,1,...,N-1> as identity
template<int... I>
inline constexpr bool is_identity = []()
{
  int  idx[] = {I...};
  int  c     = sizeof...(I);
  bool ok    = true;

  for( int i = 0; i < c; ++i ) ok = ok && (idx[i] == i);

  return ok;
}();

//================================================================================================
// Local silly helper that doesn't warrant an actual functor
//================================================================================================
struct identity_swizzle
{
  friend std::ostream& operator<<(std::ostream& os, identity_swizzle)
  {
    return os << "identity_swizzle";
  }

  template<typename Wide, typename Pattern> EVE_FORCEINLINE auto operator()(Wide v, Pattern p) const
  {
    constexpr auto cd = cardinal_v<Wide>;
    constexpr auto sz = Pattern::size();
    using that_t      = as_wide_t<Wide, fixed<sz>>;

    if constexpr( sz >= cd ) return that_t(v.storage());
    else if constexpr( cd / sz == 2 ) return that_t(v.slice(lower_).storage());
    else return shuffle(v.slice(lower_), p);
  }
};

struct zero_swizzle
{
  friend std::ostream& operator<<(std::ostream& os, zero_swizzle) { return os << "zero_swizzle"; }

  template<typename Wide, typename Cardinal>
  EVE_FORCEINLINE auto operator()([[maybe_unused]] Wide w, Cardinal) const
  {
    using w_t = as_wide_t<Wide, Cardinal>;
    if constexpr( is_bundle_v<typename Wide::abi_type> )
    {
      return w_t(kumi::map([]<typename T>(T) { return as_wide_t<T, Cardinal> {0}; }, w));
    }
    else { return w_t {0}; }
  }
};

//================================================================================================
// Wrap a callable with its additional constexpr info
//================================================================================================
template<typename Callable, typename... Args> struct bound
{
  constexpr bound(Callable, Args...) {}

  template<typename W> EVE_FORCEINLINE auto operator()(W w) const noexcept
  {
    return Callable {}(w, Args {}...);
  }

  friend std::ostream& operator<<(std::ostream& os, bound)
  {
    os << Callable {} << "(";
    ((os << " " << Args {}), ...);
    return os << " )";
  }
};

// Part time migration to shuffle_v2

template<std::ptrdiff_t G, std::ptrdiff_t N>
inline constexpr auto swap_adjacent_groups_pattern = fix_pattern<N>(
    [](auto i, auto)
    {
      if constexpr( G != N && G != 0 ) return (i + G) % (G * 2) + (G * 2) * (i / (G * 2));
      else return i;
    });

template<std::ptrdiff_t... I>
inline constexpr auto is_swag = []()
{
  // List all possible swags for a current size
  constexpr auto sz = sizeof...(I);
  constexpr auto x  = []<std::size_t... N>(std::index_sequence<N...>)
  {
    return kumi::make_tuple(swap_adjacent_groups_pattern<sz / (1 << (N + 1)), sz>...);
  }
  (std::make_index_sequence<std::bit_width(sz) - 1> {});

  // Find the fitting one
  constexpr auto idx = detail::find_index(pattern<I...>, x);
  return fixed<sz / (1 << (idx + 1))> {};
}();

template<int N, int... I>
inline constexpr bool is_reverse = []
{
  std::array idxs {I...};
  for( int i = 0; i != static_cast<int>(idxs.size()); ++i )
  {
    if( idxs[i] != (static_cast<int>(idxs.size()) - i - 1) ) return false;
  }
  return static_cast<int>(idxs.size()) == N;
}();

// ---------------------------------

//================================================================================================
// Look to see if a given pattern is optimizable and returns the optimized function object
//================================================================================================
template<std::ptrdiff_t InCardinal, std::ptrdiff_t I0, std::ptrdiff_t... I>
consteval auto
find_optimized_shuffle_pattern()
{
  [[maybe_unused]] constexpr auto sz = fixed<1 + sizeof...(I)> {};
  [[maybe_unused]] constexpr auto p  = pattern_t<I0, I...> {};

  if constexpr( is_zero<I0, I...> ) return bound {zero_swizzle {}, sz};
  else if constexpr( is_broadcast<I0, I...> ) return bound {broadcast, index<I0>, sz};
  else if constexpr( is_identity<I0, I...> ) return bound {identity_swizzle {}, p};
  else if constexpr( is_swag<I0, I...> != sz )
  {
    return bound {swap_adjacent, is_swag<I0, I...>};
  }
  else if constexpr( constexpr auto st = is_broadcast_group<InCardinal, I0, I...> )
  {
    return bound {broadcast_group, st->first, st->second, sz};
  }
  else if constexpr(is_slide_left<I0, I...> != 0 )
  {
    return bound {slide_left, index<is_slide_left<I0, I...>>};
  }
  else if constexpr(is_slide_right<I0, I...> != 0 )
  {
    return bound {slide_right, index<is_slide_right<I0, I...>>};
  }
  else if constexpr( is_reverse<InCardinal, I0, I...> ) return bound {reverse};
  else if constexpr( is_rotate<InCardinal, I0, I...> != 0 )
  {
    return bound {rotate, index<is_rotate<InCardinal, I0, I...>>};
  }
  else if constexpr( is_deinterleave_groups_shuffle<I0, I...> != sz )
  {
    return bound {deinterleave_groups_shuffle, is_deinterleave_groups_shuffle<I0, I...>};
  }
  else return bound {basic_shuffle, p};
}
}
