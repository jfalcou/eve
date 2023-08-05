//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

template<typename T, std::ptrdiff_t G, typename PGen>
constexpr auto
pad_pattern_with_we(PGen)
{
  constexpr std::ptrdiff_t f_n = eve::fundamental_cardinal_v<eve::element_type_t<T>>;

  if constexpr( T::size() >= f_n ) { return eve::fix_pattern<T::size() / G>(PGen {}); }
  else
  {
    return eve::fix_pattern<f_n / G>(
        [](int i, int)
        {
          if( i >= T::size() / G ) return eve::we_;
          else return PGen {}(i);
        });
  }
}

template<typename T0,
         std::ptrdiff_t G0,
         typename T1,
         std::ptrdiff_t G1,
         typename P0Gen,
         typename P1Gen>
void
simplify_test(P0Gen, P1Gen)
{
  constexpr auto p0 = eve::fix_pattern<T0::size() / G0>(P0Gen {});
  constexpr auto p1 = pad_pattern_with_we<T1, G1>(P1Gen {});
  {
    auto [x_, g_, p_] = eve::detail::simplify_plain_shuffle(p0, eve::lane<G0>, kumi::tuple<T0> {});

    TTS_TYPE_IS(decltype(x_), kumi::tuple<T1>);
    TTS_CONSTEXPR_EQUAL(decltype(g_)::value, G1);
    TTS_EQUAL(p_, p1) << "T0::size(): " << T0::size() << " G: " << G0 << " p0: " << p0;
  }
}

template<typename T0,
         std::ptrdiff_t G0,
         typename T1,
         std::ptrdiff_t G1,
         typename P0Gen,
         typename P1Gen>
void
simplify2_test(P0Gen, P1Gen)
{
  constexpr auto p0 = eve::fix_pattern<T0::size() / G0>(P0Gen {});
  constexpr auto p1 = pad_pattern_with_we<T1, G1>(P1Gen {});
  {
    auto [x_, g_, p_] =
        eve::detail::simplify_plain_shuffle(p0, eve::lane<G0>, kumi::tuple<T0, T0> {});

    TTS_TYPE_IS(decltype(x_), (kumi::tuple<T1, T1>));
    TTS_CONSTEXPR_EQUAL(decltype(g_)::value, G1);
    TTS_EQUAL(p_, p1) << "p0: " << p0 << " T0::size() " << T0::size() << " G0: " << G0;
  }
}

template<typename T0, std::ptrdiff_t G0, typename T1, std::ptrdiff_t G1>
void
simplify_test()
{
  auto p = [](int i, int size) { return size - i - 1; };
  simplify_test<T0, G0, T1, G1>(p, p);

  auto p2 = [](int i, int) { return i + 1; };
  simplify2_test<T0, G0, T1, G1>(p2, p2);
}

TTS_CASE("Check simplification, types")
{
  if constexpr( !eve::supports_simd )
  {
    TTS_PASS();
    return;
  }

  simplify_test<eve::wide<std::uint8_t>, 2, eve::wide<std::uint16_t>, 1>();
  simplify_test<eve::wide<std::int8_t>, 4, eve::wide<std::uint32_t>, 1>();
  simplify_test<eve::wide<std::uint8_t>, 4, eve::wide<std::uint32_t>, 1>();
  simplify_test<eve::wide<std::int16_t>, 4, eve::wide<std::uint64_t>, 1>();
  simplify_test<eve::wide<std::uint16_t>, 4, eve::wide<std::uint64_t>, 1>();
  simplify_test<eve::wide<std::int8_t>, 1, eve::wide<std::uint8_t>, 1>();
  simplify_test<eve::wide<std::int16_t>, 1, eve::wide<std::uint16_t>, 1>();
  simplify_test<eve::wide<std::uint16_t>, 1, eve::wide<std::uint16_t>, 1>();

  simplify_test<eve::wide<float, eve::fixed<16>>, 1, eve::wide<std::uint32_t, eve::fixed<16>>, 1>();
  simplify_test<eve::wide<float, eve::fixed<16>>, 2, eve::wide<std::uint64_t, eve::fixed<8>>, 1>();
  simplify_test<eve::wide<double, eve::fixed<8>>, 2, eve::wide<std::uint64_t, eve::fixed<8>>, 2>();

  if constexpr( !eve::abi_t<std::int8_t, eve::fixed<1>>::is_wide_logical )
  {
    simplify_test<eve::logical<eve::wide<std::uint8_t>>,
                  2,
                  eve::logical<eve::wide<std::uint8_t>>,
                  2>();
    simplify_test<eve::logical<eve::wide<std::int8_t>>,
                  4,
                  eve::logical<eve::wide<std::uint8_t>>,
                  4>();
    simplify_test<eve::logical<eve::wide<std::int16_t>>,
                  4,
                  eve::logical<eve::wide<std::uint16_t>>,
                  4>();

    simplify_test<eve::logical<eve::wide<float, eve::fixed<16>>>,
                  2,
                  eve::logical<eve::wide<std::uint32_t, eve::fixed<16>>>,
                  2>();
  }
};

