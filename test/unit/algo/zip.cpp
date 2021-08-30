//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/zip.hpp>

#include <vector>

TTS_CASE("zip iterators")
{
  std::vector<int>         v{1, 2, 3, 4};
  std::vector<std::int8_t> c{'a', 'b', 'c', 'd'};

  eve::algo::zip_iterator f = eve::algo::zip(v.begin(), c.begin());
  TTS_EQUAL(v.begin(), get<0>(f));
  TTS_EQUAL(c.begin(), get<1>(f));

  eve::algo::zip_iterator l = eve::algo::zip(v.end(), c.end());
  TTS_EQUAL(v.end(), get<0>(l));
  TTS_EQUAL(c.end(), get<1>(l));

  auto rng_test = [&](auto rng) {
    TTS_EQUAL(rng.begin(), f);
    TTS_TYPE_IS(decltype(rng.begin()), decltype(f));
    TTS_EQUAL(rng.end(), l);
    TTS_TYPE_IS(decltype(rng.end()), decltype(l));
  };

  rng_test(eve::algo::zip(v, c));
  rng_test(eve::algo::zip(v, c.begin()));
  rng_test(eve::algo::zip(v.begin(), c));
}

TTS_CASE("zip range, decomposition")
{
  std::vector<int> const   v{1, 2, 3, 4};
  std::vector<std::int8_t> c{'a', 'b', 'c', 'd'};

  auto zipped = eve::algo::zip(v, c);
  auto [cref_v, ref_c] = zipped;
  TTS_EQUAL(cref_v.begin(), v.begin());
  TTS_EQUAL(cref_v.end(),   v.end());
  TTS_EQUAL(ref_c.begin(),  c.begin());
  TTS_EQUAL(ref_c.end(),    c.end());
}

TTS_CASE("zip/zip_range, traits")
{
  std::vector<int> const   v{1, 2, 3, 4};
  std::vector<std::int8_t> c{'a', 'b', 'c', 'd'};

  eve::algo::traits expected{eve::algo::common_type};

  {
    auto zipped = eve::algo::zip[eve::algo::common_type](v, c);
    TTS_TYPE_IS(decltype(zipped.get_traits()), decltype(expected));
  }

  {
    auto zipped = eve::algo::zip(v, c);
    auto with_traits = zipped[eve::algo::common_type];
    TTS_TYPE_IS(decltype(with_traits.get_traits()), decltype(expected));
  }

  {
    auto zipped = eve::algo::zip(v, c);
    auto with_traits = zipped[expected];
    TTS_TYPE_IS(decltype(with_traits.get_traits()), decltype(expected));
  }
}
