//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"
#include "unit/algo/iterator_concept_test.hpp"

#include <eve/views/iota.hpp>

#include <eve/views/convert.hpp>

#include <numeric>

TTS_CASE_TPL("Check iota_with_step_iterator", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;

  T values([](int i, int) { return 5 + i * 2; });
  auto replace = [&](auto v, auto ignore) { return eve::replace_ignored(v, ignore, T{0}); };

  auto f = eve::views::iota_with_step(e_t{5}, e_t{2}).cardinal_cast(eve::lane<T::size()>);
  auto l = f + T::size();
  TTS_EQUAL((l - f), T::size());

  algo_test::iterator_sentinel_test(f, l, values, replace);

  TTS_CONSTEXPR_EXPECT(eve::algo::always_aligned_iterator<decltype(f)>);
};

TTS_CASE_TPL("Check iota_with_step_iterator, conversions", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  auto f = eve::views::iota_with_step(T(0), T(1));

  auto actual_bytes   = eve::views::convert(f, eve::as<std::int8_t>{});
  auto expected_bytes = eve::views::iota_with_step(std::int8_t{0}, std::int8_t{1}).cardinal_cast(eve::lane<eve::expected_cardinal_v<T>>);
  TTS_EQUAL(expected_bytes, actual_bytes);

  auto actual_back = eve::views::convert(actual_bytes, eve::as<T>{});
  TTS_EQUAL(f, actual_back);
};

TTS_CASE_TPL("Check iota", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  std::array<T, 13> expected;
  std::iota(expected.begin(), expected.end(), T{0});

  std::array<T, 13> actual;

  auto iota_r = eve::views::iota(T{0}, 13);
  for (auto f = iota_r.begin(); f != iota_r.end(); ++f) {
    actual[f - iota_r.begin()] = eve::read(f);
  }
  TTS_EQUAL(expected, actual);
};
