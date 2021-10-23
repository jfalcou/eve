//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/views/iota_scaled.hpp>

#include "iterator_concept_test.hpp"

#include <numeric>

EVE_TEST_TYPES("Check iota_scaled_iterator", algo_test::selected_types)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;

  T values([](int i, int) { return 5 + i * 2; });
  auto replace = [&](auto v, auto ignore) { return eve::replace_ignored(v, ignore, T{0}); };

  auto f = eve::algo::views::iota_scaled(e_t{5}, e_t{2}).cardinal_cast(eve::lane<T::size()>);
  auto l = f + T::size();
  TTS_EQUAL((l - f), T::size());

  algo_test::iterator_sentinel_test(f, l, values, replace);

  TTS_CONSTEXPR_EXPECT(eve::algo::always_aligned_iterator<decltype(f)>);
};

EVE_TEST_TYPES("Check iota_scaled_iterator, conversions", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  auto f = eve::algo::views::iota_scaled(T(0), T(1));

  auto actual_bytes   = eve::algo::views::convert(f, eve::as<std::int8_t>{});
  auto expected_bytes = eve::algo::views::iota_scaled(std::int8_t{0}, std::int8_t{1}).cardinal_cast(eve::lane<eve::expected_cardinal_v<T>>);
  TTS_EQUAL(expected_bytes, actual_bytes);

  auto actual_back = eve::algo::views::convert(actual_bytes, eve::as<T>{});
  TTS_EQUAL(f, actual_back);
};

EVE_TEST_TYPES("Check iota", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  std::array<T, 13> expected;
  std::iota(expected.begin(), expected.end(), T{0});

  std::array<T, 13> actual;

  auto iota_r = eve::algo::views::iota(T{0}, 13);
  for (auto f = iota_r.begin(); f != iota_r.end(); ++f) {
    actual[f - iota_r.begin()] = eve::read(f);
  }
  TTS_EQUAL(expected, actual);
};
