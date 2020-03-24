//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/minus.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>

TTS_CASE("Check eve::minus return type")
{
  TTS_EXPR_IS(eve::minus(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::minus behavior")
{
  TTS_EQUAL(eve::minus(EVE_TYPE( 1)) , static_cast<EVE_TYPE>(-1));
  TTS_EQUAL(eve::minus(EVE_TYPE(-1)) , static_cast<EVE_TYPE>( 1));
  if (std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EXPECT(eve::all(eve::is_negative(eve::minus(eve::Zero<EVE_TYPE>()))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::minus(eve::Mzero<EVE_TYPE>())))); 
  }
  
}
