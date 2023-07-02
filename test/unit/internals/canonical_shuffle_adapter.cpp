//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/detail/function/canonical_shuffle_adapter.hpp>

namespace
{

template<typename T, std::ptrdiff_t G = 1>
constexpr auto some_pattern =
    eve::fix_pattern<T::size() / G>([](int i, int size) { return size - i - 1; });

template<typename T, std::ptrdiff_t G = 1>
constexpr auto some_pattern2 =
    eve::fix_pattern<T::size() / G>([](int i, int size) { return size * 2 - 2 * i - 1; });

template<typename T, std::ptrdiff_t G = 1> using some_p_t = decltype(some_pattern<T, G>);

template<typename T, std::ptrdiff_t G = 1> using some_p2_t = decltype(some_pattern2<T, G>);

TTS_CASE("Canonical shuffle with lambdas")
{
  // using very_wide to not care for fundamental cardinals
  constexpr auto shuffle = eve::detail::as_canonical_shuffle(
      [](auto p, auto, auto x)
      {
        constexpr auto expected = eve::pattern<7, 6, 5, 4, 3, 2, 1, 0>;
        TTS_EQUAL(expected, p);
        return x;
      });

  constexpr auto formula = [](int i, int size) { return size - i - 1; };

  shuffle(eve::wide<std::uint64_t, eve::fixed<8>> {}, formula);
  shuffle(eve::wide<std::uint32_t, eve::fixed<16>> {}, eve::lane<2>, formula);
};

TTS_CASE("Canonical shuffle propagates not found")
{
  // Propagate sfinae
  constexpr auto op = []<typename T, typename N>(auto /*p*/, auto /*g*/, eve::wide<T, N> x, auto...)
  requires(sizeof(T) > 1)
  {
    if constexpr( sizeof(T) == 4 ) return eve::detail::no_matching_shuffle;
    else return x;
  };
  constexpr auto shuffle = eve::detail::as_canonical_shuffle(op);

  TTS_CONSTEXPR_EXPECT((std::invocable<decltype(shuffle),
                                       eve::wide<std::int16_t>,
                                       some_p_t<eve::wide<std::int16_t>>>));
  TTS_CONSTEXPR_EXPECT((std::invocable<decltype(shuffle),
                                       eve::wide<std::int16_t>,
                                       eve::wide<std::int16_t>,
                                       some_p2_t<eve::wide<std::int16_t>>>));

  TTS_CONSTEXPR_EXPECT_NOT(
      (std::invocable<decltype(shuffle), eve::wide<float>, some_p_t<eve::wide<float>>>));
  TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(shuffle),
                                           eve::wide<float>,
                                           eve::wide<float>,
                                           some_p2_t<eve::wide<float>>>));
  TTS_CONSTEXPR_EXPECT_NOT(
      (std::invocable<decltype(shuffle), eve::wide<char>, some_p_t<eve::wide<char>>>));
  TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(shuffle),
                                           eve::wide<char>,
                                           eve::wide<char>,
                                           some_p2_t<eve::wide<char>>>));
};

TTS_CASE_TPL("Check canonical shuffle, wide logicals", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using abi = typename T::abi_type;
  if constexpr( !abi::is_wide_logical ) { TTS_PASS(); }
  else
  {
    std::ptrdiff_t numTimesCalled = 0;
    auto           hasShuffle     = eve::detail::as_canonical_shuffle(
        [&numTimesCalled]<std::ptrdiff_t... i>(eve::pattern_t<i...>,
                                               eve::fixed<1>,
                                               eve::plain_simd_value auto x,
                                               std::same_as<decltype(x)> auto...)
        {
          ++numTimesCalled;
          return x;
        });
    using P  = some_p_t<T>;
    using P2 = some_p2_t<T>;
    auto r   = hasShuffle(eve::logical<T> {true}, P {});

    TTS_EQUAL(numTimesCalled, 1);
    TTS_TYPE_IS(decltype(r), eve::logical<T>);

    auto notFound =
        eve::detail::as_canonical_shuffle([](auto...) { return eve::detail::no_matching_shuffle; });

    TTS_CONSTEXPR_EXPECT((std::invocable<decltype(hasShuffle), eve::logical<T>, P>));
    TTS_CONSTEXPR_EXPECT(
        (std::invocable<decltype(hasShuffle), eve::logical<T>, eve::logical<T>, P2>));
    TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(notFound), eve::logical<T>, P>));
    TTS_CONSTEXPR_EXPECT_NOT(
        (std::invocable<decltype(notFound), eve::logical<T>, eve::logical<T>, P2>));
    TTS_CONSTEXPR_EXPECT((std::invocable<decltype(hasShuffle), eve::logical<T>, eve::fixed<1>, P>));
    TTS_CONSTEXPR_EXPECT((
        std::invocable<decltype(hasShuffle), eve::logical<T>, eve::logical<T>, eve::fixed<1>, P2>));

    if constexpr( T::size() >= 2 )
    {
      using half_T = eve::wide<eve::element_type_t<T>, eve::fixed<T::size() / 2>>;
      TTS_CONSTEXPR_EXPECT_NOT(
          (std::invocable<decltype(notFound), eve::logical<T>, eve::fixed<2>, some_p_t<half_T>>));
      TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(notFound),
                                               eve::logical<T>,
                                               eve::logical<T>,
                                               eve::fixed<2>,
                                               some_p2_t<half_T>>));
    }
  }
};

