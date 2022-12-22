//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algorithm/minmax_generic_test.hpp"

#include <eve/module/algo.hpp>

#include <algorithm>

TTS_CASE_TPL("Check min_element", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::minmax_generic_test</*biggest*/ false, /*right*/ false>(
      eve::as<T> {},
      eve::algo::min_element,
      [](auto, auto, auto expected, auto actual) { TTS_EQUAL(expected, actual); });
};
