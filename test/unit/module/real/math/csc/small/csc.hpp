//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::small(eve::csc) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small(eve::csc)(T()), T);
}

TTS_CASE_TPL("Check eve::small(eve::csc) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto ref_csc =  [](auto x){return eve::rec(std::sin(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small(eve::csc)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::small(eve::csc)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::small(eve::csc)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::small(eve::csc)(T( 0 )), T(ref_csc(v_t(0.0))));
  TTS_IEEE_EQUAL(eve::small(eve::csc)(T(-0.)), T(ref_csc(v_t(-0.0))));

  TTS_ULP_EQUAL(eve::small(eve::csc)( T(1)              ), T(ref_csc(1.0))                   , 1.0 );
  TTS_ULP_EQUAL(eve::small(eve::csc)(-T(1)              ), T(ref_csc(-1.0))                  , 1.0 );
  TTS_ULP_EQUAL(eve::small(eve::csc)(-eve::pio_2(eve::as<T>())   ), T(ref_csc(-eve::pio_2(eve::as<v_t>())))    , 1.0 );
  TTS_ULP_EQUAL(eve::small(eve::csc)(-eve::pio_4(eve::as<T>())   ), T(ref_csc(-eve::pio_4(eve::as<v_t>())))    , 0.75);
  TTS_ULP_EQUAL(eve::small(eve::csc)(-eve::pio_4(eve::as<T>())/ 2), T(ref_csc(-eve::pio_4(eve::as<v_t>())/2))  , 0.5 );
  TTS_ULP_EQUAL(eve::small(eve::csc)( eve::pio_4(eve::as<T>())   ), T(ref_csc(eve::pio_4(eve::as<v_t>())))     , 0.5 );
  TTS_ULP_EQUAL(eve::small(eve::csc)( eve::pio_4(eve::as<T>())/ 2), T(ref_csc(eve::pio_4(eve::as<v_t>())/2))   , 0.75);
  TTS_ULP_EQUAL(eve::small(eve::csc)(eve::pio_2(eve::as<T>())    ), T(ref_csc(eve::pio_2(eve::as<v_t>())))     , 1.0 );

  auto z = eve::pio_2(eve::as<v_t>());
  TTS_ULP_EQUAL(eve::small(eve::csc)(T(z)), T(ref_csc(z)), 1);
  z = eve::prev(z);
  TTS_ULP_EQUAL(eve::small(eve::csc)(T(z)), T(ref_csc(z)), 1);
  z = eve::prev(z);
  TTS_ULP_EQUAL(eve::small(eve::csc)(T(z)), T(ref_csc(z)), 1);
  z = eve::prev(z);
  TTS_ULP_EQUAL(eve::small(eve::csc)(T(z)), T(ref_csc(z)), 0.5);
}
