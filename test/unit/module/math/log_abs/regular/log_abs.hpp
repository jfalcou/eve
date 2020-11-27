//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log_abs.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::log_abs return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::log_abs(T()), T);
}

TTS_CASE_TPL("Check eve::log_abs behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::log_abs(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log_abs(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log_abs(eve::mone(eve::as<T>())) , eve::zero(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log_abs(T( 0 ))                  , eve::minf(eve::as<T>()));
  }

  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log_abs(eve::mindenormal(eve::as<T>())), T(std::log(eve::mindenormal(eve::as<v_t>()))));
  }

  TTS_IEEE_EQUAL(eve::log_abs(T( 1)), T( 0 )               );
  TTS_IEEE_EQUAL(eve::log_abs(T( 2)), T(std::log(v_t( 2))) );
  TTS_IEEE_EQUAL(eve::log_abs(T( 8)), T(std::log(v_t( 8))) );
  TTS_IEEE_EQUAL(eve::log_abs(T(64)), T(std::log(v_t(64))) );
  TTS_IEEE_EQUAL(eve::log_abs(T( -1)), T( 0 )               );
  TTS_IEEE_EQUAL(eve::log_abs(T( -2)), T(std::log(v_t( 2))) );
  TTS_IEEE_EQUAL(eve::log_abs(T( -8)), T(std::log(v_t( 8))) );
  TTS_IEEE_EQUAL(eve::log_abs(T(-64)), T(std::log(v_t(64))) );
}
