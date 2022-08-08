//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================

#include "unit/algo/algorithm/minmax_generic_test.hpp"

#include <eve/algo.hpp>

TTS_CASE_TPL("Check min_value", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::minmax_generic_test</*biggest*/ false, /*right*/ false>(
      eve::as<T> {},
      eve::algo::min_value,
      [](auto, auto l, auto expected, auto actual)
      {
        if( expected == l ) { TTS_EXPECT(!actual); }
        else { TTS_EQUAL(*expected, *actual); }
      });
};
