//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/range.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>
#include <algorithm>
#include <utility>
#include <tuple>

namespace eve::detail
{
  // Value extraction from RandomAccessRange
  template<typename T> EVE_FORCEINLINE
  constexpr decltype(auto) at(T &&t, std::size_t i) noexcept requires(has_random_access<T>)
  {
    return std::forward<T>(t)[ i ];
  }

  template<typename T> EVE_FORCEINLINE
  constexpr decltype(auto) at(T &&t, std::size_t) noexcept requires(!has_random_access<T>)
  {
    return std::forward<T>(t);
  }

  // Subparts extraction
  template<typename T>
  EVE_FORCEINLINE constexpr auto upper(T &&t) noexcept
  {
    using u_t = std::remove_cvref_t<T>;
    if constexpr(simd_value<u_t>) return eve::detail::slice(std::forward<T>(t), upper_);
    else                          return std::forward<T>(t);
  }

  // Lower values extraction
  template<typename T>
  EVE_FORCEINLINE constexpr auto lower(T &&t) noexcept
  {
    using u_t = std::remove_cvref_t<T>;
    if constexpr(simd_value<u_t>) return eve::detail::slice(std::forward<T>(t), lower_);
    else                          return std::forward<T>(t);
  }

  // Compute a transformed wide type
  template<typename F, typename... Ts>
  struct wide_result
  {
    static constexpr std::size_t card_v = std::max({eve::cardinal_v<std::decay_t<Ts>>...});
    using value_t                       = decltype(std::declval<F>()(at(std::declval<Ts>(), 0)...));
    using fixed_t                       = fixed<card_v>;
    using type                          = as_wide_t<value_t, fixed_t>;
  };

  // MAP skeleton used to emulate SIMD operations
  template<typename Out, typename... Bs>
  EVE_FORCEINLINE auto rebuild( Bs const&... ps) noexcept
  {
    static constexpr auto sz = count_v<Out>;

    auto const inside = [&](auto const& I)
    {
      using idx_t = std::decay_t<decltype(I)>;
      return std::tuple_element_t<idx_t::value,Out>(std::get<idx_t::value>(ps)...);
    };

    return detail::apply<sz>( [&]( auto const&... I)
    {
      Out that;
      ((std::get<std::decay_t<decltype(I)>::value>(that) = inside(I)),...);
      return that;
    }
    );
  }

  struct map_
  {
    // Not a lambda as we need force-inlining
    template<typename Func, typename Idx, typename... Ts>
    EVE_FORCEINLINE auto operator()(Func &&fn, Idx const &i, Ts &&... vs) const noexcept
    {
      return std::forward<Func>(fn)(at(std::forward<Ts>(vs), i)...);
    }
  };

  template<typename Fn, typename... Ts>
  EVE_FORCEINLINE decltype(auto) map(Fn &&f, Ts &&... ts) noexcept
  {
    using w_t = typename wide_result<Fn, Ts...>::type;

    auto impl = [&](auto... I)
    {
      static constexpr auto sz = count_v<element_type_t<w_t>>;

      if constexpr( sz != 0 )
      {
        return rebuild<w_t>(map_{}(std::forward<Fn>(f), I, std::forward<Ts>(ts)...)...);
      }
      else
      {
        return w_t{map_{}(std::forward<Fn>(f), I, std::forward<Ts>(ts)...)...};
      }
    };

    return apply<cardinal_v<w_t>>(impl);
  }

  // AGGREGATE skeleton used to emulate SIMD operations on aggregated wide
  template<std::size_t I> struct aggregate_step
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr auto subpart(T &&t) noexcept
    {
      using u_t = std::remove_cvref_t<T>;
      if constexpr(simd_value<u_t>) return std::forward<T>(t).storage().template get<I>();
      else                          return std::forward<T>(t);
    }

    // Not a lambda as we need force-inlining
    template<typename Func, typename Out, typename... Ts>
    static EVE_FORCEINLINE auto perform(Func &&f, Out& dst, Ts &&... ts) -> decltype(auto)
    {
      dst.template get<I>() =  std::forward<Func>(f)( subpart(std::forward<Ts>(ts))... );
    }
  };

  // Extract th e# of registers used by a wide (0 if T is scalar)
  template<typename T> constexpr auto replication() noexcept
  {
    if constexpr( scalar_value<T> )             return 0;
    else if constexpr(has_aggregated_abi_v<T>)  return T::storage_type::replication;
    else                                        return 1;
  }

  // Check if O o = f(I{}...) can be optimized as a non-recursive aggregate call
  template<typename O, typename... I> constexpr bool is_fully_sliceable() noexcept
  {
    constexpr std::size_t reps[]  = { replication<std::decay_t<I>>()... };
    constexpr auto              w = replication<O>();
    bool r = true;

    // If output is not aggregated, we need to go recursive
    if(replication<O>() <= 1) return false;

    // Check that every parts are sliceable
    for(auto s : reps) r = r && (s == w || s == 0);
    return r;
  }

  template<typename Func, typename... Ts>
  EVE_FORCEINLINE auto aggregate(Func &&f, Ts &&... ts)
  {
    using wide_t = typename wide_result<Func, Ts...>::type;

    // Full sliceable case
    if constexpr( is_fully_sliceable<wide_t,std::decay_t<Ts>...>() )
    {
      wide_t that;

      // If everything can be sliced in equal sub-parts, we save compile-time and
      // simplify debugging by iterating over all smallest sub-parts
      detail::apply<replication<wide_t>()>
      ( [&]<typename... I>(I const&...)
        {
          ( ( aggregate_step<I::value>::perform ( std::forward<Func>(f)
                                                , that.storage()
                                                , std::forward<Ts>(ts)...
                                                )
            ),...
          );
        }
      );

      return that;
    }
    // Recursive case
    else
    {
      // We end up there if we have a difference of # of replications inside
      // This happens in conversions context or when we call a function on a
      // AVX/AVX2 type with no implementation.
      return wide_t{std::forward<Func>(f)(lower(std::forward<Ts>(ts))...),
                    std::forward<Func>(f)(upper(std::forward<Ts>(ts))...)};
    }
  }
}

