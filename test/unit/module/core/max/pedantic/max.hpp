//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/max.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <tts/tests/basic.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::pedantic_(eve::max) return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::max)(EVE_TYPE(0)  , EVE_TYPE(0) ) , (EVE_TYPE));
  TTS_EXPR_IS(eve::pedantic_(eve::max)(EVE_VALUE(0) , EVE_TYPE(0) ) , (EVE_TYPE));
  TTS_EXPR_IS(eve::pedantic_(eve::max)(EVE_TYPE(0)  , EVE_VALUE(0)) , (EVE_TYPE));
}

TTS_CASE("Check eve::pedantic_(eve::max) behavior")
{
  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_TYPE(0)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_TYPE(0)), (EVE_TYPE(1))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_TYPE(1)), (EVE_TYPE(0))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_TYPE(1)), (EVE_TYPE(1))), (EVE_TYPE(1)));

  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_VALUE(0)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_VALUE(0)), (EVE_TYPE(1))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_VALUE(1)), (EVE_TYPE(0))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_VALUE(1)), (EVE_TYPE(1))), (EVE_TYPE(1)));

  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_TYPE(0)), (EVE_VALUE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_TYPE(0)), (EVE_VALUE(1))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_TYPE(1)), (EVE_VALUE(0))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::pedantic_(eve::max)((EVE_TYPE(1)), (EVE_VALUE(1))), (EVE_TYPE(1)));

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_IEEE_EQUAL(eve::pedantic_(eve::max)((eve::Nan<EVE_TYPE>() ), (EVE_TYPE(1))) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::max)((eve::Nan<EVE_VALUE>()), (EVE_TYPE(1))) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::max)((eve::Nan<EVE_TYPE>() ), (EVE_VALUE(1))), (eve::Nan<EVE_TYPE>()) );

    TTS_IEEE_EQUAL(eve::pedantic_(eve::max)((EVE_TYPE(1)) , (eve::Nan<EVE_TYPE>())  ), (EVE_TYPE(1)) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::max)((EVE_VALUE(1)), (eve::Nan<EVE_TYPE>())  ), (EVE_TYPE(1)) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::max)((EVE_TYPE(1)) , (eve::Nan<EVE_VALUE>()) ), (EVE_TYPE(1)) );

    TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic_(eve::max)(eve::Mzero<EVE_TYPE>(), eve::Zero<EVE_TYPE>()))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic_(eve::max)(eve::Zero<EVE_TYPE>(), eve::Mzero<EVE_TYPE>()))));    
  }
}
