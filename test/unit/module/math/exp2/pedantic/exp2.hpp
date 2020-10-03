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

TTS_CASE("Check eve::pedantic(eve::exp2) return type")
{
  TTS_EXPR_IS(eve::pedantic(eve::exp2)(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE_TPL("Check eve::pedantic(eve::exp2) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(T(1)), T(2), 0.5);
  TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(T(0)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(eve::minf(eve::as<T>())), T( 0 ) );
    }

    TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(T(-0.)), T(1));
    TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(T(-1)) , T(0.5), 0.5);

    using v_t = eve::element_type_t<T>;

    if constexpr( eve::platform::supports_denormals )
    {
      TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(eve::minlog2(eve::as<T>())), T(std::exp2(eve::minlog2(eve::as<v_t>()))), 0.5);
      TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(eve::prev(eve::minlog2(eve::as<T>()))), T(std::exp2(eve::prev(eve::minlog2(eve::as<v_t>())))), 0.5);
    }

    TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(eve::minlog2denormal(eve::as<T>())), T(std::exp2(eve::minlog2denormal(eve::as<v_t>()))), 0);
    TTS_ULP_EQUAL (eve::pedantic(eve::exp2)(eve::prev(eve::minlog2denormal(eve::as<T>()))), T(std::exp2(eve::prev(eve::minlog2denormal(eve::as<v_t>())))), 0);
  }

}
