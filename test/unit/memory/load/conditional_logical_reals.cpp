//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/memory/load/conditional.hpp"

TTS_CASE_TPL("Check conditional loads of real logical wides", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  check_loads(eve::logical<T>([](auto i, auto) { return i % 2 == 0; }));
};
