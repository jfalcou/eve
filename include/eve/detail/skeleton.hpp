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

  // Checks that a map is valid so that callable that discard this and try another route
  template<typename F, typename... Ts>
  concept supports_mapping =  requires(F func, Ts... ts)
  {
    { func(eve::detail::get_at(ts, 0)...) };
  };

  // Compute a transformed wide type
  template<typename F, typename... Ts>
  struct wide_result;

  template<typename F, typename... Ts>
  requires supports_mapping<F,Ts...>
  struct wide_result<F,Ts...>
  {
    template<typename T>
    static constexpr std::ptrdiff_t card() noexcept
    {
      if constexpr(simd_value<T>) return T::size(); else return 1;
    }

    static constexpr std::size_t card_v = std::max({card<std::decay_t<Ts>>()...});
    using value_t                       = decltype(std::declval<F>()(eve::detail::get_at(std::declval<Ts>(), 0)...));
    using fixed_t                       = fixed<card_v>;

    template<typename S> struct widen : as_wide<S, fixed_t> {};

    using base  = std::conditional_t< kumi::product_type<value_t>
                                    , kumi::as_tuple<value_t,widen>
                                    , as_wide<value_t, fixed_t>
                                    >;
    using type = typename base::type;
  };

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

  // MAP skeleton used to emulate SIMD operations
  struct map_
  {
    // Not a lambda as we need force-inlining
    template<typename Func, typename Idx, typename... Ts>
    EVE_FORCEINLINE auto operator()(Func &&fn, Idx i, Ts &&... vs) const noexcept
    {
      return EVE_FWD(fn)(eve::detail::get_at(EVE_FWD(vs), i)...);
    }
  };

  template<typename Fn, typename... Ts>
  EVE_FORCEINLINE typename wide_result<Fn, Ts...>::type map(Fn &&f, Ts &&... ts) noexcept
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
      return apply<cardinal_v<w_t>>([&](auto... I) { return w_t{map_{}( EVE_FWD(f), I, EVE_FWD(ts)...)...}; } );
    }
  }

  // Aggregate replication count for a given type
  template<typename T>
  constexpr std::ptrdiff_t replication()
  {
    if constexpr (requires { T::storage_type::replication; }) return T::storage_type::replication;
    else if constexpr (scalar_value<T>)                       return 0;
    else                                                      return 1;
  }

  template<typename... Ts>
  constexpr std::ptrdiff_t max_replication()
  {
    return std::max({ replication<Ts>()... });
  }

  // Returns true if all Ts have the same replication count or 0.
  // That is, if all Ts are either scalars or aggregates with the same internal replication count.
  template<typename... Ts>
  constexpr bool has_same_replication()
  {
    constexpr auto max_repl = max_replication<Ts...>();
    return ((( replication<Ts>() == max_repl) || (replication<Ts>() == 0) ) && ...);
  }

  template<typename Func, typename... Ts>
  EVE_FORCEINLINE auto aggregate(Func f, Ts... ts)
  {
    if constexpr (has_same_replication<Ts...>())
    {
      constexpr auto max_repl = max_replication<Ts...>();

      // Convert all values to tuples of wides of the expected cardinal
      auto slicer = []<typename T>(T t)
      {
        if constexpr (simd_value<T>) return t.storage().slice_to_expected();
        else                         return kumi::fill<max_repl>(t);
      };

      // Build the lists of all ready-to-aggregate values
      auto parts = kumi::make_tuple(slicer(ts)...);
      auto process = [&](auto i) { return kumi::apply([&](auto... p) { return f( get<i>(p)... ); }, parts); };

      using small_result_t = decltype(process(kumi::index<0>));
      using wide_t = typename small_result_t::template rescale<fixed<small_result_t::size() * max_repl>>;
      using storage_t = typename wide_t::storage_type;

      // return decltype(auto) to ensure optimal codegen when dealing with non-product-type outputs
      auto rewrap = [](auto const& inner) -> decltype(auto)
      {
        // Handle the case where the returned type's storage is itself a product type.
        // Functions returning zipped values need an extra level of storage wrapping.
        if constexpr (product_type<storage_t>)
        {
          auto inner_tuple = kumi::generate<kumi::size_v<storage_t>>([&](auto i)
          {
            using inner_wide_t = typename kumi::element_t<i, storage_t>;

            // Whether we should re-wrap the inner storage into the proper product type.
            if constexpr (has_aggregated_abi_v<inner_wide_t>)
            {
              using inner_storage_t = typename inner_wide_t::storage_type;
              return kumi::apply([&](auto... m){ return inner_wide_t { inner_storage_t { kumi::get<i>(m.storage())... } }; }, inner);
            }
            else if constexpr (requires { kumi::get<i>(inner); })
            {
              return kumi::get<i>(inner);
            }
            else
            {
              void*p = inner;
              void* f = kumi::get<i>(inner);
              // static_assert(i < kumi::size_v<inner>, "Index out of bounds for inner tuple");
            }
          });

          return inner_tuple;
        }
        else
        {
          return  inner;
        }
      };

      return wide_t { storage_t { rewrap(kumi::generate<max_repl>([&process](auto i) { return process(i); })) }};
    }
    else
    {
      // We use this function to turn every parameters into either a pair of slices
      // or a pair of scalar so that the apply later down is more regular
      auto slicer = []<typename T>(T t)
      {
        if constexpr (simd_value<T>) return t.slice();
        else                         return kumi::make_tuple(t,t);
      };

      // Build the lists of all ready-to-aggregate values
      auto parts = kumi::make_tuple(slicer(ts)...);

      // Apply f on both side of the slices and re-combine
      using half_result_t = decltype(f(get<0>(slicer(ts))...));
      using wide_t = typename half_result_t::template rescale<typename half_result_t::cardinal_type::combined_type>;

      return kumi::apply([&f](auto... m) { return wide_t { f(get<0>(m)...), f(get<1>(m)...)}; }, parts);
    }
  }
}