TTS_CASE_TPL("Check canonical shuffle, half", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr( T::size() == 1U )
  {
    TTS_PASS();
    return;
  }
  else
  {
    auto half_shuffle =
        eve::detail::as_canonical_shuffle([](auto, auto, auto x) { return x.slice(eve::lower_); });

    using half_t = typename T::template rescale<eve::fixed<T::size() / 2>>;

    auto in       = T {0};
    auto shuffled = half_shuffle(in, some_pattern<half_t>);
    TTS_TYPE_IS(decltype(shuffled), half_t);

    using abi = typename T::abi_type;
    if constexpr( abi::is_wide_logical )
    {
      auto l_in       = eve::logical<T> {true};
      auto l_shuffled = half_shuffle(l_in, some_pattern<half_t>);
      TTS_TYPE_IS(decltype(l_shuffled), eve::logical<half_t>);
    }
  }
};

TTS_CASE_TPL("Check canonical shuffle, bundle", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t  = eve::element_type_t<T>;
  using s_t  = kumi::tuple<std::int8_t, e_t, double>;
  using w_t  = eve::wide<s_t, eve::fixed<T::size()>>;
  using ww_t = eve::wide<kumi::tuple<e_t, s_t>, eve::fixed<T::size()>>;

  std::ptrdiff_t numTimesCalled = 0;
  auto           shuffle        = eve::detail::as_canonical_shuffle(
      [&numTimesCalled]<std::ptrdiff_t... i>(eve::pattern_t<i...>, eve::fixed<1>, auto x, auto...)
      {
        TTS_CONSTEXPR_EXPECT(eve::plain_simd_value<decltype(x)>);
        ++numTimesCalled;
        if constexpr( sizeof(e_t) == 2 ) return eve::detail::no_matching_shuffle;
        else return x;
      });
  using P  = some_p_t<w_t>;
  using P2 = some_p2_t<w_t>;

  if constexpr( sizeof(e_t) == 2 )
  {
    TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(shuffle), w_t, P>));
    TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(shuffle), w_t, w_t, P2>));
    TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(shuffle), ww_t, P>));
  }
  else
  {
    auto r = shuffle(w_t {}, P {});
    TTS_EQUAL(numTimesCalled, 3);
    TTS_TYPE_IS(decltype(r), w_t);

    numTimesCalled = 0;
    auto r1        = shuffle(w_t {}, w_t {}, P2 {});
    TTS_EQUAL(numTimesCalled, 3);
    TTS_TYPE_IS(decltype(r1), w_t);

    numTimesCalled = 0;
    auto r2        = shuffle(ww_t {}, P {});
    TTS_EQUAL(numTimesCalled, 4);
    TTS_TYPE_IS(decltype(r2), ww_t);
  }
};

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
  constexpr auto p1 = eve::fix_pattern<T1::size() / G1>(P1Gen {});
  {
    auto [x_, g_, p_] = eve::detail::simplify_plain_shuffle(p0, eve::lane<G0>, T0 {});

    TTS_TYPE_IS(decltype(x_), kumi::tuple<T1>);
    TTS_CONSTEXPR_EQUAL(decltype(g_)::value, G1);
    TTS_EQUAL(p_, p1);
  }

  {
    // second part is cut out
    auto [x_, g_, p_] = eve::detail::simplify_plain_shuffle(p0, eve::lane<G0>, T0 {}, T0 {});

    TTS_TYPE_IS(decltype(x_), kumi::tuple<T1>)
        << "p0: " << p0 << " T::size(): " << T0::size() << " g: " << G0;
    TTS_CONSTEXPR_EQUAL(decltype(g_)::value, G1);
    TTS_EQUAL(p_, p1);
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
  constexpr auto p1 = eve::fix_pattern<T1::size() / G1>(P1Gen {});
  {
    auto [x_, g_, p_] = eve::detail::simplify_plain_shuffle(p0, eve::lane<G0>, T0 {}, T0 {});

    TTS_TYPE_IS(decltype(x_), (kumi::tuple<T1, T1>));
    TTS_CONSTEXPR_EQUAL(decltype(g_)::value, G1);
    TTS_EQUAL(p_, p1);
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

  if constexpr( eve::current_api != eve::neon )
  {
    simplify_test<eve::wide<double, eve::fixed<8>>,
                  2,
                  eve::wide<std::uint64_t, eve::fixed<8>>,
                  2>();
  }
  else
  {
    simplify_test<eve::wide<double, eve::fixed<8>>, 2, eve::wide<double, eve::fixed<8>>, 2>();
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
}

TTS_CASE("Check simplification, pad to fundamental")
{
  if constexpr( !eve::supports_simd )
  {
    TTS_PASS();
    return;
  }

  simplify_test_pad_to_fundamental<std::uint8_t, eve::fixed<1>>();
  simplify_test_pad_to_fundamental<std::uint8_t, eve::fixed<2>>();
  simplify_test_pad_to_fundamental<std::uint16_t, eve::fixed<2>>();
  simplify_test_pad_to_fundamental<std::uint32_t, eve::fixed<2>>();
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

TTS_CASE("Check simplification, upscale")
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
};

TTS_CASE("Check simplification, 2 register")
{
  using T = eve::wide<std::uint64_t, eve::fixed<8>>;

  // pick lexicographical min
  {
    // 0 1 2 3 | 4 5 6 7
    constexpr auto p0 = eve::pattern<eve::we_, 5, 1, 2>;
    constexpr auto p1 = eve::pattern<eve::we_, 1, 5, 6>;
    auto [x_, g_, p_] = eve::detail::simplify_plain_shuffle(p0, eve::lane<2>, T {}, T {});

    TTS_TYPE_IS(decltype(x_), (kumi::tuple<T, T>));
    TTS_EQUAL(p_, p1);
  }

  // Only one register, low
  {
    constexpr auto p0 = eve::pattern<eve::we_, 0, 2, 1>;
    auto [x_, g_, p_] = eve::detail::simplify_plain_shuffle(p0, eve::lane<2>, T {}, T {});

    TTS_TYPE_IS(decltype(x_), kumi::tuple<T>);
    TTS_EQUAL(p_, p0);
  }

  // Only one register, high
  {
    constexpr auto p0 = eve::pattern<eve::we_, 4, 6, 5>;
    constexpr auto p1 = eve::pattern<eve::we_, 0, 2, 1>;
    auto [x_, g_, p_] = eve::detail::simplify_plain_shuffle(p0, eve::lane<2>, T {}, T {});

    TTS_TYPE_IS(decltype(x_), kumi::tuple<T>);
    TTS_EQUAL(p_, p1);
  }

  // Only one register, 1 element, low
  {
    constexpr auto p0 = eve::pattern<0>;
    auto [x_, g_, p_] = eve::detail::simplify_plain_shuffle(p0, eve::lane<8>, T {}, T {});
    TTS_TYPE_IS(decltype(x_), kumi::tuple<T>);
    TTS_EQUAL(p_, p0);
  }
  // Only one register, 1 element, high
  {
    constexpr auto p0 = eve::pattern<1>;
    constexpr auto p1 = eve::pattern<0>;
    auto [x_, g_, p_] = eve::detail::simplify_plain_shuffle(p0, eve::lane<8>, T {}, T {});
    TTS_TYPE_IS(decltype(x_), kumi::tuple<T>);
    TTS_EQUAL(p_, p1);
  }
};

TTS_CASE_TPL("Check simplifcation is used", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  // previous tests is enough
  if constexpr( eve::has_emulated_abi_v<T> )
  {
    TTS_PASS();
    return;
  }

  auto shuffle = eve::detail::as_canonical_shuffle(
      []<typename U, typename N, std::ptrdiff_t G>(
          auto, eve::fixed<G>, eve::wide<U, N> x, std::same_as<eve::wide<U, N>> auto...)
      {
        TTS_CONSTEXPR_EXPECT(std::unsigned_integral<U>);
        if constexpr( T::size() > 1 )
        {
          int expectedG = sizeof(eve::element_type_t<T>) == 8 ? 2 : 1;
          TTS_EQUAL(expectedG, G);
        }

        return x;
      });

  constexpr int G = T::size() == 1 ? 1 : 2;
  shuffle(T {}, eve::lane<G>, some_pattern<T, G>);
  shuffle(T {}, T {}, eve::lane<G>, some_pattern2<T, G>);
};

} // namespace
