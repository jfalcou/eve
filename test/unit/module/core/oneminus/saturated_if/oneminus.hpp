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
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ Value(0)  ])(Type(0))              , (Type));
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ (Type(0)) ])(Type(0))              , (Type));
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ (eve::logical<Type>(0))])(Type(0)) , (Type));
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ eve::logical<Value>(0) ])(Type(0)) , (Type));
  //TTS_EXPR_IS(eve::saturated_(eve::oneminus[ true ](Type(0)))                   , (Type));
}

TTS_CASE("Check eve::saturated_(eve::oneminus) behavior")
{
  Type tv, res;
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  if constexpr(std::is_signed_v<Value>)
  {
    tv  = eve::Valmin<Type>();
    res = eve::Valmax<Type>();
  }
  else
  {
    tv  = Type{2};
    res = Type{0};
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
  eve::as_logical_t<Type> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_ALL_EQUAL(eve::saturated_(eve::oneminus[ m ])(tv), eve::if_else(m, res, tv) );
}
