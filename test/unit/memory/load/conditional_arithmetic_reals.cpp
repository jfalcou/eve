//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/memory/load/conditional.hpp"

TTS_CASE_TPL("Check conditional loads of real arithmetic wides", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  check_loads(T([](auto i, auto) { return 101 + i % 20; }));
};
