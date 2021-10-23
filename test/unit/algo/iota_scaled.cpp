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

EVE_TEST_TYPES("Check iota_scaled_iterator", algo_test::selected_types)
<typename T>(eve::as<T>)
{
  T values([](int i, int) { return (i + 5) * 2; });
  auto replace = [&](auto v, auto ignore) { return eve::replace_ignored(v, ignore, T{0}); };

  auto f = eve::algo::views::iota_scaled_unbound(5,             eve::element_type_t<T>{2}, eve::lane<T::size()>);
  auto l = eve::algo::views::iota_scaled_unbound(5 + T::size(), eve::element_type_t<T>{2}, eve::lane<T::size()>);

  algo_test::iterator_sentinel_test(f, l, values, replace);

  TTS_CONSTEXPR_EXPECT(eve::algo::always_aligned_iterator<decltype(f)>);
};

EVE_TEST_TYPES("Check iota_scaled_iterator, conversions", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  auto f = eve::algo::views::iota_scaled_unbound(0, T(1));

  auto actual_bytes   = eve::algo::views::convert(f, eve::as<std::int8_t>{});
  auto expected_bytes = eve::algo::views::iota_scaled_unbound(0, std::int8_t{1}, eve::lane<eve::expected_cardinal_v<T>>);
  TTS_EQUAL(expected_bytes, actual_bytes);

  auto actual_back = eve::algo::views::convert(actual_bytes, eve::as<T>{});
  TTS_EQUAL(f, actual_back);
};
