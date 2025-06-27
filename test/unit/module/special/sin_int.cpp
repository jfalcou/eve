//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
TTS_CASE_TPL("Check return types of sin_int", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sin_int(T()), T);
  TTS_EXPR_IS(eve::sin_int(v_t()), v_t);
};

//==================================================================================================
// sin_int  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of sin_int on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sin_int(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::sin_int(eve::inf(eve::as<T>())), eve::pio_2(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::sin_int(eve::minf(eve::as<T>())),-eve::pio_2(eve::as<T>()));
  }

  auto ulp = sizeof(eve::element_type_t<T>) == 8 ? 4.0 : 8.0;
  TTS_IEEE_EQUAL(eve::sin_int(T(0)), T(0));
  TTS_IEEE_EQUAL(eve::sin_int(T(-0.)), T(0));
  TTS_ULP_EQUAL(eve::sin_int(T(1)),            T( 0.946083070367183 ), ulp);
  TTS_ULP_EQUAL(eve::sin_int(T(2)),            T( 1.605412976802695),  ulp);
  TTS_ULP_EQUAL(eve::sin_int(T(4)),            T( 1.7582031389490531), ulp);
  TTS_ULP_EQUAL(eve::sin_int(T(8)),            T( 1.5741868217069421), ulp);
  TTS_ULP_EQUAL(eve::sin_int(T(1.0e10)),       T( 1.5707963267075846), ulp);
  TTS_ULP_EQUAL(eve::sin_int(T(2.5))   ,       T( 1.7785201734438265), ulp);
  TTS_ULP_EQUAL(eve::sin_int(T(0.9241388730)), T( 0.8813991752023395), ulp);

  eve::wide<double, eve::fixed<8>> w {
      0.0, 1.0, 2.0, 4.0, 8.0, 2.0, eve::inf(eve::as<double>()), eve::nan(eve::as<double>())};
  eve::wide<double, eve::fixed<8>> rr {eve::sin_int((0.0)),
                                     eve::sin_int((1.0)),
                                     eve::sin_int((2.0)),
                                     eve::sin_int((4.0)),
                                     eve::sin_int((8.0)),
                                     eve::sin_int((2.0)),
                                     eve::sin_int(eve::inf(eve::as<double>())),
                                     eve::sin_int(eve::nan(eve::as<double>()))};
  TTS_ULP_EQUAL(eve::sin_int(w), rr, 2);
};


//==================================================================================================
// Tests for masked sin_int
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sin_int)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 100.0),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sin_int[mask](a0),
            eve::if_else(mask, eve::sin_int(a0), a0));
};
