//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/shuffle_v2/simplify_plain_shuffle.hpp>

namespace eve::detail
{

// emulated shuffle ------------------------------------

template<typename T, typename... Ts>
EVE_FORCEINLINE auto
shuffle_emulated_no_group(auto p, kumi::tuple<T, Ts...> xs_)
{
  std::array xs = [&]<std::size_t... i>(std::index_sequence<i...>)
  { return std::array {&get<i>(xs_)...}; }(std::make_index_sequence<sizeof...(Ts) + 1> {});

  auto shuffled = kumi::map(
      [&]<std::ptrdiff_t... I>(pattern_t<I...>)
      {
        using N1 = eve::fixed<(std::ptrdiff_t)sizeof...(I)>;
        using T1 = typename T::template rescale<N1>;
        T1 res;

        int res_i = 0;

        for( std::ptrdiff_t in_flat_i : {I...} )
        {
          if( in_flat_i < 0 )
          {
            res.set(res_i++, eve::zero(eve::as<eve::element_type_t<T>> {}));
            continue;
          }

          int input_wide_i  = in_flat_i / T::size();
          int within_wide_i = in_flat_i % T::size();

          const auto& input_wide = (*xs[input_wide_i]);
          res.set(res_i++, input_wide.get(within_wide_i));
        }
        return res;
      },
      idxm::slice_pattern<T::size()>(p));
  return kumi::tuple {shuffled, index<0>};
}

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename... Ts>
EVE_FORCEINLINE auto
shuffle_emulated(pattern_t<I...>, fixed<G>, kumi::tuple<Ts...> xs)
{
  constexpr auto p2 = idxm::to_pattern<idxm::expand_group<G>(std::array {I...})>();
  return shuffle_emulated_no_group(p2, xs);
}

// upscale pattern-------

template<typename Tuple>
constexpr auto
shuffle_v2_combined_l()
{
  constexpr std::ptrdiff_t r = []<std::size_t... i>(std::index_sequence<i...>)
  {
    int res = 0;
    for( std::ptrdiff_t l : {std::tuple_element_t<1, std::tuple_element_t<i, Tuple>>::value...} )
    {
      // did not found a shuffle
      if( l == -1 ) return -1;
      res = l > res ? l : res;
    }
    return res;
  }(std::make_index_sequence<std::tuple_size_v<Tuple>> {});
  return index<r>;
}

// shuffle_v2_driver_call_native

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
shuffle_v2_common_l0_l1(pattern_t<I...>, fixed<G>, kumi::tuple<T, Ts...> xs)
{
  constexpr std::array idxs {I...};

  // l0
  if constexpr( idxm::is_identity(idxs) && G == T::size() )
  {
    return kumi::tuple {get<0>(xs), eve::index<0>};
  }
  // l1
  else if constexpr( idxm::is_zero(idxs) )
  {
    using N1 = eve::fixed<pattern_t<I...>::size() * G>;
    using T1 = typename T::template rescale<N1>;
    return kumi::tuple {T1 {typename T1::value_type(0)}, eve::index<1>};
  }
  else return kumi::tuple {no_matching_shuffle_t {}, eve::index<-1>};
}

template<typename NativeSelector,
         std::ptrdiff_t G,
         std::ptrdiff_t... I,
         typename... Ts,
         std::size_t... i>
EVE_FORCEINLINE auto
shuffle_v2_driver_call_native_invoke(NativeSelector     selector,
                                     pattern_t<I...>    p,
                                     fixed<G>           g,
                                     kumi::tuple<Ts...> xs,
                                     std::index_sequence<i...>)
{
  if constexpr( auto r = shuffle_v2_common_l0_l1(p, g, xs);
                std::tuple_element_t<1, decltype(r)>::value != -1 )
  {
    return r;
  }
  else if constexpr( requires { selector(p, g, get<i>(xs)...); } )
  {
    return selector(p, g, get<i>(xs)...);
  }
  else { return kumi::tuple {no_matching_shuffle_t {}, eve::index<-1>}; }
}

template<typename NativeSelector, std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
shuffle_v2_driver_call_native(NativeSelector        selector,
                              pattern_t<I...>       p,
                              fixed<G>              g,
                              kumi::tuple<T, Ts...> xs)
{
  auto xgp = simplify_plain_shuffle(p, g, xs);

  auto r = shuffle_v2_driver_call_native_invoke(
      selector,
      xgp.p,
      xgp.g,
      xgp.x,
      std::make_index_sequence<std::tuple_size_v<decltype(xgp.x)>> {});
  auto [shuffled, l] = r;
  if constexpr( decltype(l)::value == -1 ) return r;
  else
  {
    using N1 = eve::fixed<sizeof...(I) * G>;
    using T1 = typename T::template rescale<N1>;
    return kumi::tuple {eve::bit_cast(shuffled, as<T1> {}), l};
  }
}

// shuffle_v2_driver_another_emulation_check

// Some types might be emulated but not everything.
// Example: arm-v7 emulates double simd.
template<typename NativeSelector, std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
shuffle_v2_driver_another_emulation_check(NativeSelector        selector,
                                          pattern_t<I...>       p,
                                          fixed<G>              g,
                                          kumi::tuple<T, Ts...> xs)
{
  if constexpr( eve::has_emulated_abi_v<T> )
  {
    auto [shuffled_tuple, l] = shuffle_emulated(p, g, xs);
    return kumi::tuple {get<0>(shuffled_tuple), l};
  }
  else return shuffle_v2_driver_call_native(selector, p, g, xs);
}

// shuffle_v2_driver_wide_logicals

template<typename NativeSelector, std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
shuffle_v2_driver_wide_logicals(NativeSelector        selector,
                                pattern_t<I...>       p,
                                fixed<G>              g,
                                kumi::tuple<T, Ts...> xs)
{
  using abi_type = typename T::abi_type;
  if constexpr( !logical_simd_value<T> || !abi_type::is_wide_logical )
  {
    return shuffle_v2_driver_another_emulation_check(selector, p, g, xs);
  }
  else
  {
    auto r = shuffle_v2_driver_another_emulation_check(
        selector, p, g, kumi::map([](auto x) { return x.mask(); }, xs));
    auto [bits, l] = r;
    if constexpr( decltype(l)::value == -1 ) return r;
    else
    {
      using N1 = typename decltype(bits)::cardinal_type;
      using L1 = typename T::template rescale<N1>;
      return kumi::make_tuple(eve::bit_cast(bits, as<L1> {}), l);
    }
  }
}

// shuffle_v2_driver_drop_unsued
template<typename NativeSelector, std::ptrdiff_t G, typename T, typename... Ts>
struct shuffle_v2_driver_drop_unsued
{
  NativeSelector        selector;
  fixed<G>              g;
  kumi::tuple<T, Ts...> xs;

