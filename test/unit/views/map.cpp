//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/module/core.hpp>
#include "unit/algo/algo_test.hpp"

#include <eve/views/map.hpp>


struct load_op
{
  auto operator()(auto x) const
  {
    return eve::convert(x, eve::as<double>{}) * 2.0;
  }
};

struct store_op
{
  auto operator()(auto x, eve::as<int>) const
  {
    return eve::convert(x / 2.0, eve::as<double>{});
  }
};

TTS_CASE("eve::views::map, read/write")
{
  std::vector<int> v{1, 2, 3, 4};

  auto map     = eve::views::map(v, load_op{});
  auto map_cvt = eve::views::map_convert(v, load_op{}, store_op{});

  {
    eve::views::map_iterator f = map.begin();
    TTS_EQUAL(eve::read(f),     2.0);
    TTS_EQUAL(eve::read(f + 1), 4.0);
    TTS_EQUAL(eve::read(f + 2), 6.0);
    TTS_EQUAL(eve::read(f + 3), 8.0);
  }

  {
    eve::views::map_iterator f = map_cvt.begin();
    TTS_EQUAL(eve::read(f),     2.0);
    TTS_EQUAL(eve::read(f + 1), 4.0);
    TTS_EQUAL(eve::read(f + 2), 6.0);
    TTS_EQUAL(eve::read(f + 3), 8.0);
  }
};

TTS_CASE("eve::views::map, preprocess")
{
  std::vector<int> v;

  using up = int*;
  using ap = eve::aligned_ptr<int>;

  // double because the map operation returns double
  using N      = eve::fixed<eve::expected_cardinal_v<double>>;
  using ui     = eve::algo::ptr_iterator<int*, N>;
  using ai     = eve::algo::ptr_iterator<eve::aligned_ptr<int, N>, N>;
  using map_ui = eve::views::map_iterator<ui, load_op, store_op>;
  using map_ai = eve::views::map_iterator<ai, load_op, store_op>;

  TTS_TYPE_IS(eve::value_type_t<map_ui>, double);
  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<map_ui>, (kumi::tuple<double, int>));

  eve::views::map_range mapped = eve::views::map_convert(eve::algo::as_range(ap{}, up{}), load_op{}, store_op{});

  TTS_TYPE_IS(eve::value_type_t<decltype(mapped)>, double);
  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<decltype(mapped)>, (kumi::tuple<double, int>));

  auto processed = eve::algo::preprocess_range(eve::algo::traits{}, mapped);

  TTS_TYPE_IS(decltype(processed.begin()), map_ai);
  TTS_TYPE_IS(decltype(processed.end()), map_ui);
  TTS_TYPE_IS(decltype(eve::load(processed.begin())), eve::wide<double>);
};
