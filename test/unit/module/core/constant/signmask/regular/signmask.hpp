//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/signmask.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE_TPL("Check signmask return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::Signmask<T>(), T);
}

TTS_CASE_TPL("Check signmask behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::Signmask<T>(), eve::Mzero<T>());
  }
  else if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::Signmask<T>(), T(v_t(1) << (sizeof(v_t)*CHAR_BIT-1)));
  }
}
