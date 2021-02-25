//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
