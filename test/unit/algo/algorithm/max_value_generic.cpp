//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algorithm/minmax_generic_test.hpp"

#include <eve/algo.hpp>

TTS_CASE_TPL("Check max_value", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::minmax_generic_test</*biggest*/ true, /*right*/ true>(
      eve::as<T> {},
      eve::algo::max_value,
      [](auto, auto l, auto expected, auto actual)
      {
        if( expected == l ) { TTS_EXPECT(!actual); }
        else { TTS_EQUAL(*expected, *actual); }
      });
};
