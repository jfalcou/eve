//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/fill.hpp>

#include "transform_inplace_generic_test.hpp"

#include <numeric>

EVE_TEST_TYPES("Check fill", algo_test::selected_types)
<typename T>(eve::as<T> tgt)
{
  algo_test::transform_inplace_generic_test(
    tgt,
    eve::algo::fill,
    [](auto f, auto l, auto o, auto v) {
      std::fill(o, o + (l - f), v);
    },
    5
  );
};
