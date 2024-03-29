//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algorithm/set_intersection_test.hpp"

#include <eve/module/algo.hpp>

TTS_CASE_TPL("Check set_intersection basic", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::set_intersection_test(eve::as<T> {},
                                   eve::algo::set_intersection);
};