  template<std::ptrdiff_t... I> EVE_FORCEINLINE auto operator()(pattern_t<I...> p) const
  {
    constexpr auto p2_selected_wides = idxm::drop_unused_wides<T::size() / G>(p);
    constexpr auto p2                = get<0>(p2_selected_wides);
    constexpr auto selected_wides    = get<1>(p2_selected_wides);

    kumi::tuple xs_ = [&]<std::size_t... i>(std::index_sequence<i...>)
    {
      return kumi::tuple {get<selected_wides[i]>(xs)...};
    }(std::make_index_sequence<selected_wides.size()> {});

    return shuffle_v2_driver_wide_logicals(selector, p2, g, xs_);
  }
};

template<typename NativeSelector, std::ptrdiff_t G, typename... Ts>
shuffle_v2_driver_drop_unsued(NativeSelector, eve::fixed<G>, kumi::tuple<Ts...>)
    -> shuffle_v2_driver_drop_unsued<NativeSelector, G, Ts...>;

// shuffle_v2_driver_multiple_registers ------------------------------

// Returns a tuple of native registers (even for one register)
template<typename NativeSelector, std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
shuffle_v2_driver_multiple_registers(NativeSelector selector,
                                     pattern_t<I...>,
                                     fixed<G>              g,
                                     kumi::tuple<T, Ts...> xs)
{
  constexpr auto sub_patterns = []
  {
    constexpr pattern_t<I...> p;
    if constexpr( p.size() * G <= T::size() ) return kumi::tuple {p};
    else return idxm::slice_pattern<T::size() / G>(p);
  }();
  auto each_part   = kumi::map(shuffle_v2_driver_drop_unsued {selector, g, xs}, sub_patterns);
  constexpr auto l = shuffle_v2_combined_l<decltype(each_part)>();
  if constexpr( l() == -1 ) return kumi::tuple {no_matching_shuffle, l};
  else
  {
    auto shuffled = kumi::map([](auto x_l) { return get<0>(x_l); }, each_part);
    return kumi::tuple {shuffled, l};
  }
}

// shuffle_v2_overly_large groups --------------------------

template<typename NativeSelector, std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
shuffle_v2_overly_large_groups(NativeSelector        selector,
                               pattern_t<I...>       p,
                               fixed<G>              g,
                               kumi::tuple<T, Ts...> xs)
{
  if constexpr( G < T::size() ) return shuffle_v2_driver_multiple_registers(selector, p, g, xs);
  else if constexpr( G > T::size() )
  {
    constexpr auto p2 = idxm::to_pattern<idxm::expand_group<G / T::size()>(std::array {I...})>();
    return shuffle_v2_overly_large_groups(selector, p2, eve::lane<T::size()>, xs);
  }
  else if constexpr( G == T::size() )
  {
    // This section is not technically necessary, we could've done G <= T::size(),
    // but it helps to simplify some code.
    //
    // Level: if we just shuffle, then it's 0. If we need a 0 constant - that's 1 but
    //        not on emulated, on emulated we don't count anything.
    constexpr bool has_zeroes = ((I == na_) || ...);
    auto           l          = eve::index < (has_zeroes && !has_emulated_abi_v<T>) ? 1 : 0 > ;
    auto           get_i      = [&]<std::ptrdiff_t i>(eve::index_t<i>)
    {
      if constexpr( i == na_ ) return eve::zero(eve::as<T> {});
      else if constexpr( i == we_ ) return get<0>(xs);
      else return get<i>(xs);
    };
    auto shuffled = kumi::tuple {get_i(eve::index<I>)...};
    return kumi::tuple {shuffled, l};
  }
}

// shuffle_v2_driver_aggregation logic -----------------------------------

struct shuffle_v2_driver_aggregation
{
  template<typename T, typename... Ts>
  static EVE_FORCEINLINE auto aggregate_componets(kumi::tuple<Ts...> components)
  {
    // No callback - can probably use lambda without inlining problems
    return [&]<std::size_t... i>(std::index_sequence<i...>)
    {
      return kumi::tuple {T {get<2 * i>(components), get<2 * i + 1>(components)}...};
    }(std::make_index_sequence<std::tuple_size_v<decltype(components)> / 2> {});
  }

