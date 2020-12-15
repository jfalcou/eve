//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/betainc.hpp>

TTS_CASE_TPL("Check eve::betainc return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::betainc(T()   , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::betainc(T()   , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::betainc(T()   , v_t() , T()   ) , T);
  TTS_EXPR_IS(eve::betainc(T()   , v_t() , v_t() ) , T);
  TTS_EXPR_IS(eve::betainc(v_t() , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::betainc(v_t() , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::betainc(v_t() , v_t() , T()   ) , T);
}

TTS_CASE_TPL("Check eve::betainc behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::betainc(T(0), T(0), T(0)), T(0)  );
  TTS_EQUAL(eve::betainc(T(0), T(0), T(7)), T(0)  );
  TTS_ULP_EQUAL(eve::betainc(T(0.5), T(0.5), T(0.5)), T(0.5) , 1.5 );
  TTS_ULP_EQUAL(eve::betainc(T(0.2), T(0.3), T(2)), T(7.651219897728122e-01), 3);
}
