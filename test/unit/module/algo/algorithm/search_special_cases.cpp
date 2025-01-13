//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

TTS_CASE("eve.algo.search, smoke test")
{
  std::vector<int> haystack;
  haystack.resize(100);
  std::iota(haystack.begin(), haystack.end(), 0);

  std::vector<int> needle = {1, 2};
  auto             found  = eve::algo::search(haystack, needle);
  TTS_EQUAL(found - haystack.begin(), 1);

  needle     = {10, 11, 12};
  found = eve::algo::search(haystack, needle);
  TTS_EQUAL(found - haystack.begin(), 10);

  found = eve::algo::search(haystack, needle);
  TTS_EQUAL(found - haystack.begin(), 10);

  needle.assign(20, 0);
  std::iota(needle.begin(), needle.end(), 35);

  found = eve::algo::search(haystack, needle);
  TTS_EQUAL(found - haystack.begin(), 35);
};

TTS_CASE("eve.algo.search, doesn't stop bug")
{
  std::vector<std::int8_t> haystack(1000U, 1);
  std::vector<std::int8_t> needle{1, 2, 1};

  auto found = eve::algo::search(haystack, needle);
  TTS_EQUAL(found - haystack.begin(), (std::ptrdiff_t)haystack.size());
};

TTS_CASE("eve.algo.search, last char of 32") {
  std::vector<std::int8_t> haystack;
  haystack.resize(32);
  haystack.back() = 1;

  std::vector<std::int8_t> needle = {1};

  auto found = eve::algo::search(haystack, needle);
  TTS_EQUAL(found - haystack.begin(), 31);
};
