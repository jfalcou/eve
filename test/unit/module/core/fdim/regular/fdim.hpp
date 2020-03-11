//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fdim.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::fdim return type")
{
  TTS_EXPR_IS(eve::fdim(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE(" fdim behaviour")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::fdim(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>()), eve::Zero<EVE_TYPE>());
    TTS_EQUAL(eve::fdim(eve::Minf<EVE_TYPE>(), eve::Minf<EVE_TYPE>()), eve::Zero<EVE_TYPE>());
    TTS_ULP_EQUAL((eve::fdim(eve::Nan<EVE_TYPE>(), eve::Nan<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL((eve::fdim(eve::Nan<EVE_TYPE>(), eve::Zero<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL((eve::fdim(eve::Zero<EVE_TYPE>(), eve::Nan<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL((eve::fdim(eve::Nan<EVE_TYPE>(), eve::Zero<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL((eve::fdim(eve::One<EVE_TYPE>(), eve::Nan<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL((eve::fdim(eve::Nan<EVE_TYPE>(), eve::One<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
  }
  TTS_EQUAL((eve::fdim(eve::Mone<EVE_TYPE>(), eve::Mone<EVE_TYPE>())), eve::Zero<EVE_TYPE>());
  TTS_EQUAL((eve::fdim(eve::One<EVE_TYPE>(), eve::One<EVE_TYPE>())), eve::Zero<EVE_TYPE>());
  TTS_EQUAL((eve::fdim(eve::Zero<EVE_TYPE>(), eve::Zero<EVE_TYPE>())), eve::Zero<EVE_TYPE>());
  TTS_EQUAL((eve::fdim(eve::One<EVE_TYPE>(), eve::Zero<EVE_TYPE>())), eve::One<EVE_TYPE>());
  TTS_EQUAL((eve::fdim(EVE_TYPE(2), EVE_TYPE(-3))), EVE_TYPE(5));
  TTS_EQUAL((eve::fdim(EVE_TYPE(2), EVE_TYPE(3))), EVE_TYPE(0));
}
