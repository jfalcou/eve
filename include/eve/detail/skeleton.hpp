//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>
#include <type_traits>
#include <algorithm>
#include <utility>

namespace eve::detail
{
  // Extract ith element of a wide or propagate the value if non SIMD
  template<typename T> EVE_FORCEINLINE
  constexpr decltype(auto) get_at(T &&t, std::size_t i) noexcept
  {
    if constexpr(simd_value<std::decay_t<T>>) return EVE_FWD(t).get(i);
    else                                      return EVE_FWD(t);
  }

  template<typename Out, typename... Bs>
  EVE_FORCEINLINE auto rebuild( Bs const&... ps) noexcept
  {
    using kumi::get;

    auto const inside = [&]<typename I>(I)
    {
      return std::tuple_element_t<I::value, Out>(get<I::value>(ps)...);
    };

    return detail::apply<kumi::size<Out>::value>( [&]( auto const&... I)
      {
        Out that;
        ((get<std::decay_t<decltype(I)>::value>(that) = inside(I)),...);
        return that;
      }
    );
  }

  // MAP skeleton used to emulate SIMD operations
  struct map_
  {
    // Not a lambda as we need force-inlining
    template<typename Func, typename Idx, typename... Ts>
    EVE_FORCEINLINE auto operator()(Func &&fn, Idx i, Ts &&... vs) const noexcept -> decltype(EVE_FWD(fn)(eve::detail::get_at(EVE_FWD(vs), i)...))
    {
      return EVE_FWD(fn)(eve::detail::get_at(EVE_FWD(vs), i)...);
    }
  };

  template<typename R, typename Fn, typename... Ts>
  EVE_FORCEINLINE R map_pt(as<R>, Fn &&f, Ts &&... ts) noexcept
  requires( requires{ EVE_FWD(f)(eve::detail::get_at(EVE_FWD(ts), 0)...); } )
  {
    if constexpr (kumi::product_type<element_type_t<R>>)
    {
      return  apply<cardinal_v<std::tuple_element_t<0, R>>>
              ( [&](auto... I)
                {
                  return rebuild<R>(map_{}(EVE_FWD(f), I, EVE_FWD(ts)...)...);
                }
              );
    }
    else
    {
      return apply<cardinal_v<R>>([&](auto... I) { return R{map_{}( EVE_FWD(f), I, EVE_FWD(ts)...)...}; } );
    }
  }

  template<typename Func, typename... Ts>
  EVE_FORCEINLINE auto aggregate(Func f, Ts... ts)
  {
    // We use this function to turn every parameters into either a pair of slices
    // or a pair of scalar so that the apply later down is more regular
    auto slicer = []<typename T>(T t)
    {
      if constexpr(simd_value<T>) return t.slice(); else return kumi::make_tuple(t,t);
    };

    // Build the lists of all ready-to-aggregate values
    auto parts = kumi::make_tuple(slicer(ts)...);

    // Apply f on both side of the slices and re-combine
    using half_result_t = decltype(f(get<0>(slicer(ts))...));
    using wide_t = typename half_result_t::template rescale<typename half_result_t::cardinal_type::combined_type>;

    return kumi::apply([&f](auto... m) { return wide_t { f(get<0>(m)...), f(get<1>(m)...)}; }, parts);
  }
}
