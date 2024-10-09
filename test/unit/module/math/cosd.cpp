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

#include <cmath>

//==================================================================================================
// Types tests
// //==================================================================================================
TTS_CASE_TPL( "Check return types of cosd"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::cosd(T())  , T);
  TTS_EXPR_IS( eve::cosd(v_t()), v_t);
};

//==================================================================================================
//== cosd  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of cosd on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-45, 45),
                            tts::randoms(-90, 90),
                            tts::randoms(-5000, 5000)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::cosd;

  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref  = [](auto e) -> v_t { return eve::cospi(double(e / 180.0l)); };

  TTS_ULP_EQUAL(cosd[eve::quarter_circle](a0), tts::map(ref, a0), 2);
  TTS_ULP_EQUAL(cosd(a0), tts::map(ref, a0), 2);
  TTS_ULP_EQUAL(cosd(a1), tts::map(ref, a1), 30);
  TTS_ULP_EQUAL(cosd(a2), tts::map(ref, a2), 420);
};

TTS_CASE_TPL("Check return types of cosd", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_ULP_EQUAL(eve::cosd(T(1)), T(0.9998476951563912391570115588139148516927403105832), 0.5);
  TTS_ULP_EQUAL(eve::cosd(T(-1)), T(0.9998476951563912391570115588139148516927403105832), 0.5);
  TTS_ULP_EQUAL(eve::cosd(T(45.0)), T(0.70710678118654752440084436210484903928483593768847), 0.5);
  TTS_ULP_EQUAL(eve::cosd(T(-45.0)), T(0.70710678118654752440084436210484903928483593768847), 0.5);
  TTS_ULP_EQUAL(eve::cosd(T(135.0)), T(-0.70710678118654752440084436210484903928483593768847), 0.5);
  TTS_ULP_EQUAL(eve::cosd(T(-135.0)), T(-0.70710678118654752440084436210484903928483593768847), 0.5);
  TTS_ULP_EQUAL(eve::cosd(T(-500.0)), T(-0.7660444431189780352023926505554166739358324570804), 3.5);
  TTS_ULP_EQUAL(eve::cosd(T(500.0)), T(-0.7660444431189780352023926505554166739358324570804), 3.5);

  eve::wide wf = {22.5, 45.0, 67.5, 90.0, 112.5, 157.5, 180.0, 202.5};
  TTS_RELATIVE_EQUAL(eve::cosd(wf), eve::cos(eve::deginrad(wf)), 0.01);



};


//==================================================================================================
// Tests for masked cosd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::cosd)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::cosd[mask](a0),
            eve::if_else(mask, eve::cosd(a0), a0));
};
