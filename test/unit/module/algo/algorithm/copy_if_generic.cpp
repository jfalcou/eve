//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "copy_if_generic_test.hpp"

TTS_CASE_TPL("Check copy_if", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::copy_if_generic_test(eve::as<T>{}, eve::algo::copy_if);
};
