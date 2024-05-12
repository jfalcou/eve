//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/find.hpp>

#include "find_generic_test.hpp"

TTS_CASE_TPL("Check find_if", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::find_generic_test(eve::as<T>{}, eve::algo::find_if,
  [](auto, auto, auto expected, auto actual) {
    TTS_EQUAL(actual, expected);
  });
};
