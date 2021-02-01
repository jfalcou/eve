//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

TTS_CASE_TPL("Check operator+ return type", EVE_TYPE)
{
  TTS_EXPR_IS( +T()                         , T);
  TTS_EXPR_IS( (T()          + T()        ) , T);
  TTS_EXPR_IS( (T()          + EVE_VALUE()) , T);
  TTS_EXPR_IS( (EVE_VALUE()  + T()        ) , T);
}

TTS_CASE_TPL("Check operator+ behavior", EVE_TYPE)
{
  TTS_EQUAL(+T(1)                         , T(1));
  TTS_EQUAL((T(1)          + T(1)        ), T(2));
  TTS_EQUAL((T(1)          + EVE_VALUE(1)), T(2));
  TTS_EQUAL((EVE_VALUE(1)  + T(1)        ), T(2));
}
