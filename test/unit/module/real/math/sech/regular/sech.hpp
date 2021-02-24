//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sech.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/all.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::sech return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sech(T()), T);
}

TTS_CASE_TPL("Check eve::sech behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sech(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::sech(eve::inf(eve::as<T>())) , T(0)          );
    TTS_IEEE_EQUAL(eve::sech(eve::minf(eve::as<T>())), T(0)          );

    TTS_EXPECT(eve::all(eve::is_positive(eve::sech(eve::inf(eve::as<T>())))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::sech(eve::minf(eve::as<T>())))));
  }

  TTS_ULP_EQUAL(eve::sech( T(1)), T(eve::rec(std::cosh(v_t(1))))  , 0.5);
  TTS_ULP_EQUAL(eve::sech(-T(1)), T(eve::rec(std::cosh(v_t(-1)))) , 0.5);

  TTS_IEEE_EQUAL(eve::sech(T( 0 )), T(1));
  TTS_IEEE_EQUAL(eve::sech(T(-0.)), T(1));
}