  template<typename NativeSelector,
           std::ptrdiff_t G,
           std::ptrdiff_t... I,
           typename T,
           typename... Ts>
  EVE_FORCEINLINE auto
  operator()(NativeSelector selector, pattern_t<I...> p, fixed<G> g, kumi::tuple<T, Ts...> xs) const
  {
    if constexpr( !has_aggregated_abi_v<T> )
    {
      return shuffle_v2_overly_large_groups(selector, p, g, xs);
    }
    else
    {
      auto lo_hi = kumi::flatten(kumi::map(
          [](auto x)
          {
            auto [l, h] = x.slice();
            return kumi::tuple {l, h};
          },
          xs));

      auto r = operator()(selector, p, g, lo_hi);

      auto [shuffled, l] = r;

      if constexpr( decltype(l)::value == -1 || pattern_t<I...>::size() * G < T::size() ) return r;
      else return kumi::tuple {aggregate_componets<T>(shuffled), l};
    }
  }
};

// shuffle_v2_driver_bundle logic -----------------------------------------

template<typename> struct had_no_matching_shuffle;
template<typename... Ts> struct had_no_matching_shuffle<kumi::tuple<Ts...>>
{
  static constexpr bool value = (std::same_as<Ts, no_matching_shuffle_t> || ...);
};

template<typename T> constexpr bool had_no_matching_shuffle_v = had_no_matching_shuffle<T>::value;

struct shuffle_v2_driver_bundle
{
  template<typename T, typename... Ts> auto split_by_field(kumi::tuple<T, Ts...> xs) const noexcept
  {
    // no parameters - can use lambdas
    auto get_one_field = [&]<std::ptrdiff_t i>(index_t<i>)
    { return kumi::map([](auto x) { return get<i>(x); }, xs); };

    return [&]<std::size_t... field_i>(std::index_sequence<field_i...>)
    {
      return kumi::tuple {get_one_field(index<(std::ptrdiff_t)field_i>)...};
    }(std::make_index_sequence<std::tuple_size_v<T>> {});
  }

