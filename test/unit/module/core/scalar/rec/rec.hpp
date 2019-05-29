//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REC_HPP
#define REC_HPP

#include "test.hpp"
#include <eve/function/scalar/rec.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check rec return type")
{
  TTS_EXPR_IS(eve::rec(Type(0)),  Type);
  TTS_EXPR_IS(eve::rec[eve::raw_](Type(0)),  Type);
}

TTS_CASE("Check eve::rec behavior")
{
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::rec( Type(0)), eve::Inf<Type>()  );
    TTS_EQUAL(eve::rec(-Type(0)), eve::Minf<Type>() );
    TTS_EQUAL(eve::rec( Type(1)), Type(1)           );
    TTS_EQUAL(eve::rec( Type(2)), Type(1)/Type(2)   );
  }
  else
  {
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::rec(Type(-1) ), Type(-1));
      TTS_EQUAL(eve::rec(Type(-2) ), Type(0));
      TTS_EQUAL(eve::rec(Type(-47)), Type(0));
    }

    TTS_EQUAL(eve::rec(Type(0) ), eve::Valmax<Type>());
    TTS_EQUAL(eve::rec(Type(1) ), Type(1));
    TTS_EQUAL(eve::rec(Type(2) ), Type(0));
    TTS_EQUAL(eve::rec(Type(47)), Type(0));
  }
}

TTS_CASE("Check eve::rec[raw_] behavior")
{
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::rec[eve::raw_]( Type(0)), eve::Inf<Type>()  );
    TTS_EQUAL(eve::rec[eve::raw_](-Type(0)), eve::Minf<Type>() );
    TTS_EQUAL(eve::rec[eve::raw_]( Type(1)), Type(1)           );
    TTS_EQUAL(eve::rec[eve::raw_]( Type(2)), Type(1)/Type(2)   );
  }
  else
  {
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::rec[eve::raw_](Type(-1) ), Type(-1));
      TTS_EQUAL(eve::rec[eve::raw_](Type(-2) ), Type(0));
      TTS_EQUAL(eve::rec[eve::raw_](Type(-47)), Type(0));
    }

    TTS_EQUAL(eve::rec[eve::raw_](Type(0) ), eve::Valmax<Type>());
    TTS_EQUAL(eve::rec[eve::raw_](Type(1) ), Type(1));
    TTS_EQUAL(eve::rec[eve::raw_](Type(2) ), Type(0));
    TTS_EQUAL(eve::rec[eve::raw_](Type(47)), Type(0));
  }
}

#endif
