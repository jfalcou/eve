//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_SKELETON_HPP_INCLUDED
#define EVE_DETAIL_SKELETON_HPP_INCLUDED

#include <eve/detail/is_range.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/ext/is_wide.hpp>
#include <eve/ext/has_abi.hpp>
#include <eve/cardinal.hpp>
#include <algorithm>
#include <utility>

namespace eve::detail
{
  // Value extraction from RandomAccessRange
  template<typename T> EVE_FORCEINLINE constexpr decltype(auto) at( T&& t, std::size_t i ) noexcept
  {
    if constexpr(is_random_access_range_v<T>)
      return std::forward<T>(t)[i];
    else
      return std::forward<T>(t);
  }

  // Upper values extraction
  template<typename T> EVE_FORCEINLINE constexpr auto upper( T&& t ) noexcept
  {
    if constexpr( ext::is_wide_v<T> )
      return eve::detail::slice(std::forward<T>(t),upper_);
    else
      return std::forward<T>(t);
  }

  // Lower values extraction
  template<typename T> EVE_FORCEINLINE constexpr auto lower( T&& t ) noexcept
  {
    if constexpr( ext::is_wide_v<T> )
      return eve::detail::slice(std::forward<T>(t),lower_);
    else
      return std::forward<T>(t);
  }

  // Compute a transformed wide type
  template<typename F, typename... Ts>
  struct wide_result
  {
    template<typename T>  using       card_t = eve::cardinal<std::decay_t<T>>;
    static constexpr      std::size_t card_v = std::max( {card_t<Ts>::value...} );
    using value_t = decltype(std::declval<F>()(at(std::declval<Ts>(),0)...));
    using type    = wide<value_t,fixed<card_v>>;
  };

  // MAP skeleton used to emulate SIMD operations
  struct map_
  {
    // Not a lambda as we need force-inlining
    template<typename Func, typename Idx, typename... Ts>
    EVE_FORCEINLINE auto operator()(Func&& fn, Idx const& i, Ts&&... vs) const noexcept
    {
      return std::forward<Func>(fn)(at(std::forward<Ts>(vs),i)...);
    };
  };

  template<typename Fn, typename... Ts>
  EVE_FORCEINLINE decltype(auto) map(Fn&& f, Ts&&... ts)
  {
    using w_t  = typename wide_result<Fn,Ts...>::type;

    auto impl = [&](auto... I)  { return w_t{ map_{}( std::forward<Fn>(f), I
                                                    , std::forward<Ts>(ts)...
                                                    )...
                                            };
                                };

    return apply<w_t::static_size>(impl);
  }

  // AGGREGATE skeleton used to emulate SIMD operations on aggregated wide
  struct aggregate_wide
  {
    // Not a lambda as we need force-inlining
    template<typename Func, typename... Ts>
    EVE_FORCEINLINE auto operator()(Func&& f, Ts&&... ts) const -> decltype(auto)
    {
      using wide_t = typename wide_result<Func,Ts...>::type;
      return  wide_t{ std::forward<Func>(f)( lower(std::forward<Ts>(ts))...)
                    , std::forward<Func>(f)( upper(std::forward<Ts>(ts))...)
                    };
    }
  };

  template<typename Func, typename... Ts>
  EVE_FORCEINLINE auto aggregate(Func&& f, Ts&&... ts)
  {
    return aggregate_wide{}(std::forward<Func>(f),std::forward<Ts>(ts)...);
  }
}

#endif
