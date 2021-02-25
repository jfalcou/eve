//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/betainc_inv.hpp>

TTS_CASE_TPL("Check eve::betainc_inv return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::betainc_inv(T()   , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::betainc_inv(T()   , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::betainc_inv(T()   , v_t() , T()   ) , T);
  TTS_EXPR_IS(eve::betainc_inv(T()   , v_t() , v_t() ) , T);
  TTS_EXPR_IS(eve::betainc_inv(v_t() , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::betainc_inv(v_t() , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::betainc_inv(v_t() , v_t() , T()   ) , T);
}

TTS_CASE_TPL("Check eve::betainc_inv behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::betainc_inv(T(0), T(0), T(0)), T(0)  );
  TTS_EQUAL(eve::betainc_inv(T(0), T(0), T(7)), T(0)  );
  TTS_ULP_EQUAL(eve::betainc_inv(T(0.5), T(0.5), T(0.5)), T(0.5) , 30 );
  TTS_ULP_EQUAL(eve::betainc_inv(T(7.651219897728122e-01), T(0.3), T(2)), T(0.2), 30);
}
