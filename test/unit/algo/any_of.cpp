//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/any_of.hpp>

#include "find_generic_test.hpp"

EVE_TEST_TYPES("Check any_of", algo_test::selected_types)
<typename T>(eve::as_<T> as_t)
{
  algo_test::find_generic_test(as_t, [](auto f, auto l, auto res) {
    bool actual = eve::algo::any_of(f, l, [](auto x) { return x != 0; });
    bool expected = (res != l);
    TTS_EQUAL(actual, expected);
  });
};
