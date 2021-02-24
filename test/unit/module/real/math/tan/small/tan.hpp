//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::small(eve::tan) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small(eve::tan)(T(0)), (T));
}

TTS_CASE_TPL("Check eve::small(eve::tan) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small(eve::tan)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::small(eve::tan)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::small(eve::tan)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::small(eve::tan)(T( 1)), T(std::tan( 1.0)), 0.5);
  TTS_ULP_EQUAL(eve::small(eve::tan)(T(-1)), T(std::tan(-1.0)), 0.5);

  TTS_IEEE_EQUAL( eve::small(eve::tan)(T(0))   , T(0));
  TTS_IEEE_EQUAL( eve::small(eve::tan)(T(-0.)) , T(0));

  TTS_EXPECT(eve::all(eve::is_negative(eve::small(eve::tan)(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::small(eve::tan)(T( 0 )))));

  TTS_ULP_EQUAL(eve::small(eve::tan)( eve::pio_4(eve::as<T>()))  , T(std::tan( eve::pio_4(eve::as<v_t>())))  , 0.5);
  TTS_ULP_EQUAL(eve::small(eve::tan)(-eve::pio_4(eve::as<T>()))  , T(std::tan(-eve::pio_4(eve::as<v_t>())))  , 0.5);
  TTS_ULP_EQUAL(eve::small(eve::tan)( eve::pio_4(eve::as<T>())/2), T(std::tan( eve::pio_4(eve::as<v_t>())/2)), 0.5);
  TTS_ULP_EQUAL(eve::small(eve::tan)(-eve::pio_4(eve::as<T>())/2), T(std::tan(-eve::pio_4(eve::as<v_t>())/2)), 0.5);

  auto z = eve::pio_2(eve::as<v_t>());
  TTS_ULP_EQUAL( eve::small(eve::tan)(T(z)), T(std::tan(eve::pio_2(eve::as<v_t>()))), 5.5);

  z = eve::prev(z);
  TTS_ULP_EQUAL( eve::small(eve::tan)(T(z)), T(std::tan(z)), 1);

  z = eve::prev(z);
  TTS_ULP_EQUAL( eve::small(eve::tan)(T(z)), T(std::tan(z)), 1);

  z = eve::prev(z);
  TTS_ULP_EQUAL( eve::small(eve::tan)(T(z)), T(std::tan(z)), 0.5);
}
