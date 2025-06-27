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
TTS_CASE_TPL("Check return types of cos_int", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::cos_int(T()), T);
  TTS_EXPR_IS(eve::cos_int(v_t()), v_t);
};

//==================================================================================================
// cos_int  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of cos_int on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
//   if constexpr( sizeof(eve::element_type_t<T>) == 8 )
//   {
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cos_int(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::cos_int(eve::inf(eve::as<T>())), eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::cos_int(eve::minf(eve::as<T>())),eve::nan(eve::as<T>()));
  }

  auto ulp = sizeof(eve::element_type_t<T>) == 8 ? 4.0 : 8.0;
  TTS_IEEE_EQUAL(eve::cos_int(T(0)), eve::minf(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::cos_int(T(-0.)), eve::minf(eve::as<T>()));
  TTS_ULP_EQUAL(eve::cos_int(T(1)),            T(  0.33740392290096805   ), ulp);
  TTS_ULP_EQUAL(eve::cos_int(T(2)),            T(  0.42298082877486487   ),  ulp);
  TTS_ULP_EQUAL(eve::cos_int(T(4)),            T( -0.1409816978869303    ), ulp);
  TTS_ULP_EQUAL(eve::cos_int(T(8)),            T(  0.12243388253200957   ), ulp);
  TTS_ULP_EQUAL(eve::cos_int(T(ulpe10)),       T( -4.8750602517482264e-11), ulp);
  TTS_ULP_EQUAL(eve::cos_int(T(2.5))   ,       T(  0.2858711963653835    ), ulp);
  TTS_ULP_EQUAL(eve::cos_int(T(0.9241388730)), T(  0.29226964555971935   ), ulp);

  eve::wide<double, eve::fixed<8>> w {
      0.0, 1.0, 2.0, 4.0, 8.0, 2.0, eve::inf(eve::as<double>()), eve::nan(eve::as<double>())};
  eve::wide<double, eve::fixed<8>> rr {eve::cos_int((0.0)),
                                     eve::cos_int((1.0)),
                                     eve::cos_int((2.0)),
                                     eve::cos_int((4.0)),
                                     eve::cos_int((8.0)),
                                     eve::cos_int((2.0)),
                                     eve::cos_int(eve::inf(eve::as<double>())),
                                     eve::cos_int(eve::nan(eve::as<double>()))};
  TTS_ULP_EQUAL(eve::cos_int(w), rr, 2);
//  };
};



//==================================================================================================
// Tests for masked cos_int
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::cos_int)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 100.0),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::cos_int[mask](a0),
            eve::if_else(mask, eve::cos_int(a0), a0));
};
