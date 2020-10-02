//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/erfcx.hpp>
#include <eve/constant/halfeps.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::erfcx return type")
{
  TTS_EXPR_IS(eve::erfcx(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::erfcx behavior")
{
  auto eve__erfcx =  [](auto x) { return eve::erfcx(x); };
  using eve::as;
  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(-0.0)), EVE_TYPE(1), 0);
  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(0)), EVE_TYPE(1), 0);
  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(eve::halfeps(as<EVE_TYPE>()))),EVE_TYPE(0.999999999999999874724746818321), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(0.25)), EVE_TYPE(0.7703465477309967439167391723367911261876423850266), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(0.5)), EVE_TYPE(0.61569034419292587487079342268374193678230639126563), 0.5);

  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(1)), EVE_TYPE(0.42758357615580700441075034449051518082015950316425), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(2)), EVE_TYPE(0.25539567631050574386508858090854276330259930525524), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(4)), EVE_TYPE(0.1369994576250613898894451714), 0.5);

  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(5)), EVE_TYPE(0.110704637733068626370212086492), 0.5);      //    1.5);
  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(27)), EVE_TYPE(0.0208816079904209406740944901929), 0.5);    //     4);
  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(100)), EVE_TYPE(0.00564161378298943290355645700695), 0.5);  //   36.5);
  auto big = [](auto x){ return eve::rsqrt(eve::pi(as<EVE_TYPE>()))/x;};

  TTS_ULP_EQUAL(eve__erfcx(eve::valmax(as<EVE_TYPE>()))                   ,big(eve::valmax(as<EVE_TYPE>())), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(eve::prev(eve::valmax(as<EVE_TYPE>()), 3))     ,big(eve::prev(eve::valmax(as<EVE_TYPE>()), 3)), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(eve::prev(eve::valmax(as<EVE_TYPE>()), 2))     ,big(eve::prev(eve::valmax(as<EVE_TYPE>()), 2)), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(eve::prev(eve::valmax(as<EVE_TYPE>()), 1))     ,big(eve::prev(eve::valmax(as<EVE_TYPE>()), 1)), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(EVE_TYPE(1.0E30)), eve::rsqrt(eve::pi(as<EVE_TYPE>()))/EVE_TYPE(1.0E30), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(-eve::halfeps(as<EVE_TYPE>())), EVE_TYPE(1.00000000000000012527525318168), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(-EVE_TYPE(0.25))          , EVE_TYPE(1.3586423701047221152100420169489882200138085022721), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(-EVE_TYPE(0.5))           , EVE_TYPE(1.95236048918255709327604771344), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(-EVE_TYPE(1))             , EVE_TYPE(5.00898008076228346630982459821), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(-EVE_TYPE(2))             , EVE_TYPE(108.940904389977972412355433825), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(-EVE_TYPE(4))             , EVE_TYPE(17772220.9040162876484646575921) , 0.5);
  TTS_ULP_EQUAL(eve__erfcx(-EVE_TYPE(5))             , EVE_TYPE(144009798674.661040410589634306), 0.5);
  TTS_ULP_EQUAL(eve__erfcx(-EVE_TYPE(27))            , eve::inf(as<EVE_TYPE>()), 0);
  TTS_ULP_EQUAL(eve__erfcx(-EVE_TYPE(100))           , eve::inf(as<EVE_TYPE>()), 0);
  TTS_ULP_EQUAL(eve__erfcx(-eve::valmax(as<EVE_TYPE>())) , eve::inf(as<EVE_TYPE>()), 0);
  TTS_ULP_EQUAL(eve__erfcx(eve::valmax(as<EVE_TYPE>())/2)     ,big(eve::valmax(as<EVE_TYPE>())/2), 0.5);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__erfcx(eve::inf(as<EVE_TYPE>())), EVE_TYPE(0), 0);
    TTS_ULP_EQUAL(eve__erfcx(eve::minf(as<EVE_TYPE>())), eve::inf(as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve__erfcx(eve::nan(as<EVE_TYPE>())), eve::nan(as<EVE_TYPE>()), 0);
  }
}
