//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log10.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::log10 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::log10(T()), T);
}

TTS_CASE_TPL("Check eve::log10 behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::log10(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log10(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log10(eve::mone(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log10(T( 0 ))         , eve::minf(eve::as<T>()));
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log10(eve::mindenormal(eve::as<T>())), T(std::log10(eve::mindenormal(eve::as<v_t>()))));
  }

  TTS_IEEE_EQUAL(eve::log10(T(1)      ), T(0) );
  TTS_IEEE_EQUAL(eve::log10(T(10)     ), T(1) );
  TTS_IEEE_EQUAL(eve::log10(T(1000)   ), T(3) );
  TTS_IEEE_EQUAL(eve::log10(T(1000000)), T(6) );
}
