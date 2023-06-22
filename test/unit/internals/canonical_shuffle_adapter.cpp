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

template<typename T, std::ptrdiff_t G = 1> using some_p_t = decltype(some_pattern<T, G>);

TTS_CASE("Canonical shuffle propagates not found")
{
  // Propagate sfinae
  constexpr auto op = []<typename T, typename N>(eve::wide<T, N> x, auto...)
  requires(sizeof(T) > 1)
  {
    if constexpr( std::same_as<T, float> ) return eve::detail::no_matching_shuffle;
    else return x;
  };
  constexpr auto shuffle = eve::detail::as_canonical_shuffle(op);

  TTS_CONSTEXPR_EXPECT((std::invocable<decltype(shuffle),
                                       eve::wide<std::int16_t>,
                                       some_p_t<eve::wide<std::int16_t>>>));
  TTS_CONSTEXPR_EXPECT_NOT(
      (std::invocable<decltype(shuffle), eve::wide<float>, some_p_t<eve::wide<float>>>));
  TTS_CONSTEXPR_EXPECT_NOT(
      (std::invocable<decltype(shuffle), eve::wide<char>, some_p_t<eve::wide<char>>>));
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
        [&numTimesCalled]<std::ptrdiff_t... i>(auto x, eve::fixed<1>, eve::pattern_t<i...>)
        {
          ++numTimesCalled;
          return x;
        });
    using P = some_p_t<T>;
    auto r  = hasShuffle(eve::logical<T> {true}, P {});

    TTS_EQUAL(numTimesCalled, 1);
    TTS_TYPE_IS(decltype(r), eve::logical<T>);

    auto notFound =
        eve::detail::as_canonical_shuffle([](auto...) { return eve::detail::no_matching_shuffle; });

    TTS_CONSTEXPR_EXPECT((std::invocable<decltype(hasShuffle), eve::logical<T>, P>));
    TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(notFound), eve::logical<T>, P>));
    TTS_CONSTEXPR_EXPECT((std::invocable<decltype(hasShuffle), eve::logical<T>, eve::fixed<1>, P>));

    if constexpr( T::size() >= 2 )
    {
      TTS_CONSTEXPR_EXPECT_NOT(
          (std::invocable<decltype(notFound), eve::logical<T>, eve::fixed<2>, P>));
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
      [&numTimesCalled]<std::ptrdiff_t... i>(auto x, eve::fixed<1>, eve::pattern_t<i...>)
      {
        TTS_CONSTEXPR_EXPECT(eve::plain_simd_value<decltype(x)>);
        ++numTimesCalled;
        if constexpr( sizeof(e_t) == 2 ) return eve::detail::no_matching_shuffle;
        else return x;
      });
  using P = some_p_t<w_t>;

  if constexpr( sizeof(e_t) == 2 )
  {
    TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(shuffle), w_t, P>));
    TTS_CONSTEXPR_EXPECT_NOT((std::invocable<decltype(shuffle), ww_t, P>));
  }
  else
  {
    auto r = shuffle(w_t {}, P {});
    TTS_EQUAL(numTimesCalled, 3);
    TTS_TYPE_IS(decltype(r), w_t);

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

  auto [x_, g_, p_] = eve::detail::simplify_plain_shuffle(T0 {}, eve::lane<G0>, p0);

  TTS_TYPE_IS(decltype(x_), T1);
  TTS_CONSTEXPR_EQUAL(decltype(g_)::value, G1);
  TTS_EQUAL(p_, p1);
}

template<typename T0, std::ptrdiff_t G0, typename T1, std::ptrdiff_t G1>
void
simplify_test()
{
  auto p = [](int i, int size) { return size - i - 1; };
  simplify_test<T0, G0, T1, G1>(p, p);
}

