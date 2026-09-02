//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/deps/kumi.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/traits/apply_fp16.hpp>
#include <eve/arch/cpu/as_register.hpp>
#include <type_traits>
#include <algorithm>
#include <utility>

namespace eve::_
{
  // Extract Ith element of a wide or propagate the value if non SIMD
  template<std::size_t I, typename T> EVE_FORCEINLINE
  constexpr decltype(auto) get_at(T &&t) noexcept
  {
    if constexpr(simd_value<T>) return EVE_FWD(t).get(I);
    else                        return EVE_FWD(t);
  }

  // Compute a transformed wide type
  template<typename F, typename... Ts>
  struct wide_result;

  // Checks that a map is valid so that callable that discard this and try another route
  template<typename F, typename... Ts>
  requires std::invocable<F, decltype(eve::_::get_at<0>(std::declval<Ts>()))...> // Feels wrong
  struct  wide_result<F,Ts...>
  {
    static constexpr std::size_t card = std::max({cardinal_v<std::decay_t<Ts>>...});
    using value_t                     = std::invoke_result_t<F, decltype(eve::_::get_at<0>(std::declval<Ts>()))...>;
    using fixed_t                     = fixed<card>;

    template<typename S> 
    using widen = as_wide<S, fixed_t>;

    using base  = _::conditional_t< eve::product_type<value_t>
                                  , kumi::as_tuple<value_t,widen>   // tuple of chunked element
                                  , as_wide<value_t, fixed_t>       // scalar -> simd
                                  >;
    using type = typename base::type;
  };

  struct build
  {
    template<typename... Ts>
    EVE_FORCEINLINE auto operator()( Ts const&... ts ) const noexcept
    {
      constexpr std::size_t cardinal = sizeof...(Ts);

      if constexpr ( eve::product_type<Ts> && ...)
      {
        return 
      }
      else

      //auto const inside = [&]<typename I>(I)
      //{
      //  return std::tuple_element_t<I::value,Out>(kumi::get<I::value>(ps)...);
      //};
      //
      //return _::apply<kumi::size<Out>::value>( [&]( auto const&... I)
      //{
      //  Out that;
      //  ((kumi::get<std::decay_t<decltype(I)>::value>(that) = inside(I)),...);
      //  return that;
      //}
      //);
    } inline constexpr builder;
  }

  template<typename Func, typename... Ts>
  EVE_FORCEINLINE typename wide_result<Fn, Ts...>::type map(Func f, Ts &&... ts) noexcept
  {
    constexpr std::size_t cardinal = std::max({cardinal_v<Ts>...});
    return map_<cardinal>(builder, [&, f](auto I){ return f(eve::_::get_at<I>(EVE_FWD(ts))...); });
  }

  // Apply the function `f` to every `ts` once sliced.
  template<typename Func, typename... Ts>
  EVE_FORCEINLINE auto slice_apply(Func f, Ts... ts)
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

  // Returns decltype(auto) to ensure optimal codegen when dealing with non-product-type outputs
  template<typename T>
  constexpr decltype(auto) rewrap(T const& inner)
  {
    // Handle the case where the returned type's storage is itself a product type.
    // Functions returning zipped values need an extra level of storage wrapping.
    // This doesn't applies to blobs as they are already in the correct format and the result was already flattened.
    // The check on range is used due to arrays now being considered `product types`

    //if constexpr (!range<storage_t> && eve::product_type<storage_t> && !instance_of<storage_t, blob>)
    //{
    //  return kumi::generate<kumi::size_v<storage_t>>([&]<std::size_t I>(kumi::index_t<I>)
    //    {
    //      using inner_wide_t = kumi::element_t<I, storage_t>;
    //      // Whether we should re-wrap the inner storage into the proper product type.
    //      if constexpr (has_aggregated_abi_v<inner_wide_t> || eve::product_type<kumi::element_t<0, T>>)
    //      {
    //        return kumi::apply([&](auto... m){ return inner_wide_t { kumi::get<I>(m.storage())... }; }, inner);
    //      }
    //      else
    //      {
    //        return kumi::get<I>(inner);
    //      }
    //    });
    //}
    else
    {
      using current_wide = kumi::element_t<0, T>;
      constexpr std::ptrdiff_t current_card = current_wide::size();
      constexpr std::ptrdiff_t expected_card = expected_cardinal_v<typename current_wide::value_type>;
      using expected_wide = typename current_wide::template rescale<fixed<expected_card>>;

      if constexpr (current_card < expected_card)
      {
        auto chunks = kumi::map([&]<typename W>(W const& w) -> decltype(auto)
        {
          return kumi::apply([](auto... c)
          {
            return expected_wide { c... };
          }, w);
        }, kumi::chunks<expected_card / current_card>(inner));

        if constexpr (kumi::size_v<decltype(chunks)> == 1) return expected_wide{ kumi::get<0>(chunks) };
        else                                               return chunks;
      }
      else
      {
        return inner;
      }
    }
  };

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

      // Zip all tuples of ready-to-aggregate value to gather corresponding chunks
      // Flatten the per-slice result in case it still contains aggregated values.
      // In order to prepare them for the `rewrap` operation.
      auto parts        = kumi::zip(slicer(ts)...);
      auto processed    = kumi::map([f](auto e){ return kumi::apply(f, e); }, parts);
      auto fundamental  = kumi::flatten_all(processed);
       // Imo here the idea is transpose -> rebuild final type

      using small_result_t  = kumi::element_t<0,decltype(fundamental)>; //decltype(process(kumi::index<0>));
      using wide_t          = typename small_result_t::template rescale<fixed<small_result_t::size() * max_repl>>;
      using storage_t       = typename wide_t::storage_type;

     
      //auto inner_output = kumi::apply([&](auto... m)
      //  {
      //    auto v_or_t = []<typename V>(V v) {
      //      if constexpr (has_aggregated_abi_v<V>) return v.storage().slice_to_expected();
      //      else                                   return kumi::make_tuple(v);
      //    };
      //
      //    return kumi::cat(v_or_t(m)...);
      //  }, kumi::generate<max_repl>(process));     
      //
      const auto out = rewrap(fundamental);

      if constexpr (has_emulated_abi_v<wide_t> && product_type<decltype(out)>)
        return kumi::apply([](auto... m) { return wide_t{m...}; }, out);
      else if constexpr (has_aggregated_abi_v<wide_t>)
        return wide_t { storage_t { out } };
      else
        return out;
    }
    else
    {
      return slice_apply(f, ts...);
    }
  }
}
