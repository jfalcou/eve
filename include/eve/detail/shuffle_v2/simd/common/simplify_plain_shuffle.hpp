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

template<typename U, typename... Ts>
EVE_FORCEINLINE auto
bit_cast_tuple(kumi::tuple<Ts...> xs, eve::as<U>)
{
  return kumi::map([](auto x) { return eve::bit_cast(x, eve::as<U> {}); }, xs);
};

template<typename G, typename P, typename... Ts> struct simplified_pattern
{
  kumi::tuple<Ts...> x;
  G                  g;
  P                  p;
};

template<typename G, typename P, typename... Ts>
simplified_pattern(kumi::tuple<Ts...>, G, P) -> simplified_pattern<G, P, Ts...>;

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
simplify_plain_up_the_type(pattern_t<I...> p, eve::fixed<G> g, kumi::tuple<T, Ts...> xs)
{
  // non wide logicals
  if constexpr( eve::logical_value<T> )
  {
    if constexpr( !eve::unsigned_value<typename T::mask_type> )
    {
      using e_t = eve::element_type_t<typename T::mask_type>;
      using N   = eve::fixed<T::size()>;

      using u_t = typename T::template rebind<detail::make_integer_t<sizeof(e_t), unsigned>, N>;
      return simplify_plain_up_the_type(p, g, bit_cast_tuple(xs, as<u_t> {}));
    }
    else return simplified_pattern {xs, g, p};
  }
  else if constexpr( !std::unsigned_integral<eve::element_type_t<T>> )
  {
    using e_t = eve::element_type_t<T>;
    using N   = eve::fixed<T::size()>;
    using u_t = eve::wide<detail::make_integer_t<sizeof(e_t), unsigned>, N>;
    return simplify_plain_up_the_type(p, g, bit_cast_tuple(xs, as<u_t> {}));
  }
  else if constexpr( G >= 2 && sizeof(eve::element_type_t<T>) < 8 )
  {
    using e_t  = eve::element_type_t<T>;
    using N    = eve::fixed<T::size() / 2>;
    using up_t = eve::wide<detail::make_integer_t<sizeof(e_t) * 2, unsigned>, N>;
    return simplify_plain_up_the_type(p, eve::lane<G / 2>, bit_cast_tuple(xs, as<up_t> {}));
  }
  else { return simplified_pattern {xs, g, p}; }
}

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
simplify_plain_swap_input_wides(pattern_t<I...> p, eve::fixed<G> g, kumi::tuple<T, Ts...> xs)
{
  constexpr std::array idxs {I...};

  if constexpr( sizeof...(Ts) != 1 ) return simplify_plain_up_the_type(p, g, xs);
  else if constexpr( constexpr auto swapped = idxm::swap_xy(idxs, T::size() / G); swapped < idxs )
  {
    return simplify_plain_up_the_type(idxm::to_pattern<swapped>(), g, kumi::reverse(xs));
  }
  else return simplify_plain_up_the_type(p, g, xs);
}

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename... Ts>
EVE_FORCEINLINE auto
simplify_plain_shuffle_upscale_pattern(pattern_t<I...>, eve::fixed<G> g, kumi::tuple<Ts...> xs)
{
  constexpr auto p  = pattern<I...>;
  constexpr auto up = upscale_pattern(p);

  if constexpr( up != p ) return simplify_plain_shuffle_upscale_pattern(up, eve::lane<G * 2>, xs);
  else return simplify_plain_swap_input_wides(p, g, xs);
}

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
EVE_FORCEINLINE auto
simplify_plain_pad_fundamental(pattern_t<I...> p, eve::fixed<G> g, kumi::tuple<T, Ts...> xs)
{
  constexpr std::ptrdiff_t f_n = fundamental_cardinal_v<eve::element_type_t<T>>;
  if constexpr( f_n > T::size() || (f_n / G) > pattern_t<I...>::size() )
  {
    constexpr auto p2_arr =
        idxm::fix_indexes_to_fundamental<f_n / G>(std::array {I...}, T::size() / G);
    constexpr auto p2 = idxm::to_pattern<p2_arr>();

    using N1 = fixed<std::max(T::size(), f_n)>;
    using T1 = typename T::template rescale<N1>;
    return simplify_plain_shuffle_upscale_pattern(p2, g, bit_cast_tuple(xs, as<T1> {}));
  }
  else return simplify_plain_shuffle_upscale_pattern(p, g, xs);
}

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename... Ts>
EVE_FORCEINLINE auto
simplify_plain_shuffle_(EVE_SUPPORTS(cpu_),
                        pattern_t<I...>    p,
                        eve::fixed<G>      g,
                        kumi::tuple<Ts...> xs)
{
  return simplify_plain_pad_fundamental(p, g, xs);
}

}
