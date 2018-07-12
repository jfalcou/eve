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
#include <eve/cardinal.hpp>
#include <algorithm>
#include <utility>

namespace eve { namespace detail
{
  // Value extraction from RandomAccessRange
  template<typename T> EVE_FORCEINLINE constexpr decltype(auto) at( T&& t, std::size_t i ) noexcept
  {
    if constexpr(is_random_access_range_v<T>)
      return std::forward<T>(t)[i];
    else
      return std::forward<T>(t);
  }

  // Compute a transformed pack type
  template<typename F, typename... Ts>
  struct pack_result
  {
    using fn_t    = std::decay_t<F>;
    using value_t = decltype(std::declval<fn_t>()(at(std::declval<std::decay_t<Ts>>(),0)...));

    template<typename T>
    using card_t = eve::cardinal<std::decay_t<T>>;

    static constexpr std::size_t card_v = std::max( {card_t<Ts>::value...} );

    using type    = pack<value_t,fixed<card_v>>;
  };

  // MAP skeleton used to emulate SIMD operations
  template<typename Func, typename... Ts>
  EVE_FORCEINLINE decltype(auto) map(Func&& f, Ts&&... ts)
  {
    using pack_t  = typename pack_result<Func,Ts...>::type;

    auto impl = [&](auto... I)
                {
                  auto eval = [](Func&& fn, auto const& i, Ts&&... vs)
                  {
                    return std::forward<Func>(fn)(at(std::forward<Ts>(vs),i)...);
                  };

                  return pack_t{ eval( std::forward<Func>(f), I, std::forward<Ts>(ts)...)... };
                };

    return apply<pack_t::static_size>(impl);
  }

  // AGGREGATE skeleton used to emulate SIMD operations on aggregated pack
  template<typename Func, typename... Ts>
  EVE_FORCEINLINE decltype(auto) aggregate(Func&& f, Ts&&... ts)
  {
    using pack_t  = typename pack_result<Func,Ts...>::type;
    using stg_t   = typename pack_t::storage_type;

    return pack_t ( stg_t { std::forward<Func>(f)(std::forward<Ts>(ts).storage()[0]...)
                          , std::forward<Func>(f)(std::forward<Ts>(ts).storage()[1]...)
                          }
                  );
  }
} }

#endif
