//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/if_else.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::if_else return type", EVE_TYPE)
{
  using sT =  eve::element_type_t<T>;
  TTS_EXPR_IS(eve::if_else(T()               , T(), T()), T);
  TTS_EXPR_IS( eve::if_else(eve::logical<T>() , T(), T()), T);
  TTS_EXPR_IS(eve::if_else(true              , T(), T()), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>(), T(),  sT()), T);
}

TTS_CASE_TPL("Check eve::if_else behavior with arithmetic alternatives", EVE_TYPE)
{
  T tv{2};
  T fv{3};
  auto t = eve::True<T>();
  auto f = eve::False(eve::as<T>());

  TTS_EQUAL(eve::if_else(1    , tv, fv), tv);
  TTS_EQUAL(eve::if_else(1.0  , tv, fv), tv);
  TTS_EQUAL(eve::if_else(true , tv, fv), tv);
  TTS_EQUAL(eve::if_else(t    , tv, fv), tv);
  TTS_EQUAL(eve::if_else(0    , tv, fv), fv);
  TTS_EQUAL(eve::if_else(0.0  , tv, fv), fv);
  TTS_EQUAL(eve::if_else(false, tv, fv), fv);
  TTS_EQUAL(eve::if_else(f    , tv, fv), fv);
  TTS_EQUAL(eve::if_else(fv    , tv, fv), tv);
}

TTS_CASE_TPL("Check eve::if_else behavior with logical alternatives", EVE_TYPE)
{
  auto t = eve::True<T>();
  auto f = eve::False(eve::as<T>());
 T fv{3};

  TTS_EQUAL(eve::if_else(1    , t, f), t);
  TTS_EQUAL(eve::if_else(1.0  , t, f), t);
  TTS_EQUAL(eve::if_else(true , t, f), t);
  TTS_EQUAL(eve::if_else(t    , t, f), t);
  TTS_EQUAL(eve::if_else(0    , t, f), f);
  TTS_EQUAL(eve::if_else(0.0  , t, f), f);
  TTS_EQUAL(eve::if_else(false, t, f), f);
  TTS_EQUAL(eve::if_else(f    , t, f), f);
  TTS_EQUAL(eve::if_else(fv   , t, f), t);
}
