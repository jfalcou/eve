//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fms.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check eve::fms return type")
{
  TTS_EXPR_IS(eve::numeric_(eve::fms)(EVE_TYPE(), EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::numeric_(eve::fms) behavior")
{
  TTS_EQUAL(eve::numeric_(eve::fms)(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::numeric_(eve::fms)(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE(-7)), (EVE_TYPE(7)));
  TTS_EQUAL(eve::numeric_(eve::fms)(EVE_TYPE(2), EVE_TYPE(0), EVE_TYPE(-7)), (EVE_TYPE(7)));
  TTS_EQUAL(eve::numeric_(eve::fms)(EVE_TYPE(0), EVE_TYPE(5), EVE_TYPE(-7)), (EVE_TYPE(7)));
  TTS_EQUAL(eve::numeric_(eve::fms)(EVE_TYPE(2), EVE_TYPE(5), EVE_TYPE(-7)), (EVE_TYPE(17)));
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    EVE_TYPE e = eve::Eps<EVE_TYPE>();
    TTS_EQUAL(eve::numeric_(eve::fms)(eve::inc(e), eve::oneminus(e), eve::One<EVE_TYPE>()), (-eve::sqr(e)));
    TTS_EQUAL(                        (eve::inc(e)* eve::oneminus(e)- eve::One<EVE_TYPE>()) , eve::Zero<EVE_TYPE>());
    TTS_EQUAL(eve::numeric_(eve::fms)(eve::Valmax<EVE_TYPE>(), EVE_TYPE(2), eve::Valmax<EVE_TYPE>()), eve::Valmax<EVE_TYPE>());
    TTS_EQUAL(                       (eve::Valmax<EVE_TYPE>()* EVE_TYPE(2)+ eve::Valmax<EVE_TYPE>()), eve::Inf<EVE_TYPE>()); 
  }
  
}
