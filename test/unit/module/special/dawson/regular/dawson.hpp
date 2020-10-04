//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dawson.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/minlog2.hpp>
#include <eve/constant/minlog2denormal.hpp>
#include <eve/concept/value.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/concept/value.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::dawson return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::dawson(T(0)), T);
}

TTS_CASE_TPL("Check eve::dawson behavior", EVE_TYPE)
{

 if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::dawson(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::dawson(eve::inf(eve::as<T>()))  , T(0) );
    TTS_IEEE_EQUAL(eve::dawson(eve::minf(eve::as<T>())) , T(0) );
  }


   TTS_IEEE_EQUAL(eve::dawson(T( 0 )), T(0) );
   TTS_IEEE_EQUAL(eve::dawson(T(-0.)), T(0) );
   TTS_ULP_EQUAL(eve::dawson(T( 1 )), T(0.53807950691276840161),                      0.5  );
   TTS_ULP_EQUAL(eve::dawson(T( 2)) , T(0.30134038892379196603466443928642),          0.5  );
   TTS_ULP_EQUAL(eve::dawson(T( 4)) , T(1.293480012360051e-01),                       0.5  );
   TTS_ULP_EQUAL(eve::dawson(T( 8)) , T( 6.300019870755338e-02),                      0.5  );
   TTS_ULP_EQUAL(eve::dawson(T( 1.0e10)), T(  5.000000000000000e-11),                 0.5  );
   TTS_ULP_EQUAL(eve::dawson(T( 2.5 )), T( 2.230837221674355e-01),                    1.0  );
   TTS_ULP_EQUAL(eve::dawson(T(0.9241388730)), T(5.410442246351818e-01),              0.5  );

   eve::wide < float, eve::fixed < 8 > > w{0.0f, 1.0f, 2.0f, 4.0f, 8.0f, 2.0, eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};
   eve::wide < float, eve::fixed < 8 > > r{eve::dawson(( 0.0f )),
                                           eve::dawson(( 1.0f )),
                                           eve::dawson(( 2.0f )),
                                           eve::dawson(( 4.0f )),
                                           eve::dawson(( 8.0f )),
                                           eve::dawson(( 2.0f )),
       eve::dawson(eve::inf(eve::as<float>())),
       eve::dawson( eve::nan(eve::as<float>()))};
   TTS_ULP_EQUAL(eve::dawson(w), r, 2);


}
