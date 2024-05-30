//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "transform_copy_if_generic_test.hpp"

TTS_CASE_TPL("Check transform_copy_if", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  auto op = [](auto x) { return x + x; };
  algo_test::transform_copy_if_generic_test(eve::as<T>{}, eve::algo::transform_copy_if, op);
};
