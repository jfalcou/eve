//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::big(eve::cos) return type")
{
  TTS_EXPR_IS(eve::big(eve::cos)(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::big(eve::cos) behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big(eve::cos)(eve::nan(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::big(eve::cos)(eve::inf(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::big(eve::cos)(eve::minf(eve::as<EVE_TYPE>())), (eve::nan(eve::as<EVE_TYPE>())) );
  }

  auto std_cos = [](auto e) { return std::cos(double(e)); };

  TTS_IEEE_EQUAL( eve::big(eve::cos)(EVE_TYPE(-0.)), EVE_TYPE(1) );
  TTS_IEEE_EQUAL( eve::big(eve::cos)(EVE_TYPE( 0.)), EVE_TYPE(1) );

  TTS_ULP_EQUAL(eve::big(eve::cos)( EVE_TYPE(1)           )         , EVE_TYPE(std_cos(1.0))                   , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cos)(-EVE_TYPE(1)           )         , EVE_TYPE(std_cos(-1.0))                  , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cos)( eve::pio_4(eve::as<EVE_TYPE>()))         , EVE_TYPE(std_cos( eve::pio_4(eve::as<EVE_VALUE>())))    , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cos)(-eve::pio_4(eve::as<EVE_TYPE>()))         , EVE_TYPE(std_cos(-eve::pio_4(eve::as<EVE_VALUE>())))    , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cos)( EVE_TYPE(100000.0)    )         , EVE_TYPE(std_cos(100000.0))              , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cos)(-EVE_TYPE(100000.0)    )         , EVE_TYPE(std_cos(-100000.0))             , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cos)( EVE_TYPE(100000000.0) )         , EVE_TYPE(std_cos(100000000.0))           , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cos)(-EVE_TYPE(100000000.0) )         , EVE_TYPE(std_cos(-100000000.0))          , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cos)( EVE_TYPE(eve::valmax(eve::as<EVE_TYPE>()))    ) , EVE_TYPE(std_cos(eve::valmax(eve::as<EVE_VALUE>()))   ) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cos)( EVE_TYPE(eve::valmax(eve::as<EVE_TYPE>())/10) ) , EVE_TYPE(std_cos(eve::valmax(eve::as<EVE_VALUE>())/10 )), 0.5);

  using wide_dt = eve::wide<double, eve::fixed<4>>;

  wide_dt e{+0x1.42ae8e38e5eb9p+954, +0x1.ee7ed0206072ap+559, +0x1.d71af50a57018p-128, +0x1.154e112f8b03cp-826};
  wide_dt f{+0x1.f231a6797dd59p-2, +0x1.f3a517713f05fp-1, +0x1p+0, +0x1p+0};
  std::cout << "---- simd" << std::hexfloat << '\n'
            << "<- e      = " << e << '\n'
             << "-> cos(e) = " << eve::big(eve::cos)(e) << '\n';

  TTS_ULP_EQUAL(eve::big(eve::cos)(e), f, 0.5);
}
