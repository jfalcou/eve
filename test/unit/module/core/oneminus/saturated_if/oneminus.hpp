//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE("Check oneminus return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ EVE_VALUE(0)  ])(EVE_TYPE(0))              , (EVE_TYPE));
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ (EVE_TYPE(0)) ])(EVE_TYPE(0))              , (EVE_TYPE));
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ (eve::logical<EVE_TYPE>(0))])(EVE_TYPE(0)) , (EVE_TYPE));
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ eve::logical<EVE_VALUE>(0) ])(EVE_TYPE(0)) , (EVE_TYPE));
  //TTS_EXPR_IS(eve::saturated_(eve::oneminus[ true ](EVE_TYPE(0)))                   , (EVE_TYPE));
}

TTS_CASE("Check eve::saturated_(eve::oneminus) behavior")
{
  EVE_TYPE tv, res;
  auto t = eve::True<EVE_TYPE>();
  auto f = eve::False<EVE_TYPE>();

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    tv  = eve::Valmin<EVE_TYPE>();
    res = eve::Valmax<EVE_TYPE>();
  }
  else
  {
    tv  = EVE_TYPE{2};
    res = EVE_TYPE{0};
  }

  TTS_EQUAL(eve::saturated_(eve::oneminus[ 1    ])(tv), res);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ 1.0  ])(tv), res);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ true ])(tv), res);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ t    ])(tv), res);

  TTS_EQUAL(eve::saturated_(eve::oneminus[ 0 ])(tv)     , tv);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ 0.0 ])(tv)   , tv);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ false ])(tv) , tv);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ f ])(tv)     , tv);

    // Mixed case
  eve::as_logical_t<EVE_TYPE> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::saturated_(eve::oneminus[ m ])(tv), eve::if_else(m, res, tv) );
}
