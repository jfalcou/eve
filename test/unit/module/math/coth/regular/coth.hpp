//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/coth.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::coth return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::coth(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::coth behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::coth(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::coth(eve::inf(eve::as<T>())) , T( 1)         );
    TTS_IEEE_EQUAL(eve::coth(eve::minf(eve::as<T>())), T(-1)         );
  }

  TTS_ULP_EQUAL (eve::coth(T( 1 )), T(eve::rec(std::tanh(v_t(1)))), 0.5);
  TTS_ULP_EQUAL (eve::coth(T(-1 )), T(eve::rec(std::tanh(v_t(-1)))), 0.5);
  TTS_IEEE_EQUAL(eve::coth(T( 0 )), eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::coth(T(-0.)), eve::minf(eve::as<T>()));
}
