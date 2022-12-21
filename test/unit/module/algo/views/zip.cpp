//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include <vector>

TTS_CASE("zip iterators")
{
  std::vector<int>         v{1, 2, 3, 4};
  std::vector<std::int8_t> c{'a', 'b', 'c', 'd'};

  eve::views::zip_iterator f = eve::views::zip(v.begin(), c.begin());
  TTS_EQUAL(v.begin(), get<0>(f));
  TTS_EQUAL(c.begin(), get<1>(f));

  eve::views::zip_iterator l = eve::views::zip(v.end(), c.end());
  TTS_EQUAL(v.end(), get<0>(l));
  TTS_EQUAL(c.end(), get<1>(l));

  auto rng_test = [&](auto rng) {
    TTS_EQUAL(rng.begin(), f);
    TTS_TYPE_IS(decltype(rng.begin()), decltype(f));
    TTS_EQUAL(rng.end(), l);
    TTS_TYPE_IS(decltype(rng.end()), decltype(l));
  };

  rng_test(eve::views::zip(v, c));
  rng_test(eve::views::zip(v, c.begin()));
  rng_test(eve::views::zip(v.begin(), c));
};

TTS_CASE("zip range, decomposition")
{
  std::vector<int> const   v{1, 2, 3, 4};
  std::vector<std::int8_t> c{'a', 'b', 'c', 'd'};

  auto zipped = eve::views::zip(v, c);
  auto [cref_v, ref_c] = zipped;
  TTS_EQUAL(cref_v.begin(), v.begin());
  TTS_EQUAL(cref_v.end(),   v.end());
  TTS_EQUAL(ref_c.begin(),  c.begin());
  TTS_EQUAL(ref_c.end(),    c.end());
};

TTS_CASE("zip common_type")
{
  std::vector<int> const   v{1, 2, 3, 4};
  std::vector<std::int8_t> c{'a', 'b', 'c', 'd'};

  auto expected = eve::views::zip(v, eve::views::convert(c, eve::as<int>{}));

  auto expected_f = expected.begin();

  {
    auto zipped = eve::views::zip[eve::algo::common_type](v, c);
    TTS_TYPE_IS(decltype(zipped), decltype(expected));

    auto zipped_f = eve::views::zip[eve::algo::common_type](v.begin(), c.begin());
    TTS_EQUAL(zipped_f, expected_f);
  }

  {
    auto zipped = eve::views::zip(v, c)[eve::algo::common_type];
    TTS_TYPE_IS(decltype(zipped), decltype(expected));
  }
};

TTS_CASE("zip common_with_types")
{
  std::vector<int> const   v{1, 2, 3, 4};
  std::vector<std::int8_t> c{'a', 'b', 'c', 'd'};

  auto expected = eve::views::zip(eve::views::convert(v, eve::as<double>{}),
                                  eve::views::convert(c, eve::as<double>{}));

  auto expected_f = expected.begin();

  {
    auto zipped = eve::views::zip[eve::algo::common_with_types<double>](v, c);
    TTS_TYPE_IS(decltype(zipped), decltype(expected));

    auto zipped_f = eve::views::zip[eve::algo::common_with_types<double>](v.begin(), c.begin());
    TTS_EQUAL(zipped_f, expected_f);
  }

  {
    auto zipped = eve::views::zip(v, c)[eve::algo::common_with_types<double>];
    TTS_TYPE_IS(decltype(zipped), decltype(expected));
  }
};

TTS_CASE("zip force_type")
{
  std::vector<int> const   v{1, 2, 3, 4};
  std::vector<std::int8_t> c{'a', 'b', 'c', 'd'};

  auto expected = eve::views::zip(eve::views::convert(v, eve::as<std::int8_t>{}),
                                  eve::views::convert(c, eve::as<std::int8_t>{}));

  auto expected_f = expected.begin();

  {
    auto zipped = eve::views::zip[eve::algo::force_type<std::int8_t>](v, c);
    TTS_TYPE_IS(decltype(zipped), decltype(expected));

    auto zipped_f = eve::views::zip[eve::algo::force_type<std::int8_t>](v.begin(), c.begin());
    TTS_EQUAL(zipped_f, expected_f);
  }

  {
    auto zipped = eve::views::zip(v, c)[eve::algo::force_type<std::int8_t>];
    TTS_TYPE_IS(decltype(zipped), decltype(expected));
  }
};

TTS_CASE("zip_with_iota, should align")
{
  std::array<std::uint32_t, 64> i;
  auto zipped = eve::views::zip(i , eve::views::iota(0));
  auto processed = eve::algo::preprocess_range(eve::algo::traits{}, zipped);
  TTS_CONSTEXPR_EXPECT_NOT(decltype(processed.traits())::contains(eve::algo::no_aligning));
  TTS_CONSTEXPR_EXPECT(eve::algo::unaligned_iterator<decltype(processed.begin())>);
  TTS_CONSTEXPR_EXPECT_NOT(eve::algo::always_aligned_iterator<decltype(processed.begin())>);
};
