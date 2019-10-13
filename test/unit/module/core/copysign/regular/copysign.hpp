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
  TTS_EXPR_IS(eve::copysign(Type(), Type()), (Type));
}

TTS_CASE("Check eve::copysign behavior")
{
  if constexpr(std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::copysign((Type(1.)), eve::Mzero<Type>()), (Type(-1.)));
    TTS_EQUAL(eve::copysign((Type(1.)), (Type(0.))        ), (Type(1.)));
  }
  else if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::copysign((Type(-1.)), (Type(-1.)) ) , (Type(-1.)) );
    TTS_EQUAL(eve::copysign((Type(-1.)), (Type(1.))  ) , (Type(1.))  );
    TTS_EQUAL(eve::copysign((Type(1.)) , (Type(1.))  ) , (Type(1.))  );
    TTS_EQUAL(eve::copysign((Type(1.)) , (Type(-1.)) ) , (Type(-1.)) );

    TTS_EQUAL(eve::copysign((Type(0.)) , (Type(0.))) , (Type(0.))  );
    TTS_EQUAL(eve::copysign((Type(-1.)), (Type(0.))) , (Type(1.))  );
  }
  else
  {
    TTS_EQUAL(eve::copysign((Type(1.)), (Type(1.))), (Type(1.)) );
    TTS_EQUAL(eve::copysign((Type(1.)), (Type(0.))), (Type(1.)) );
    TTS_EQUAL(eve::copysign((Type(0.)), (Type(0.))), (Type(0.)) );
  }
}
