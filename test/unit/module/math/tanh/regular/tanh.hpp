//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tanh.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::tanh return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::tanh(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::tanh behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::tanh(eve::nan(eve::as<T>()) ), eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::tanh(eve::inf(eve::as<T>()) ), T(1)          );
    TTS_IEEE_EQUAL(eve::tanh(eve::minf(eve::as<T>())), T(-1)         );
  }

  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::tanh(T( 1)), T(std::tanh(v_t(1))) , 0.5);
  TTS_ULP_EQUAL(eve::tanh(T(-1)), T(std::tanh(v_t(-1))), 0.5);

  TTS_IEEE_EQUAL( eve::tanh(T( 0 )), T(0) );
  TTS_IEEE_EQUAL( eve::tanh(T(-0.)), T(0) );

  TTS_EXPECT( eve::all(eve::is_negative(eve::tanh(T(-0.)))) );
  TTS_EXPECT( eve::all(eve::is_positive(eve::tanh(T( 0 )))) );
}
