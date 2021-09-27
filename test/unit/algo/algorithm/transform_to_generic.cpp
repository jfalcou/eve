//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/transform.hpp>

#include "transform_to_generic_test.hpp"

#include <algorithm>

EVE_TEST_TYPES("Check trasnform_to", algo_test::selected_pairs_types)
<typename T>(eve::as<T> tgt)
{
  algo_test::transform_to_generic_test(
    tgt,
    eve::algo::transform_to,
    [](auto f, auto l, auto o, auto op) {
      (void)op;
      std::transform(f, l, o,
      [](auto x) { return static_cast<decltype(x)>(x + x); });
    },
    [](auto x) { return x + x; }
  );
};
