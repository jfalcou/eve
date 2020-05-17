//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/inf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>
#include <limits>

TTS_CASE_TPL("Check inf return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::Inf<T>(), T);
}

TTS_CASE_TPL("Check inf behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::Inf<T>(), T(std::numeric_limits<v_t>::infinity()) );
}
