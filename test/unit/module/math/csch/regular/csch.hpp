//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csch.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::csch return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::csch(T()), T);
}

TTS_CASE_TPL("Check eve::csch behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::csch(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::csch(eve::inf(eve::as<T>())) , T(0) );
    TTS_IEEE_EQUAL(eve::csch(eve::minf(eve::as<T>())), T(0) );

    TTS_EXPECT(eve::all(eve::is_positive(eve::csch(eve::inf(eve::as<T>())))) );
    TTS_EXPECT(eve::all(eve::is_negative(eve::csch(eve::minf(eve::as<T>())))));
  }

  TTS_ULP_EQUAL(eve::csch(T(1)) , T(eve::rec(std::sinh(v_t(1))) ), 0.5);
  TTS_ULP_EQUAL(eve::csch(T(-1)), T(eve::rec(std::sinh(v_t(-1)))), 0.5);

  TTS_IEEE_EQUAL(eve::csch(T( 0 )), eve::inf(eve::as<T>())  );
  TTS_IEEE_EQUAL(eve::csch(T(-0.)), eve::minf(eve::as<T>()) );
}
