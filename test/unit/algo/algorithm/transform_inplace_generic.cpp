//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/transform.hpp>

#include "transform_inplace_generic_test.hpp"

#include <algorithm>

EVE_TEST_TYPES("Check transform_inplace", algo_test::selected_types)
<typename T>(eve::as<T> tgt)
{
  algo_test::transform_inplace_generic_test(
    tgt,
    eve::algo::transform_inplace,
    [](auto f, auto l, auto o, auto op) {
      std::transform(f, l, o, op);
    },
    [](auto x) { return x + x; }
  );
};
