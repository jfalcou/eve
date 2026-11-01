//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/memory/load/conditional.hpp"

TTS_CASE_TPL("Check conditional loads of arithmetic wides", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  check_conditional_loads(T([](auto i, auto) { return 101 + i % 20; }));
};

TTS_CASE_TPL("Check conditional loads of arithmetic wides from nullptr keeping no lane", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  check_empty_loads_from_nullptr(T([](auto i, auto) { return 101 + i % 20; }));
};
