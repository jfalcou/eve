//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/memory/load/conditional.hpp"

TTS_CASE_TPL("Check conditional loads of signed integer arithmetic wides", eve::test::simd::signed_integers)
<typename T>(tts::type<T>)
{
  check_loads(T([](auto i, auto) { return 101 + i % 20; }));
};
