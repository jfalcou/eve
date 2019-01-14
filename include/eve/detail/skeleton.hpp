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
#include <eve/ext/is_pack.hpp>
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
    if constexpr( ext::is_pack_v<T> )
    {
      if constexpr( ext::has_abi_v<T,avx_> )
        return std::forward<T>(t).slice(upper_);
      else
        return std::forward<T>(t).storage()[1];
    }
    else
    {
      return std::forward<T>(t);
    }
  }

  // Lower values extraction
  template<typename T> EVE_FORCEINLINE constexpr auto lower( T&& t ) noexcept
  {
    if constexpr( ext::is_pack_v<T> )
    {
      if constexpr( ext::has_abi_v<T,avx_> )
        return std::forward<T>(t).slice(lower_);
      else
        return std::forward<T>(t).storage()[0];
    }
    else
    {
      return std::forward<T>(t);
    }
  }

  // Compute a transformed pack type
  template<typename F, typename... Ts>
  struct pack_result
  {
    using value_t = decltype(std::declval<F>()(at(std::declval<Ts>(),0)...));

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
  EVE_FORCEINLINE auto aggregate(Func&& f, Ts&&... ts)
  {
    using pack_t = typename pack_result<Func,Ts...>::type;

    auto aggregate_pack = [](auto&& f, auto&&... ts) -> decltype(auto)
    {
      return  pack_t{ std::forward<Func>(f)( lower(std::forward<Ts>(ts))...)
                    , std::forward<Func>(f)( upper(std::forward<Ts>(ts))...)
                    };
    };

    return aggregate_pack(std::forward<Func>(f),std::forward<Ts>(ts)...);
  }
}

#endif
