//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fms.hpp>

TTS_CASE_TPL("Check eve::fms return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::fms(T()   , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::fms(T()   , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::fms(T()   , v_t() , T()   ) , T);
  TTS_EXPR_IS(eve::fms(T()   , v_t() , v_t() ) , T);
  TTS_EXPR_IS(eve::fms(v_t() , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::fms(v_t() , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::fms(v_t() , v_t() , T()   ) , T);
}

TTS_CASE_TPL("Check eve::fms behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::fms(T(0), T(0), T(0)), T( 0));
  TTS_EQUAL(eve::fms(T(2), T(5), T(7)), T( 3));
  TTS_EQUAL(eve::fms(T(8), T(5), T(7)), T(33));
}

