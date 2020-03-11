//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/copysign.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::copysign return type")
{
  TTS_EXPR_IS(eve::copysign(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::copysign behavior")
{
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::copysign((EVE_TYPE(1.)), eve::Mzero<EVE_TYPE>()), (EVE_TYPE(-1.)));
    TTS_EQUAL(eve::copysign((EVE_TYPE(1.)), (EVE_TYPE(0.))        ), (EVE_TYPE(1.)));
  }
  else if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::copysign((EVE_TYPE(-1.)), (EVE_TYPE(-1.)) ) , (EVE_TYPE(-1.)) );
    TTS_EQUAL(eve::copysign((EVE_TYPE(-1.)), (EVE_TYPE(1.))  ) , (EVE_TYPE(1.))  );
    TTS_EQUAL(eve::copysign((EVE_TYPE(1.)) , (EVE_TYPE(1.))  ) , (EVE_TYPE(1.))  );
    TTS_EQUAL(eve::copysign((EVE_TYPE(1.)) , (EVE_TYPE(-1.)) ) , (EVE_TYPE(-1.)) );

    TTS_EQUAL(eve::copysign((EVE_TYPE(0.)) , (EVE_TYPE(0.))) , (EVE_TYPE(0.))  );
    TTS_EQUAL(eve::copysign((EVE_TYPE(-1.)), (EVE_TYPE(0.))) , (EVE_TYPE(1.))  );
  }
  else
  {
    TTS_EQUAL(eve::copysign((EVE_TYPE(1.)), (EVE_TYPE(1.))), (EVE_TYPE(1.)) );
    TTS_EQUAL(eve::copysign((EVE_TYPE(1.)), (EVE_TYPE(0.))), (EVE_TYPE(1.)) );
    TTS_EQUAL(eve::copysign((EVE_TYPE(0.)), (EVE_TYPE(0.))), (EVE_TYPE(0.)) );
  }
}
