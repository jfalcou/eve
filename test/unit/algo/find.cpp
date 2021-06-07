//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/find.hpp>

#include "find_generic_test.hpp"

EVE_TEST_TYPES("Check find_if", algo_test::selected_types)
<typename T>(eve::as_<T> as_t)
{
  algo_test::find_generic_test(as_t, eve::algo::find_if,
  [](auto, auto, auto expected, auto actual) {
    TTS_EQUAL(actual, expected);
  });
};
