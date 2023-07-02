//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/fundamental_cardinal.hpp>

namespace eve::detail
{

template<typename Internal,
         std::ptrdiff_t G,
         std::ptrdiff_t... I,
         typename T,
         typename N,
         typename... Ts>
EVE_FORCEINLINE auto
canonical_shuffle_adapter_impl_(EVE_SUPPORTS(cpu_),
                                Internal            internal,
                                pattern_t<I...>     p,
                                fixed<G>            g,
                                logical<wide<T, N>> x,
                                Ts... xs)
requires(abi_t<T, N>::is_wide_logical)
{
  auto shuffle_bits = canonical_shuffle_adapter_impl(internal, p, g, x.mask(), xs.mask()...);
  if constexpr( std::same_as<decltype(shuffle_bits), no_matching_shuffle_t> )
  {
    return no_matching_shuffle;
  }
  else
  {
    using N1 = typename decltype(shuffle_bits)::cardinal_type;
    return bit_cast(shuffle_bits, as<logical<wide<T, N1>>> {});
  }
}

template<typename Internal, std::ptrdiff_t G, std::ptrdiff_t... I> struct BundleLambda
{
  Internal internal;

  EVE_FORCEINLINE
  auto operator()(auto... xs) const noexcept
  {
    return canonical_shuffle_adapter_impl(internal, pattern<I...>, lane<G>, xs...);
  }
};

template<typename> struct had_no_matching_shuffle;
template<typename... Ts> struct had_no_matching_shuffle<kumi::tuple<Ts...>>
{
  static constexpr bool value = (std::same_as<Ts, no_matching_shuffle_t> || ...);
};

template<typename T> constexpr bool had_no_matching_shuffle_v = had_no_matching_shuffle<T>::value;

template<typename Internal,
         product_scalar_value T,
         typename N,
         std::ptrdiff_t G,
         std::ptrdiff_t... I,
         typename... Ts>
EVE_FORCEINLINE auto
canonical_shuffle_adapter_impl_(EVE_SUPPORTS(cpu_),
                                Internal internal,
                                pattern_t<I...>,
                                fixed<G>,
                                wide<T, N> x,
                                Ts... xs)
{
  auto each_part = kumi::map(BundleLambda<Internal, G, I...> {internal}, x, xs...);

  if constexpr( had_no_matching_shuffle_v<decltype(each_part)> ) { return no_matching_shuffle; }
  else { return wide<T, N>(each_part); }
}

template<std::size_t N>
constexpr auto
upscale_pattern_impl(std::array<std::ptrdiff_t, N> p)
    -> std::optional<std::array<std::ptrdiff_t, N / 2>>
{
  if( N == 1 ) return std::nullopt;

  std::array<std::ptrdiff_t, N / 2> res {};

  for( int i = 0; i != N / 2; i += 1 )
  {
    int            i2 = i + i;
    std::ptrdiff_t i0 = p[i2];
    std::ptrdiff_t i1 = p[i2 + 1];

    if( i0 == na_ || i1 == na_ )
    {
      if( i0 == i1 || i0 == we_ || i1 == we_ )
      {
        res[i] = na_;
        continue;
      }
      return std::nullopt;
    }

    if( i0 == we_ && i1 == we_ )
    {
      res[i] = we_;
      continue;
    }

    if( i0 == we_ ) i0 = i1 - 1;
    if( i1 == we_ ) i1 = i0 + 1;

    if( i0 + 1 != i1 || i0 % 2 != 0 ) { return std::nullopt; }

    res[i] = i0 / 2;
  }

  return res;
}

template<std::ptrdiff_t... I>
constexpr auto
upscale_pattern(pattern_t<I...> p)
{
  constexpr std::array    p_arr {I...};
  constexpr std::optional attempt = upscale_pattern_impl(p_arr);
  if constexpr( !attempt ) return p;
  else return idxm::to_pattern<*attempt>();
}

template<typename G, typename P, typename... Ts> struct simplified_pattern
{
  kumi::tuple<Ts...> x;
  G                  g;
  P                  p;
};

template<typename G, typename P, typename... Ts>
simplified_pattern(kumi::tuple<Ts...>, G, P) -> simplified_pattern<G, P, Ts...>;

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename N, typename... Ts>
EVE_FORCEINLINE auto
simplify_plain_shuffle1(pattern_t<I...> p, eve::fixed<G> g, eve::wide<T, N> x, Ts... xs)
{
  // On an emulation bitcasting types won't be helpful for anything.
  if constexpr( has_emulated_abi_v<wide<T, N>> )
  {
    return simplified_pattern {kumi::tuple {x, xs...}, g, p};
  }
  else if constexpr( !std::unsigned_integral<T> )
  {
    using u_t = eve::wide<detail::make_integer_t<sizeof(T), unsigned>, N>;
    return simplify_plain_shuffle1(p, g, bit_cast(x, as<u_t> {}), bit_cast(xs, as<u_t> {})...);
  }
  else if constexpr( G >= 2 && sizeof(T) < 8 )
  {
    using up_t = eve::wide<detail::make_integer_t<sizeof(T) * 2, unsigned>, typename N::split_type>;
    return simplify_plain_shuffle1(
        p, eve::lane<G / 2>, bit_cast(x, as<up_t> {}), bit_cast(xs, as<up_t> {})...);
  }
  else if constexpr( fundamental_cardinal_v<T> > N::value )
  {
    constexpr auto next_pattern =
        idxm::fix_indexes_to_fundamental<fundamental_cardinal_v<T>>(std::array {I...}, N::value);
    using T1 = wide<T, fundamental_cardinal_t<T>>;
    return simplify_plain_shuffle1(
        idxm::to_pattern<next_pattern>(), g, bit_cast(x, as<T1> {}), bit_cast(xs, as<T1> {})...);
  }
  else { return simplified_pattern {kumi::tuple {x, xs...}, g, p}; }
}

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
simplify_plain_shuffle2(pattern_t<I...> p, eve::fixed<G> g, T x, Ts... xs)
{
  if constexpr( sizeof...(Ts) == 1
                && idxm::are_below_ignoring_specials(std::array {I...}, T::size() / G) )
  {
    return simplify_plain_shuffle1(p, g, xs...);
  }
  else return simplify_plain_shuffle1(p, g, x, xs...);
}

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
simplify_plain_shuffle3(pattern_t<I...> p, eve::fixed<G> g, T x, Ts... xs)
{
  constexpr std::array idxs {I...};

  if constexpr( sizeof...(Ts) != 1 ) return simplify_plain_shuffle2(p, g, x, xs...);
  else if constexpr( constexpr auto swapped = idxm::swap_xy(idxs, T::size() / G); swapped < idxs )
  {
    return simplify_plain_shuffle2(idxm::to_pattern<swapped>(), g, xs..., x);
  }
  else return simplify_plain_shuffle2(p, g, x, xs...);
}

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename... Ts>
EVE_FORCEINLINE auto
simplify_plain_shuffle(pattern_t<I...>, eve::fixed<G> g, Ts... xs)
{
  constexpr auto p  = pattern<I...>;
  constexpr auto up = upscale_pattern(p);

  if constexpr( up != p ) return simplify_plain_shuffle(up, eve::lane<G * 2>, xs...);
  else return simplify_plain_shuffle3(p, g, xs...);
}

template<typename Internal,
         std::ptrdiff_t G,
         std::ptrdiff_t... I,
         plain_scalar_value T,
         typename N,
         typename... Ts,
         std::size_t... i>
EVE_FORCEINLINE auto
canonical_shuffle_adapter_impl_after_simplification(Internal                       internal,
                                                    pattern_t<I...>                p,
                                                    fixed<G>                       g,
                                                    kumi::tuple<wide<T, N>, Ts...> xs,
                                                    std::index_sequence<i...>)
{
  if constexpr( requires { internal(p, g, get<i>(xs)...); } )
  {
    return internal(p, g, get<i>(xs)...);
  }
  else { return no_matching_shuffle; }
}

template<typename Internal,
         std::ptrdiff_t G,
         std::ptrdiff_t... I,
         plain_scalar_value T,
         typename N,
         typename... Ts>
EVE_FORCEINLINE auto
canonical_shuffle_adapter_impl_(EVE_SUPPORTS(cpu_),
                                Internal        internal,
                                pattern_t<I...> p,
                                fixed<G>        g,
                                wide<T, N>      x,
                                Ts... xs)
{
  auto xgp = simplify_plain_shuffle(p, g, x, xs...);
  auto r   = canonical_shuffle_adapter_impl_after_simplification(
      internal,
      xgp.p,
      xgp.g,
      xgp.x,
      std::make_index_sequence<std::tuple_size_v<decltype(xgp.x)>> {});
  if constexpr( !matched_shuffle<decltype(r)> ) { return r; }
  else
  {
    using N1 = eve::fixed<sizeof...(I) * G>;
    return bit_cast(r, as<wide<T, N1>> {});
  }
}

}
