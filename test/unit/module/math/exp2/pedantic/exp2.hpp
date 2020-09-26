//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp2.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <type_traits>

TTS_CASE_TPL("Check eve::pedantic(eve::exp2) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::exp2)(T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::exp2) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(T(1)), T(2), 0.5);
  TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(T(0)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    using elt_t =  eve::element_type_t<T>;
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(eve::minf(eve::as<T>())), T( 0 ) );
    }

    TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(T(-0.)), T(1));
    TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(T(-1)) , T(0.5), 0.5);
    if constexpr( eve::platform::supports_denormals )
    {
      TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(eve::minlog2(eve::as<T>())), T(std::exp2(eve::minlog2(eve::as<elt_t>()))), 0.5);
      TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(eve::prev(eve::minlog2(eve::as<T>()))), T(std::exp2(eve::prev(eve::minlog2(eve::as<elt_t>())))), 0.5);
    }
    TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(eve::minlog2denormal(eve::as<T>())), T(std::exp2(eve::minlog2denormal(eve::as<elt_t>()))), 0);
    TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(eve::prev(eve::minlog2denormal(eve::as<T>()))), T(std::exp2(eve::prev(eve::minlog2denormal(eve::as<elt_t>())))), 0);
  }

}
