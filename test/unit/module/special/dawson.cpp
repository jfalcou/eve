//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of dawson", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::dawson(T()), T);
  TTS_EXPR_IS(eve::dawson(v_t()), v_t);
};

//==================================================================================================
// dawson  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of dawson on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::dawson(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::dawson(eve::inf(eve::as<T>())), T(0));
    TTS_IEEE_EQUAL(eve::dawson(eve::minf(eve::as<T>())), T(0));
  }

  TTS_IEEE_EQUAL(eve::dawson(T(0)), T(0));
  TTS_IEEE_EQUAL(eve::dawson(T(-0.)), T(0));
  TTS_ULP_EQUAL(eve::dawson(T(1)), T(0.53807950691276840161), 0.5);
  TTS_ULP_EQUAL(eve::dawson(T(2)), T(0.30134038892379196603466443928642), 0.5);
  TTS_ULP_EQUAL(eve::dawson(T(4)), T(1.293480012360051e-01), 0.5);
  TTS_ULP_EQUAL(eve::dawson(T(8)), T(6.300019870755338e-02), 0.5);
  TTS_ULP_EQUAL(eve::dawson(T(1.0e10)), T(5.000000000000000e-11), 0.5);
  TTS_ULP_EQUAL(eve::dawson(T(2.5)), T(2.230837221674355e-01), 1.0);
  TTS_ULP_EQUAL(eve::dawson(T(0.9241388730)), T(5.410442246351818e-01), 0.5);

  TTS_IEEE_EQUAL(eve::dawson(T(0)), T(0));
  TTS_IEEE_EQUAL(eve::dawson(T(-0.)), T(0));
  TTS_ULP_EQUAL(eve::dawson(T(1)), T(0.53807950691276840161), 0.5);
  TTS_ULP_EQUAL(eve::dawson(T(2)), T(0.30134038892379196603466443928642), 0.5);
  TTS_ULP_EQUAL(eve::dawson(T(4)), T(1.293480012360051e-01), 0.5);
  TTS_ULP_EQUAL(eve::dawson(T(8)), T(6.300019870755338e-02), 0.5);
  TTS_ULP_EQUAL(eve::dawson(T(1.0e10)), T(5.000000000000000e-11), 0.5);
  TTS_ULP_EQUAL(eve::dawson(T(2.5)), T(2.230837221674355e-01), 1.0);
  TTS_ULP_EQUAL(eve::dawson(T(0.9241388730)), T(5.410442246351818e-01), 0.5);

  eve::wide<float, eve::fixed<8>> w {
      0.0f, 1.0f, 2.0f, 4.0f, 8.0f, 2.0, eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};
  eve::wide<float, eve::fixed<8>> r {eve::dawson((0.0f)),
                                     eve::dawson((1.0f)),
                                     eve::dawson((2.0f)),
                                     eve::dawson((4.0f)),
                                     eve::dawson((8.0f)),
                                     eve::dawson((2.0f)),
                                     eve::dawson(eve::inf(eve::as<float>())),
                                     eve::dawson(eve::nan(eve::as<float>()))};
  TTS_ULP_EQUAL(eve::dawson(w), r, 2);
};
