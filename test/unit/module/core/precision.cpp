//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>


//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::precision", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::precision(T()), 1+eve::nbmantissabits(eve::as(T())));
};