  template<typename Bundle, typename... Ts>
  auto map_components(kumi::tuple<Ts...> result_per_field) const noexcept
  {
    auto field_results = kumi::transpose(result_per_field);

    return kumi::map(
        []<typename Field, typename... Fields>(kumi::tuple<Field, Fields...> field_res)
        {
          using N1 = typename Field::cardinal_type;
          using T1 = typename Bundle::template rescale<N1>;
          return T1 {field_res};
        },
        field_results);
  }

  template<typename NativeSelector, typename Pattern, typename G> struct recurse
  {
    NativeSelector selector;
    recurse(NativeSelector selector, Pattern, G) : selector(selector) {}

    EVE_FORCEINLINE
    auto operator()(auto xs) const noexcept
    {
      return shuffle_v2_driver_bundle {}(selector, Pattern {}, G {}, xs);
    }
  };

  template<typename NativeSelector,
           std::ptrdiff_t G,
           std::ptrdiff_t... I,
           typename T,
           typename... Ts>
  EVE_FORCEINLINE auto
  operator()(NativeSelector selector, pattern_t<I...> p, fixed<G> g, kumi::tuple<T, Ts...> xs) const
  {
    if constexpr( !product_simd_value<T> )
    {
      return shuffle_v2_driver_aggregation {}(selector, p, g, xs);
    }
    else
    {
      auto fields    = split_by_field(xs);
      auto each_part = kumi::map(recurse {selector, p, g}, fields);

      constexpr auto l = shuffle_v2_combined_l<decltype(each_part)>();
      if constexpr( l() == -1 ) { return kumi::tuple {no_matching_shuffle_t {}, eve::index<-1>}; }
      else
      {
        auto result_per_field = kumi::map([](auto x_l) { return get<0>(x_l); }, each_part);
        auto shuffled         = map_components<T>(result_per_field);
        return kumi::tuple {shuffled, l};
      }
    }
  }
};

// start shuffling --------------------------------------

template<typename NativeSelector, std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
shuffle_v2_driver_start(NativeSelector        selector,
                        pattern_t<I...>       p,
                        fixed<G>              g,
                        kumi::tuple<T, Ts...> xs)
{
  if constexpr( !eve::supports_simd ) return shuffle_emulated(p, g, xs);
  else return shuffle_v2_driver_bundle {}(selector, p, g, xs);
}

// entry point -----------------------------------------

template<typename T, typename... Ts>
EVE_FORCEINLINE auto
shuffle_v2_driver_construct_result(kumi::tuple<T, Ts...> shuffled)
{
  if constexpr( sizeof...(Ts) == 0 ) return get<0>(shuffled);
  else
  {
    using e_t = kumi::tuple<element_type_t<T>, element_type_t<Ts>...>;
    using N   = typename T::cardinal_type;
    return eve::as_wide_t<e_t, N> {shuffled};
  }
}

template<typename NativeSelector, std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
shuffle_v2_driver_impl_(EVE_SUPPORTS(cpu_),
                        NativeSelector        selector,
                        pattern_t<I...>       p,
                        fixed<G>              g,
                        kumi::tuple<T, Ts...> xs)
{
  auto r             = shuffle_v2_driver_start(selector, p, g, xs);
  auto [shuffled, l] = r;
  if constexpr( decltype(l)::value == -1 ) return r;
  else return kumi::tuple {shuffle_v2_driver_construct_result(shuffled), l};
}
}
