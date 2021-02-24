//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::log return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::log(T()), T);
}

TTS_CASE_TPL("Check eve::log behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::log(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log(eve::mone(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log(T( 0 ))         , eve::minf(eve::as<T>()));
  }

  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log(eve::mindenormal(eve::as<T>())), T(std::log(eve::mindenormal(eve::as<v_t>()))));
  }

  TTS_IEEE_EQUAL(eve::log(T( 1)), T( 0 )               );
  TTS_IEEE_EQUAL(eve::log(T( 2)), T(std::log(v_t( 2))) );
  TTS_IEEE_EQUAL(eve::log(T( 8)), T(std::log(v_t( 8))) );
  TTS_IEEE_EQUAL(eve::log(T(64)), T(std::log(v_t(64))) );
}
