//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_SKELETON_HPP_INCLUDED
#define EVE_DETAIL_SKELETON_HPP_INCLUDED

#include <eve/detail/is_range.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/ext/has_abi.hpp>
#include <eve/ext/as_wide.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/cardinal.hpp>
#include <algorithm>
#include <utility>
#include <iostream>

namespace eve::detail
{
  // Value extraction from RandomAccessRange
  template<typename T>
  EVE_FORCEINLINE constexpr decltype(auto) at(T &&t, std::size_t i) noexcept
  {
    if constexpr(is_random_access_range_v<T>)
      return std::forward<T>(t)[ i ];
    else
      return std::forward<T>(t);
  }

  // Upper values extraction
  template<typename T>
  EVE_FORCEINLINE constexpr auto upper(T &&t) noexcept
  {
    if constexpr(is_vectorized_v<T>)
      return eve::detail::slice(std::forward<T>(t), upper_);
    else
      return std::forward<T>(t);
  }

  // Lower values extraction
  template<typename T>
  EVE_FORCEINLINE constexpr auto lower(T &&t) noexcept
  {
    if constexpr(is_vectorized_v<T>)
      return eve::detail::slice(std::forward<T>(t), lower_);
    else
      return std::forward<T>(t);
  }

  // Compute a transformed wide type
  template<typename F, typename... Ts>
  struct wide_result
  {
    template<typename T>
    using card_t                        = eve::cardinal<std::decay_t<T>>;
    static constexpr std::size_t card_v = std::max({card_t<Ts>::value...});
    using value_t                       = decltype(std::declval<F>()(at(std::declval<Ts>(), 0)...));
    using fixed_t                       = fixed<card_v>;
    using type                          = as_wide_t<value_t, fixed_t>;
  };

  // MAP skeleton used to emulate SIMD operations
  template<typename Out, typename... Bs>
  EVE_FORCEINLINE auto rebuild( Bs const&... ps) noexcept
  {
    static constexpr auto sz = count_v<Out>;

    if constexpr( (sz != 0) && !is_vectorized_v<Out> )
    {
      auto const inside = [&](auto const& I)
      {
        return std::tuple_element_t<I,Out>(std::get<I>(ps)...);
      };

      return detail::apply<sz>( [&]( auto const&... I)
      {
        Out that;
        ((std::get<I>(that) = inside(I)),...);
        return that;
      }
      );
    }
    else
    {
      return Out{ps...};
    }
  }

  struct map_
  {
    // Not a lambda as we need force-inlining
    template<typename Func, typename Idx, typename... Ts>
    EVE_FORCEINLINE auto operator()(Func &&fn, Idx const &i, Ts &&... vs) const noexcept
    {
      return std::forward<Func>(fn)(at(std::forward<Ts>(vs), i)...);
    };
  };

  template<typename Fn, typename... Ts>
  EVE_FORCEINLINE decltype(auto) map(Fn &&f, Ts &&... ts) noexcept
  {
    using w_t = typename wide_result<Fn, Ts...>::type;

    auto impl = [&](auto... I)
    {
      return rebuild<w_t>(map_{}(std::forward<Fn>(f), I, std::forward<Ts>(ts)...)...);
    };

    return apply<cardinal_v<w_t>>(impl);
  }

  // AGGREGATE skeleton used to emulate SIMD operations on aggregated wide
  struct aggregate_wide
  {
    // Not a lambda as we need force-inlining
    template<typename Func, typename... Ts>
    EVE_FORCEINLINE auto operator()(Func &&f, Ts &&... ts) const -> decltype(auto)
    {
      using wide_t = typename wide_result<Func, Ts...>::type;
      return wide_t{std::forward<Func>(f)(lower(std::forward<Ts>(ts))...),
                    std::forward<Func>(f)(upper(std::forward<Ts>(ts))...)};
    }
  };

  template<typename Func, typename... Ts>
  EVE_FORCEINLINE auto aggregate(Func &&f, Ts &&... ts)
  {
    return aggregate_wide{}(std::forward<Func>(f), std::forward<Ts>(ts)...);
  }
}

#endif
