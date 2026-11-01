//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace
{
void all_selected_filled_by_main_loop(auto alg, auto func, auto op)
{
  constexpr std::ptrdiff_t w = eve::wide<int>::size();

  std::vector<int> in(4 * w);
  std::iota(in.begin(), in.end(), 1);

  for( std::ptrdiff_t n : {w, 2 * w, 4 * w} )
  {
    std::vector<int> expected(in.begin(), in.begin() + n);
    std::transform(expected.begin(), expected.end(), expected.begin(), op);

    auto check = [&](auto a)
    {
      std::vector<int> out(n);
      TTS_EQUAL(a(in, out, func) - out.begin(), n);
      TTS_EQUAL(out, expected);
    };

    check(alg[eve::algo::no_aligning]);
    check(alg);
  }
}
}

TTS_CASE("eve.algo.copy_if, all selected, output filled by the main loop")
{
  all_selected_filled_by_main_loop(eve::algo::copy_if,
                                   [](auto x) { return x > 0; },
                                   [](int x) { return x; });
};

TTS_CASE("eve.algo.transform_copy_if, all selected, output filled by the main loop")
{
  all_selected_filled_by_main_loop(eve::algo::transform_copy_if,
                                   [](auto x) { return kumi::make_tuple(x * 2, x > 0); },
                                   [](int x) { return x * 2; });
};
