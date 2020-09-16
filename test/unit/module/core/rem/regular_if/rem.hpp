//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rem.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::rem[condition] return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::rem[ T() ](T(), T()))              , T);
  TTS_EXPR_IS( (eve::rem[ eve::logical<T>() ](T(), T())), T);
  TTS_EXPR_IS( (eve::rem[ true ](T(), T()))             , T);
}

TTS_CASE_TPL("Check eve::rem[condition] behavior", EVE_TYPE)
{
  T tv(2);
  T fv(3);
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(eve::rem[ 1 ](tv, fv)     , eve::toward_zero_(eve::rem)(tv, fv));
  TTS_EQUAL(eve::rem[ 1.0 ](tv, fv)   , eve::toward_zero_(eve::rem)(tv, fv));
  TTS_EQUAL(eve::rem[ true ](tv, fv)  , eve::toward_zero_(eve::rem)(tv, fv));
  TTS_EQUAL(eve::rem[ t ](tv, fv)     , eve::toward_zero_(eve::rem)(tv, fv));

  // All basic FALSE
  TTS_EQUAL(eve::rem[ 0 ](tv, fv)     , tv);
  TTS_EQUAL(eve::rem[ 0.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::rem[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::rem[ f ](tv, fv)     , tv);

  // Mixed case
  eve::as_logical_t<T> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::rem[ m ](tv, fv) , eve::if_else(m,eve::toward_zero_(eve::rem)(tv, fv), tv) );
}
