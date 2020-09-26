//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp10.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::pedantic(eve::exp10) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::exp10)(T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::exp10) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL ( eve::pedantic(eve::exp10)(T(1)), T(10), 0.5);
  TTS_IEEE_EQUAL( eve::pedantic(eve::exp10)(T(0)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    using elt_t =  eve::element_type_t<T>;
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp10)(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp10)(eve::inf(eve::as<T>())) , (eve::inf(eve::as<T>())) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp10)(eve::minf(eve::as<T>())), (T( 0 )) );
    }

    TTS_ULP_EQUAL ( eve::pedantic(eve::exp10)(T(-1)) , T(0.1), 0.5);
    TTS_IEEE_EQUAL( eve::pedantic(eve::exp10)(T(-0.)), T(1));
    if constexpr( eve::platform::supports_denormals )
    {
      TTS_ULP_EQUAL (eve::pedantic(eve::exp10)(eve::minlog10(eve::as<T>())), T(std::exp(elt_t(std::log(10.0))*eve::minlog10(eve::as<elt_t>()))), 256);
      TTS_ULP_EQUAL (eve::pedantic(eve::exp10)(eve::prev(eve::minlog10(eve::as<T>()))), T(std::exp(elt_t(std::log(10.0))*eve::prev(eve::minlog10(eve::as<elt_t>())))), 256);
    }
    TTS_ULP_EQUAL (eve::pedantic(eve::exp10)(eve::minlog10denormal(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL (eve::pedantic(eve::exp10)(eve::prev(eve::minlog10denormal(eve::as<T>()))), T(0), 0);
  }
}
