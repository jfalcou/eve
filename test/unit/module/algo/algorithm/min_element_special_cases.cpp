//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include <span>

TTS_CASE("Min element one pass, uint8 index")
{
  auto alg = eve::algo::min_element         //
      [eve::algo::single_pass]              //
      [eve::algo::index_type<std::uint8_t>] //
      [eve::algo::unroll<2>];
  {
    std::vector v {1, 2, 3};
    TTS_EQUAL(0, alg(v) - v.begin());
  }
  {
    std::vector v {2, 1, 3};
    TTS_EQUAL(1, alg(v) - v.begin());
  }
  {
    std::vector v {3, 2, 1};
    TTS_EQUAL(2, alg(v) - v.begin());
  }
  {
    std::vector<std::int8_t> v(1000u, 1);
    v.back() = 0;
    TTS_EQUAL(999, alg(v) - v.begin());
  }
  {
    std::vector<std::int8_t> v(std::numeric_limits<std::uint16_t>::max() + 1, 'b');
    v.back() = 'a';
    v[5]     = 'a';
    TTS_EQUAL(5, alg(v) - v.begin());
    v[5] = 'b';
    TTS_EQUAL(std::ssize(v) - 1, alg(v) - v.begin());
  }
  {
    std::vector<std::int8_t> v;
    v.resize(48, 'b');
    v[23] = 'a';
    v[47] = 'a';
    TTS_EQUAL(23, alg(v) - v.begin());
  }
  {
    std::vector<std::int8_t> v;
    v.resize(159, 'b');
    v[2]     = 'a';
    v.back() = 'a';
    std::span<std::int8_t> s(v.begin() + 1, v.end());
    TTS_EQUAL(1, alg(s) - s.begin());
  }
};

TTS_CASE("Min element one pass, uint8 index, first one is the answer") {
  auto alg = eve::algo::min_element         //
      [eve::algo::single_pass]              //
      [eve::algo::index_type<std::uint8_t>] //
      [eve::algo::unroll<2>];

  std::vector<std::int8_t> v;
  v.resize(300);

  for (int i = 0; i != 16; ++i) {
    for (int j = 0; j != 16; ++j) {
      eve::algo::fill(v, 0);
      std::span<std::int8_t> sub(v.begin() + i, v.end() - j);
      eve::algo::fill(sub, -1);

      for (std::int8_t& x: sub) {
        std::int8_t* found = std::to_address(alg(sub));
        TTS_EQUAL(found, &x);
        x = 0;
      }
    }
  }
};
