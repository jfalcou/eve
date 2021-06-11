//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/range.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>
#include <algorithm>
#include <type_traits>
#include <utility>

namespace eve::detail
{
  // Value extraction from RandomAccessRange
  template<typename T> EVE_FORCEINLINE
  constexpr decltype(auto) at(T &&t, std::size_t i) noexcept requires(has_indexed_get<T>)
  {
    return std::forward<T>(t).get(i);
  }

  template<typename T> EVE_FORCEINLINE
  constexpr decltype(auto) at(T &&t, std::size_t) noexcept requires(!has_indexed_get<T>)
  {
    return std::forward<T>(t);
  }

  // Subparts extraction
  template<typename T>
  EVE_FORCEINLINE constexpr auto upper(T &&t) noexcept
  {
    using u_t = std::remove_cvref_t<T>;
    if constexpr(simd_value<u_t>) return std::forward<T>(t).slice(upper_);
    else                          return std::forward<T>(t);
  }

  // Lower values extraction
  template<typename T>
  EVE_FORCEINLINE constexpr auto lower(T &&t) noexcept
  {
    using u_t = std::remove_cvref_t<T>;
    if constexpr(simd_value<u_t>) return std::forward<T>(t).slice(lower_);
    else                          return std::forward<T>(t);
  }

  // Compute a transformed wide type
  template<typename F, typename... Ts>
  struct wide_result
  {
    static constexpr std::size_t card_v = std::max({eve::cardinal_v<std::decay_t<Ts>>...});
    using value_t                       = decltype(std::declval<F>()(at(std::declval<Ts>(), 0)...));
    using fixed_t                       = fixed<card_v>;

    template<typename S> struct widen : as_wide<S, fixed_t> {};

    using base  = std::conditional_t< kumi::product_type<value_t>
                                    , kumi::remap_type<widen,value_t>
                                    , as_wide<value_t, fixed_t>
                                    >;
    using type = typename base::type;
  };

  // MAP skeleton used to emulate SIMD operations
  template<typename Out, typename... Bs>
  EVE_FORCEINLINE auto rebuild( Bs const&... ps) noexcept
  {
    auto const inside = [&]<typename I>(I)
    {
      return std::tuple_element_t<I::value,Out>(kumi::get<I::value>(ps)...);
    };

    return detail::apply<kumi::size<Out>::value>( [&]( auto const&... I)
    {
      Out that;
      ((kumi::get<std::decay_t<decltype(I)>::value>(that) = inside(I)),...);
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

    if constexpr( kumi::product_type<element_type_t<w_t>> )
    {
      return  apply<cardinal_v<std::tuple_element_t<0,w_t>>>
              ( [&](auto... I)
                {
                  return rebuild<w_t>(map_{}(std::forward<Fn>(f), I, std::forward<Ts>(ts)...)...);
                }
              );
    }
    else
    {
      return apply<cardinal_v<w_t>> ( [&](auto... I)
                                      {
                                        return w_t{ map_{}( std::forward<Fn>(f)
                                                          , I
                                                          , std::forward<Ts>(ts)...
                                                          )...
                                                  };
                                      }
                                    );
    }
  }

  // AGGREGATE skeleton used to emulate SIMD operations on aggregated wide
  template<std::size_t I> struct aggregate_step
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr auto subpart(T &t) noexcept
    {
      if constexpr(simd_value<T>) return t.storage().template get<I>();
      else                        return t;
    }

    template<typename T>
    static EVE_FORCEINLINE constexpr auto subpart(T const &t) noexcept
    {
      if constexpr(simd_value<T>) return t.storage().template get<I>();
      else                        return t;
    }

    // Not a lambda as we need force-inlining
    template<typename Func, typename Out, typename... Ts>
    static EVE_FORCEINLINE auto perform(Func &&f, Out& dst, Ts &... ts) -> decltype(auto)
    {
      dst.template get<I>() =  std::forward<Func>(f)( subpart(ts)... );
    }

    template<typename Func, typename Out, typename... Ts>
    static EVE_FORCEINLINE auto perform(Func &&f, Out& dst, Ts const&... ts) -> decltype(auto)
    {
      dst.template get<I>() =  std::forward<Func>(f)( subpart(ts)... );
    }
  };

  // Extract the # of registers used by a wide (0 if T is scalar)
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
