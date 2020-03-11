//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/negatenz.hpp>
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

TTS_CASE("Check eve::pedantic_(eve::negatenz) return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::negatenz)(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE(" negatenz behaviour")
{
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>());
      TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::Minf<EVE_TYPE>(), eve::Minf<EVE_TYPE>()), eve::Inf<EVE_TYPE>());
      TTS_ULP_EQUAL((eve::pedantic_(eve::negatenz)(eve::Nan<EVE_TYPE>(), eve::Nan<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
      TTS_ULP_EQUAL((eve::pedantic_(eve::negatenz)(eve::Nan<EVE_TYPE>(), eve::Zero<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
      TTS_ULP_EQUAL((eve::pedantic_(eve::negatenz)(eve::Zero<EVE_TYPE>(), eve::Nan<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
      TTS_ULP_EQUAL((eve::pedantic_(eve::negatenz)(eve::One<EVE_TYPE>(), eve::Nan<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
      TTS_ULP_EQUAL((eve::pedantic_(eve::negatenz)(eve::Nan<EVE_TYPE>(), eve::One<EVE_TYPE>())), eve::Nan<EVE_TYPE>(), 0);
    }
    TTS_EQUAL((eve::pedantic_(eve::negatenz)(eve::One<EVE_TYPE>(), eve::Mzero<EVE_TYPE>())), eve::Mone<EVE_TYPE>()); 
    TTS_EQUAL((eve::pedantic_(eve::negatenz)(EVE_TYPE(2), EVE_TYPE(-3))), EVE_TYPE(-2));
    TTS_EQUAL((eve::pedantic_(eve::negatenz)(EVE_TYPE(2), EVE_TYPE(3))), EVE_TYPE(2));
  }
  else if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::Mone<EVE_TYPE>(), eve::Mone<EVE_TYPE>()), eve::One<EVE_TYPE>());
    TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::Mone<EVE_TYPE>(), eve::One<EVE_TYPE>()), eve::Mone<EVE_TYPE>());
  }
  TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::One<EVE_TYPE>(), eve::One<EVE_TYPE>()), eve::One<EVE_TYPE>());
  TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::Zero<EVE_TYPE>(), eve::Zero<EVE_TYPE>()), eve::Zero<EVE_TYPE>());
  TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::One<EVE_TYPE>(), eve::Zero<EVE_TYPE>()), eve::One<EVE_TYPE>());
}
