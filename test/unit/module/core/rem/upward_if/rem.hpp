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

TTS_CASE_TPL("Check conditional saturated(eve::rem) return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::upward_(eve::rem[ T()              ])(T(), T())), T);
  TTS_EXPR_IS( (eve::upward_(eve::rem[ eve::logical<T>()])(T(), T())), T);
  TTS_EXPR_IS( (eve::upward_(eve::rem[ true             ])(T(), T())), T);
}

TTS_CASE_TPL("Check conditional saturated(eve::rem) behavior", EVE_TYPE)
{
  T tv(eve::Valmax<T>());
  T fv(3);
  auto t = eve::True<T>();
  auto f = eve::False<T>();

  TTS_EQUAL(eve::upward_(eve::rem[ 1 ])(tv, fv)    , eve::upward_(eve::rem)(tv,fv));
  TTS_EQUAL(eve::upward_(eve::rem[ 1.0 ])(tv, fv)  , eve::upward_(eve::rem)(tv,fv));
  TTS_EQUAL(eve::upward_(eve::rem[ true ])(tv, fv) , eve::upward_(eve::rem)(tv,fv));
  TTS_EQUAL(eve::upward_(eve::rem[ t ])(tv, fv)    , eve::upward_(eve::rem)(tv,fv));

  TTS_EQUAL(eve::upward_(eve::rem[ 0 ])(tv, fv)    , tv);
  TTS_EQUAL(eve::upward_(eve::rem[ 0.0 ])(tv, fv)  , tv);
  TTS_EQUAL(eve::upward_(eve::rem[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::upward_(eve::rem[ f ])(tv, fv)    , tv);

  // Mixed case
  eve::as_logical_t<T> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL ( eve::upward_(eve::rem[ m ])(tv, fv),
                  eve::if_else(m, eve::upward_(eve::rem)(tv,fv), tv)
                );

}
