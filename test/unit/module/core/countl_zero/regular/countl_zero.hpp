//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/countl_zero.hpp>

TTS_CASE_TPL("Check countl_zero return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::countl_zero(T()), T);
}

TTS_CASE_TPL("Check eve::countl_zero behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::countl_zero(T(0)), T(sizeof(v_t) * 8     ));
  TTS_EQUAL(eve::countl_zero(T(3)), T(sizeof(v_t) * 8 - 2 ));
  TTS_EQUAL(eve::countl_zero(T(5)), T(sizeof(v_t) * 8 - 3 ));
  TTS_EQUAL(eve::countl_zero(T(6)), T(sizeof(v_t) * 8 - 3 ));
  TTS_EQUAL(eve::countl_zero(T(9)), T(sizeof(v_t) * 8 - 4 ));
}
