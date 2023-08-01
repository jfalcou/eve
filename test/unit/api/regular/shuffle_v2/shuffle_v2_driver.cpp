//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

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

template<typename Selector> struct just_shuffle_test_selector
{
  Selector sel;

  template<typename... Args>
  auto operator()(Args... args) const
  requires(std::invocable<Selector, Args...>)
  {
    auto r = sel(args...);
    if constexpr( !eve::detail::matched_shuffle<decltype(r)> )
    {
      return kumi::tuple {r, eve::index<-1>};
    }
    else return kumi::tuple {r, eve::index<0>};
  }
};

template<typename Selector>
just_shuffle_test_selector(Selector) -> just_shuffle_test_selector<Selector>;

template<typename WrappedShuffleV2> struct just_shuffle_test_
{
  WrappedShuffleV2 sh2;

  template<typename... Args>
  auto operator()(Args... args) const
  requires(std::invocable<WrappedShuffleV2, Args...>)
  {
    return get<0>(sh2(args...));
  }
};

template<typename WrappedShuffleV2>
just_shuffle_test_(WrappedShuffleV2) -> just_shuffle_test_<WrappedShuffleV2>;

template<typename Selector>
constexpr auto
just_shuffle_test(Selector selector)
{
  return just_shuffle_test_ {eve::detail::make_shuffle_v2(just_shuffle_test_selector {selector})};
}

TTS_CASE("shuffle_driver with lambdas")
{
  // using very_wide to not care for fundamental cardinals
  constexpr auto shuffle = just_shuffle_test(
      [](auto p, auto, auto x)
      {
        constexpr auto expected = some_pattern<decltype(x)>;
        TTS_EQUAL(expected, p);
        return x;
      });

  constexpr auto formula = [](int i, int size) { return size - i - 1; };

  shuffle(eve::wide<std::uint16_t> {}, formula);
  shuffle(eve::wide<std::uint8_t> {}, eve::lane<2>, formula);

  if( !eve::supports_simd )
  {
    TTS_PASS(); // not calling the callback
  }
};

TTS_CASE("shuffle_driver propagates not found")
{
  if( !eve::supports_simd )
  {
    // no such thing as "not found on emulated"
    TTS_PASS();
    return;
  }

  // Propagate sfinae
  constexpr auto op = []<typename T, typename N>(auto /*p*/, auto /*g*/, eve::wide<T, N> x, auto...)
  requires(sizeof(T) > 1)
  {
    if constexpr( sizeof(T) == 4 ) return eve::detail::no_matching_shuffle;
    else return x;
  };
  constexpr auto shuffle = just_shuffle_test(op);

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

TTS_CASE_TPL("shuffle_driver, wide logicals", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using abi = typename T::abi_type;
  // emulation has separate logic
  if constexpr( eve::has_emulated_abi_v<T> || !abi::is_wide_logical || T::size() == 1 )
  {
    TTS_PASS();
  }
  else
  {
    std::ptrdiff_t numTimesCalled = 0;
    auto           hasShuffle     = just_shuffle_test(
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

    TTS_EQUAL(numTimesCalled, eve::has_aggregated_abi_v<T> ? 2 : 1);
    TTS_TYPE_IS(decltype(r), eve::logical<T>);
    auto notFound = just_shuffle_test([](auto...) { return eve::detail::no_matching_shuffle; });

    TTS_CONSTEXPR_EXPECT((std::invocable<decltype(hasShuffle), eve::logical<T>, P>));
    TTS_CONSTEXPR_EXPECT(
        (std::invocable<decltype(hasShuffle), eve::logical<T>, eve::logical<T>, P2>));

    TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(notFound), eve::logical<T>, P>));
    TTS_CONSTEXPR_EXPECT_NOT(
        (std::invocable<decltype(notFound), eve::logical<T>, eve::logical<T>, P2>));
    TTS_CONSTEXPR_EXPECT((std::invocable<decltype(hasShuffle), eve::logical<T>, eve::fixed<1>, P>));
    TTS_CONSTEXPR_EXPECT((
        std::invocable<decltype(hasShuffle), eve::logical<T>, eve::logical<T>, eve::fixed<1>, P2>));

    // below to 8 identity logic kicks in
    if constexpr( T::size() >= 8 )
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

TTS_CASE_TPL("Check shuffle_driver, half", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr( T::size() == 1U )
  {
    TTS_PASS();
    return;
  }
  else
  {
    auto half_shuffle = just_shuffle_test([](auto, auto, auto x) { return x.slice(eve::lower_); });

    using half_t = typename T::template rescale<eve::fixed<T::size() / 2>>;

    auto p = eve::fix_pattern<T::size() / 2>([](int i, int) { return i; });

    auto in       = T {0};
    auto shuffled = half_shuffle(in, p);
    TTS_TYPE_IS(decltype(shuffled), half_t);

    using abi = typename T::abi_type;
    if constexpr( abi::is_wide_logical )
    {
      auto l_in       = eve::logical<T> {true};
      auto l_shuffled = half_shuffle(l_in, p);
      TTS_TYPE_IS(decltype(l_shuffled), eve::logical<half_t>);
    }
  }
};

TTS_CASE_TPL("Check shuffle_driver, bundle", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr( !eve::supports_simd || T::size() == 1 )
  {
    // separate test
    TTS_PASS();
    return;
  }
  using e_t  = eve::element_type_t<T>;
  using s_t  = kumi::tuple<std::int8_t, e_t, double>;
  using w_t  = eve::wide<s_t, eve::fixed<T::size()>>;
  using ww_t = eve::wide<kumi::tuple<e_t, s_t>, eve::fixed<T::size()>>;

  auto shuffle = just_shuffle_test(
      []<std::ptrdiff_t... i>(eve::pattern_t<i...>, eve::fixed<1>, auto x, auto...)
      {
        TTS_CONSTEXPR_EXPECT(eve::plain_simd_value<decltype(x)>);
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
    TTS_TYPE_IS(decltype(r), w_t);

    auto r1 = shuffle(w_t {}, w_t {}, P2 {});
    TTS_TYPE_IS(decltype(r1), w_t);

    auto r2 = shuffle(ww_t {}, P {});
    TTS_TYPE_IS(decltype(r2), ww_t);
  }
};

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

TTS_CASE_TPL("Check simplifcation is used", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  // previous tests is enough
  if constexpr( !eve::supports_simd )
  {
    TTS_PASS();
    return;
  }

  auto shuffle = just_shuffle_test(
      []<typename U, typename N, std::ptrdiff_t G>(
          auto, eve::fixed<G>, eve::wide<U, N> x, std::same_as<eve::wide<U, N>> auto...)
      {
        TTS_CONSTEXPR_EXPECT(std::unsigned_integral<U>);
        if constexpr( T::size() > G )
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


// Need a template somewhere for the if constexpr to work
TTS_CASE_TPL("arm-v7, emulate double", tts::types<double>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::current_api != eve::neon )
  {
    TTS_PASS();
    return;
  }
  else
  {
    auto shuffle = eve::detail::make_shuffle_v2([] { TTS_FAIL("should not be reached"); });
    eve::wide<T> x {1, 2};
    auto [shuffled, l] = shuffle(x, [](int i, int size) { return size - i - 1; });
    TTS_EQUAL(l(), 0);
    TTS_EQUAL(shuffled, (eve::wide<T> {2, 1}));
  }
};

// There are more tests in shuffle_v2_driver_integration -
// they are split out for compilation speed.

} // namespace
