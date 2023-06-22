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

template<typename Internal, simd_value T, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
canonical_shuffle_adapter_impl_(EVE_SUPPORTS(cpu_), Internal, T, fixed<G>, pattern_t<I...>)
requires(G > T::size())
{
  // NOTE: we catch this specifically because:
  //  * sfinae failure here is most likely an error that the user will just miss.
  //  * It is very easy for the user to add this requirement somewhere at the top
  static_assert(G <= T::size(), "Group sized passed is bigger than a register, very likely a bug");
}

template<typename Internal, typename T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
canonical_shuffle_adapter_impl_(EVE_SUPPORTS(cpu_),
                                Internal                 internal,
                                logical<eve::wide<T, N>> x,
                                fixed<G>                 g,
                                pattern_t<I...>          p)
requires(abi_t<T, N>::is_wide_logical) && (G <= N::value)
{
  auto shuffle_bits = canonical_shuffle_adapter_impl(internal, x.mask(), g, p);
  if constexpr( std::same_as<decltype(shuffle_bits), no_matching_shuffle_t> )
  {
    return no_matching_shuffle;
  }
  else { return bit_cast(shuffle_bits, as(x)); }
}

template<typename Internal, std::ptrdiff_t G, std::ptrdiff_t... I> struct BundleLambda
{
  Internal internal;

  EVE_FORCEINLINE
  auto operator()(auto x) const noexcept
  {
    return canonical_shuffle_adapter_impl(internal, x, lane<G>, pattern<I...>);
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
         std::ptrdiff_t... I>
EVE_FORCEINLINE auto
canonical_shuffle_adapter_impl_(EVE_SUPPORTS(cpu_),
                                Internal   internal,
                                wide<T, N> x,
                                fixed<G>,
                                pattern_t<I...>)
requires(G <= N::value)
{
  auto each_part = kumi::map(BundleLambda<Internal, G, I...> {internal}, x);

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
  else
  {
    constexpr auto res_arr = *attempt;
    return [&]<std::size_t... for_>(std::index_sequence<for_...>)
    { return pattern<res_arr[for_]...>; }(std::make_index_sequence<attempt->size()> {});
  }
}

template<typename T, typename G, typename P> struct simplified_pattern
{
  T x;
  G g;
  P p;
};

template<typename T, typename G, typename P>
simplified_pattern(T, G, P) -> simplified_pattern<T, G, P>;

template<plain_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
simplify_plain_shuffle1(eve::wide<T, N> x, eve::fixed<G> g, pattern_t<I...> p)
{
  // On an emulation bitcasting types won't be helpful for anything.
  if constexpr( !supports_simd ) { return simplified_pattern {x, g, p}; }
  else if constexpr( G >= 2 && sizeof(T) < 8 )
  {
    if constexpr ( sizeof(T) == 4 && current_api == neon)
    {
      using up_t = std::uint64_t;
      const auto up = bit_cast(x, as<wide<up_t, typename N::split_type>>());
      return simplify_plain_shuffle1(up, eve::lane<G / 2>, p);
    }
    else
    {
      using up_t    = upgrade_t<T>;
      const auto up = bit_cast(x, as<wide<up_t, typename N::split_type>>());
      return simplify_plain_shuffle1(up, eve::lane<G / 2>, p);
    }
  }
  else if constexpr( std::signed_integral<T> )
  {
    using u_t = std::make_unsigned_t<T>;
    auto cast = bit_cast(x, as<wide<u_t, N>>());
    return simplify_plain_shuffle1(cast, g, p);
  }
  else if constexpr( current_api == avx && std::same_as<T, std::uint32_t> && N::value == 8 )
  {
    auto cast = bit_cast(x, as<wide<float, N>> {});
    return simplify_plain_shuffle1(cast, g, p);
  }
  else if constexpr( current_api == avx && std::same_as<T, std::uint64_t> && N::value == 4 )
  {
    auto cast = bit_cast(x, as<wide<double, N>> {});
    return simplify_plain_shuffle1(cast, g, p);
  }
  else if constexpr( fundamental_cardinal_v<T> > N::value )
  {
    auto cast         = bit_cast(x, as<wide<T, fundamental_cardinal_t<T>>> {});
    auto next_pattern = []<std::size_t... i>(std::index_sequence<i...>) {
      return pattern_t<I..., ((void)i, we_)...> {};
    }(std::make_index_sequence<fundamental_cardinal_v<T> - sizeof...(I)> {});
    return simplify_plain_shuffle1(cast, g, next_pattern);
  }
  else { return simplified_pattern {x, g, p}; }
}

template<plain_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
simplify_plain_shuffle(eve::wide<T, N> x, eve::fixed<G> g, pattern_t<I...>)
{
  constexpr auto p  = pattern<I...>;
  constexpr auto up = upscale_pattern(p);

  if constexpr( up != p ) return simplify_plain_shuffle(x, eve::lane<G * 2>, up);
  else return simplify_plain_shuffle1(x, g, p);
}

template<typename Internal, plain_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
canonical_shuffle_adapter_impl_(EVE_SUPPORTS(cpu_),
                                Internal        internal,
                                wide<T, N>      x,
                                fixed<G>        g,
                                pattern_t<I...> p)
requires(G <= N::value)
{
  auto [_x, _g, _p] = simplify_plain_shuffle(x, g, p);

  if constexpr( !std::invocable<Internal, decltype(_x), decltype(_g), decltype(_p)> )
  {
    return no_matching_shuffle;
  }
  else
  {
    auto r = internal(_x, _g, _p);
    if constexpr( std::same_as<decltype(r), no_matching_shuffle_t> ) { return r; }
    else { return bit_cast(r, as<wide<T, N>> {}); }
  }
}

}
