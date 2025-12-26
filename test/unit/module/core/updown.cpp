//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check type of eve::spli_down_t", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  constexpr auto lowerN = eve::integral_value<T> ? 1 : 2; 
  if constexpr(sizeof(eve::element_type_t<T>) > lowerN)
  {
    using d_t = eve::downgrade_t<T>;
    using r_t = decltype(eve::combine(d_t(), d_t()));
    TTS_EXPR_IS(eve::split_down_t<T>(),r_t );
  }
  else
    TTS_EXPR_IS(eve::split_down_t<T>(), T );
};