template<typename T, typename N>
void
simplify_test_pad_to_fundamental()
{
  auto p0 = [](int i, int size) { return size - i - 1; };
  auto p1 = [](int i, int)
  {
    if( i < N::value ) return N::value - i - 1;
    else return eve::we_;
  };
  simplify_test<eve::wide<T, N>, 1, eve::wide<T, eve::fundamental_cardinal_t<T>>, 1>(p0, p1);

  if constexpr( !eve::abi_t<std::int8_t, eve::fixed<1>>::is_wide_logical )
  {
    simplify_test<eve::logical<eve::wide<T, N>>,
                  1,
                  eve::logical<eve::wide<T, eve::fundamental_cardinal_t<T>>>,
                  1>(p0, p1);
  }

  if( N::value == 1 ) return;

  auto p0x2 = [](int i, int size)
  {
    if( i % 2 == 0 ) return i;
    return i + size;
  };

  auto p1x2 = [](int i, int size)
  {
    if( i >= N::value ) return (int)eve::we_;
    if( i % 2 == 0 ) return i;
    else return i + size;
  };

  simplify2_test<eve::wide<T, N>, 1, eve::wide<T, eve::fundamental_cardinal_t<T>>, 1>(p0x2, p1x2);

  if constexpr( !eve::abi_t<std::int8_t, eve::fixed<1>>::is_wide_logical )
  {
    simplify2_test<eve::logical<eve::wide<T, N>>,
                   1,
                   eve::logical<eve::wide<T, eve::fundamental_cardinal_t<T>>>,
                   1>(p0x2, p1x2);
  }
}

TTS_CASE("Check simplification, pad to fundamental")
{
  if constexpr( !eve::supports_simd )
  {
    TTS_PASS();
    return;
  }
  else
  {
    // simplify_test_pad_to_fundamental<std::uint8_t, eve::fixed<1>>();
    simplify_test_pad_to_fundamental<std::uint8_t, eve::fixed<2>>();
    simplify_test_pad_to_fundamental<std::uint16_t, eve::fixed<2>>();
    simplify_test_pad_to_fundamental<std::uint32_t, eve::fixed<2>>();
  }
};

template<std::ptrdiff_t... I>
using upscaled_pattern = decltype(eve::detail::upscale_pattern(eve::pattern<I...>));

TTS_CASE("Check upscale_pattern")
{
  TTS_TYPE_IS((eve::pattern_t<0>), (upscaled_pattern<0>));
  TTS_TYPE_IS((eve::pattern_t<0>), (upscaled_pattern<0, 1>));
  TTS_TYPE_IS((eve::pattern_t<0>), (upscaled_pattern<0, eve::we_>));
  TTS_TYPE_IS((eve::pattern_t<eve::na_>), (upscaled_pattern<eve::na_, eve::we_>));
  TTS_TYPE_IS((eve::pattern_t<eve::na_>), (upscaled_pattern<eve::we_, eve::na_>));
  TTS_TYPE_IS((eve::pattern_t<eve::we_>), (upscaled_pattern<eve::we_, eve::we_>));

  // NOTE: upscale only works one level at a time.
  TTS_TYPE_IS((eve::pattern_t<0, 1>), (upscaled_pattern<0, 1, 2, 3>));
  TTS_TYPE_IS((eve::pattern_t<0, 0>), (upscaled_pattern<0, 1, 0, 1>));
  TTS_TYPE_IS((eve::pattern_t<1, 1>), (upscaled_pattern<2, 3, 2, 3>));

  TTS_TYPE_IS((eve::pattern_t<3, 2, 2, 3>), (upscaled_pattern<3, 2, 2, 3>));
  TTS_TYPE_IS((eve::pattern_t<0, 1, 1, 2>), (upscaled_pattern<0, 1, 1, 2>));
  TTS_TYPE_IS((eve::pattern_t<0, 2, 2, 3>), (upscaled_pattern<0, 2, 2, 3>));
};

TTS_CASE("Check simplification, pad pattern to fundamental and upscale")
{
  if constexpr( !eve::supports_simd )
  {
    TTS_PASS();
    return;
  }
  else
  {
    using u8xN  = eve::wide<std::uint8_t, eve::fundamental_cardinal_t<std::uint8_t>>;
    using u64xN = eve::wide<std::uint64_t, eve::fundamental_cardinal_t<std::uint64_t>>;

    auto [x, g, p] =
        eve::detail::simplify_plain_shuffle(eve::pattern<0>, eve::lane<1>, kumi::tuple<u8xN> {});
    TTS_TYPE_IS(decltype(x), kumi::tuple<u64xN>);
    TTS_EQUAL(g(), u64xN::size());
    TTS_EQUAL(p, eve::pattern<0>);
  }
};

TTS_CASE("Check simplification, upscale")
{
  if constexpr( !eve::supports_simd )
  {
    TTS_PASS();
    return;
  }
  else
  {
    using up_wide =
        std::conditional_t<eve::supports_simd, eve::wide<std::uint16_t>, eve::wide<std::uint8_t>>;

    simplify_test<eve::wide<std::uint8_t>, 1, up_wide, eve::supports_simd ? 1 : 2>(
        [](int i, int size) -> std::ptrdiff_t
        {
          int group_i  = (size - i - 1) / 2;
          int within_i = i % 2;
          if( i == 3 ) return eve::we_;
          return group_i * 2 + within_i;
        },
        [](int i, int size) { return size - i - 1; });
  }
};

TTS_CASE("Check simplification, 2 register")
{
  if constexpr( !eve::supports_simd )
  {
    TTS_PASS();
    return;
  }
  else
  {
    using T = eve::wide<std::uint64_t, eve::fixed<8>>;

    // pick lexicographical min
    {
      // 0 1 2 3 | 4 5 6 7
      constexpr auto p0 = eve::pattern<eve::we_, 5, 1, 2>;
      constexpr auto p1 = eve::pattern<eve::we_, 1, 5, 6>;
      auto [x_, g_, p_] =
          eve::detail::simplify_plain_shuffle(p0, eve::lane<2>, kumi::tuple<T, T> {});

      TTS_TYPE_IS(decltype(x_), (kumi::tuple<T, T>));
      TTS_EQUAL(p_, p1);
    }
  }
};
