//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::restricted(eve::csc) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::csc(T()), T);
}

TTS_CASE_TPL("Check eve::restricted(eve::csc) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto ref_csc =  [](auto x){return eve::rec(std::sin(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::csc)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::csc)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::csc)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted(eve::csc)(T( 0 )) , T(ref_csc(v_t(0.0)))  );
  TTS_IEEE_EQUAL(eve::restricted(eve::csc)(T(-0.)) , T(ref_csc(v_t(-0.0))) );
  TTS_IEEE_EQUAL(eve::restricted(eve::csc)( T(1) ) , eve::nan(eve::as<T>())         );
  TTS_IEEE_EQUAL(eve::restricted(eve::csc)(-T(1) ) , eve::nan(eve::as<T>())         );

  TTS_ULP_EQUAL(eve::restricted(eve::csc)(-eve::pio_4(eve::as<T>()) ) , T(ref_csc(-eve::pio_4(eve::as<v_t>()))), 0.75);
  TTS_ULP_EQUAL(eve::restricted(eve::csc)( eve::pio_4(eve::as<T>()) ) , T(ref_csc(eve::pio_4(eve::as<v_t>()))) , 0.75);
}
