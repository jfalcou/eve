//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"
#include <eve/module/algo.hpp>

#include "unit/module/algo/algorithm/reduce_generic.hpp"

TTS_CASE_TPL("Check reduce", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  reduce_generic_all_test_cases(eve::as<T>{}, eve::algo::reduce);
};
