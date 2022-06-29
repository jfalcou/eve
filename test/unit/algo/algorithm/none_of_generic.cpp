//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/none_of.hpp>

#include "find_generic_test.hpp"

TTS_CASE_TPL("eve.algo.none_of generic", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::find_generic_test(eve::as<T>{}, eve::algo::none_of,
  [](auto, auto l, auto expected, bool actual) {
    TTS_EQUAL(actual, (expected == l));
  });
};
