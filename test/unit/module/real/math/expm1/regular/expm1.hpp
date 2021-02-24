//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/expm1.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::expm1 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::expm1(T(0)), T);
}

TTS_CASE_TPL("Check eve::expm1 behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::expm1(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::expm1(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::expm1(eve::minf(eve::as<T>())), T(-1)        );
  }

  TTS_EXPECT(eve::all(eve::is_negative(eve::expm1(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::expm1(T( 0.)))));

  TTS_IEEE_EQUAL(eve::expm1(T(0))   , T(0) );
  TTS_IEEE_EQUAL(eve::expm1(T(-0.)) , T(0) );

  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::expm1(T(1))    , T(std::expm1(v_t(1))), 0.5);
  TTS_ULP_EQUAL(eve::expm1(T(-1))   ,T(std::expm1(v_t(-1))), 0.5);
}
