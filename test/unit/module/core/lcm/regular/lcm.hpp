//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lcm.hpp>
#include <eve/constant/valmin.hpp>
#include <tts/tests/types.hpp>
#include <numeric>

TTS_CASE_TPL("Check eve::lcm return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::lcm(T(), T()), T);
}

TTS_CASE_TPL("Check eve::lcm behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::lcm(T(22), T( 10)) , T(std::lcm(v_t(22), v_t( 10))));
  TTS_EQUAL(eve::lcm(T(22), T(-10)) , T(std::lcm(v_t(22), v_t(-10))));
  v_t z = eve::valmin(eve::as<v_t>())/2;

  TTS_EQUAL(eve::lcm(T(z), T(2)), T(std::lcm(z, v_t(2))) );
  TTS_EQUAL(eve::lcm(T(z), T(1)), T(std::lcm(z, v_t(1))) );
  TTS_EQUAL(eve::lcm(T(0), T(1)), T(std::lcm(v_t(0), v_t(1))) );
  TTS_EQUAL(eve::lcm(T(1), T(0)), T(std::lcm(v_t(1), v_t(0))) );
}
