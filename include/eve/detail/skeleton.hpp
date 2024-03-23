//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/range.hpp>
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
  // Value extraction from RandomAccessRange
  template<typename T> EVE_FORCEINLINE
  constexpr decltype(auto) at(T &&t, std::size_t i) noexcept requires(has_indexed_get<T>)
  {
    return EVE_FWD(t).get(i);
  }

  template<typename T> EVE_FORCEINLINE
  constexpr decltype(auto) at(T &&t, std::size_t) noexcept requires(!has_indexed_get<T>)
  {
    return EVE_FWD(t);
  }

  // Compute a transformed wide type
  template<typename F, typename... Ts>
  struct wide_result
  {
    template<typename T>
    static constexpr std::ptrdiff_t card() noexcept
    {
      if constexpr(simd_value<T>) return T::size(); else return 1;
    }

    static constexpr std::size_t card_v = std::max({card<std::decay_t<Ts>>()...});
    using value_t                       = decltype(std::declval<F>()(at(std::declval<Ts>(), 0)...));
    using fixed_t                       = fixed<card_v>;

    template<typename S> struct widen : as_wide<S, fixed_t> {};

    using base  = std::conditional_t< kumi::product_type<value_t>
                                    , kumi::as_tuple<value_t,widen>
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
      return EVE_FWD(fn)(at(EVE_FWD(vs), i)...);
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
                  return rebuild<w_t>(map_{}(EVE_FWD(f), I, EVE_FWD(ts)...)...);
                }
              );
    }
    else
    {
      return apply<cardinal_v<w_t>> ( [&](auto... I)
                                      {
                                        return w_t{ map_{}( EVE_FWD(f)
                                                          , I
                                                          , EVE_FWD(ts)...
                                                          )...
                                                  };
                                      }
                                    );
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
    using wide_t = typename wide_result<Func, Ts...>::type;
    return kumi::apply([&f](auto... m) { return wide_t { f(get<0>(m)...), f(get<1>(m)...)}; }, parts);
  }
}
