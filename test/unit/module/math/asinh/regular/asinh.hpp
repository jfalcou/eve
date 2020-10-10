//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asinh.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::asinh return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::asinh(T(0)), T);
}

TTS_CASE_TPL("Check eve::asinh behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asinh(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asinh(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::asinh(eve::minf(eve::as<T>())), eve::minf(eve::as<T>()), 0);
  }

  TTS_EXPECT(eve::all(eve::is_negative(eve::asinh(eve::minf(eve::as<T>())))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::asinh(eve::inf(eve::as<T>())))));

  TTS_ULP_EQUAL(eve::asinh(T(-0.5)),  T(std::asinh(v_t(-0.5))), 0.5 );
  TTS_ULP_EQUAL(eve::asinh(T( 0. )),  T( 0 )                  , 0   );
  TTS_ULP_EQUAL(eve::asinh(T( 0.5)),  T(std::asinh(v_t(0.5))) , 0.5 );
  TTS_ULP_EQUAL(eve::asinh(T( 2. )),  T(std::asinh(v_t(2)))   , 0.5 );
}