TTS_CASE("Check simplification, types")
{
  if constexpr( !eve::supports_simd )
  {
    TTS_PASS();
    return;
  }

  simplify_test<eve::wide<std::uint8_t>, 2, eve::wide<std::uint16_t>, 1>();

  if constexpr( eve::current_api == eve::avx )
  {
    simplify_test<eve::wide<std::int8_t>, 4, eve::wide<float>, 1>();
    simplify_test<eve::wide<std::uint8_t>, 4, eve::wide<float>, 1>();
    simplify_test<eve::wide<std::int16_t>, 4, eve::wide<double>, 1>();
    simplify_test<eve::wide<std::uint16_t>, 4, eve::wide<double>, 1>();
    simplify_test<eve::wide<float>, 2, eve::wide<double>, 1>();
    simplify_test<eve::wide<std::uint16_t, eve::fixed<8>>,
                  4,
                  eve::wide<std::uint64_t, eve::fixed<2>>,
                  1>();
  }
  else
  {
    simplify_test<eve::wide<std::int8_t>, 4, eve::wide<std::uint32_t>, 1>();
    simplify_test<eve::wide<std::uint8_t>, 4, eve::wide<std::uint32_t>, 1>();
    simplify_test<eve::wide<std::int16_t>, 4, eve::wide<std::uint64_t>, 1>();
    simplify_test<eve::wide<std::uint16_t>, 4, eve::wide<std::uint64_t>, 1>();
    if constexpr( eve::current_api == eve::neon )
    {
      simplify_test<eve::wide<float>, 2, eve::wide<std::uint64_t>, 1>();
    }
    else
    {
      simplify_test<eve::wide<float>, 2, eve::wide<double>, 1>();
    }
  }

  simplify_test<eve::wide<std::int8_t>, 1, eve::wide<std::uint8_t>, 1>();
  simplify_test<eve::wide<std::int16_t>, 1, eve::wide<std::uint16_t>, 1>();
  simplify_test<eve::wide<std::int16_t>, 1, eve::wide<std::uint16_t>, 1>();

  using very_wide = eve::wide<double, eve::fixed<8>>;
  simplify_test<very_wide, 2, very_wide, 2>();
};


template<typename T, typename N>
void
simplify_test_pad_to_fundamental()
{
  auto p0 = [](int i, int size) { return size - i; };
  auto p1 = [](int i, int)
  {
    if( i < N::value ) return N::value - i;
    else return eve::we_;
  };
  simplify_test<eve::wide<T, N>, 1, eve::wide<T, eve::fundamental_cardinal_t<T>>, 1>(p0, p1);
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
  simplify_test_pad_to_fundamental<float, eve::fixed<2>>();
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
  simplify_test<eve::wide<double>, 1, eve::wide<double>, eve::expected_cardinal_v<double>>(
      [](int i, int) { return i; }, [](int i, int) { return i; });

  using up_wide = std::conditional_t<
    eve::supports_simd,
    eve::wide<std::uint16_t>,
    eve::wide<std::uint8_t>
  >;

  simplify_test<eve::wide<std::uint8_t>,
                1,
                up_wide,
                eve::supports_simd ? 1 : 2>(
      [](int i, int size) -> std::ptrdiff_t
      {
        int group_i  = (size - i - 1) / 2;
        int within_i = i % 2;
        if( i == 3 ) return eve::we_;
        return group_i * 2 + within_i;
      },
      [](int i, int size) { return size - i - 1; });
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

  auto shuffle = eve::detail::as_canonical_shuffle(
      []<typename U, typename N, std::ptrdiff_t G>(eve::wide<U, N> x, eve::fixed<G>, auto)
      {
        TTS_CONSTEXPR_EXPECT(std::unsigned_integral<U> || std::floating_point<U>);
        if constexpr( T::size() > 1 )
        {
          int expectedG = sizeof(eve::element_type_t<T>) == 8 ? 2 : 1;
          TTS_EQUAL(expectedG, G);
        }

        return x;
      });

  constexpr int G = T::size() == 1 ? 1 : 2;
  shuffle(T {}, eve::lane<G>, some_pattern<T, G>);
};

} // namespace
