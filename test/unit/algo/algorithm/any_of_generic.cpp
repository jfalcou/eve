//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/any_of.hpp>

#include "find_generic_test.hpp"

EVE_TEST_TYPES("Check any_of", algo_test::selected_types)
<typename T>(eve::as<T> as_t)
{
  algo_test::find_generic_test(as_t, eve::algo::any_of,
  [](auto, auto l, auto expected, bool actual) {
    TTS_EQUAL(actual, (expected != l));
  });
};
