//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/bessel.hpp>

#include <boost/math/special_functions/bessel.hpp>

TTS_CASE_TPL("Check return types of sph_bessel_y1", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::sph_bessel_y1(T(0)), T);
  TTS_EXPR_IS(eve::sph_bessel_y1(v_t(0)), v_t);
};

TTS_CASE_WITH("Check behavior of sph_bessel_y1 on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 0.5),
                            tts::randoms(0.5, 5.5),
                            tts::randoms(5.5, 9.5),
                            tts::randoms(9.5, 60.0)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using v_t               = eve::element_type_t<T>;
  auto eve__sph_bessel_y1 = [](auto x) { return eve::sph_bessel_y1(x); };
  auto boost__sph_bessel_y1 = [](auto x) -> v_t { return boost::math::sph_neumann(1u, double(x)); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_y1(eve::inf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_y1(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_y1(eve::inf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_y1(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  TTS_ULP_EQUAL(eve__sph_bessel_y1(v_t(500)), boost__sph_bessel_y1(v_t(500)), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(v_t(10)), boost__sph_bessel_y1(v_t(10)), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(v_t(5)), boost__sph_bessel_y1(v_t(5)), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(v_t(2)), boost__sph_bessel_y1(v_t(2)), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(v_t(1.5)), boost__sph_bessel_y1(v_t(1.5)), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(v_t(0.5)), boost__sph_bessel_y1(v_t(0.5)), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(v_t(1)), boost__sph_bessel_y1(v_t(1)), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(v_t(0)), eve::minf(eve::as<v_t>()), 0.0);

  TTS_ULP_EQUAL(eve__sph_bessel_y1(T(500)), T(boost__sph_bessel_y1(v_t(500))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(T(10)), T(boost__sph_bessel_y1(v_t(10))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(T(5)), T(boost__sph_bessel_y1(v_t(5))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(T(2)), T(boost__sph_bessel_y1(v_t(2))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(T(1.5)), T(boost__sph_bessel_y1(v_t(1.5))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(T(0.5)), T(boost__sph_bessel_y1(v_t(0.5))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(T(1)), T(boost__sph_bessel_y1(v_t(1))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(T(0)), eve::minf(eve::as<T>()), 0.0);

  TTS_ULP_EQUAL(eve__sph_bessel_y1(a0), map(boost__sph_bessel_y1, a0), 32.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(a1), map(boost__sph_bessel_y1, a1), 32.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(a2), map(boost__sph_bessel_y1, a2), 32.0);
  TTS_ULP_EQUAL(eve__sph_bessel_y1(a3), map(boost__sph_bessel_y1, a3), 32.0);
};


//==================================================================================================
// Tests for masked sph_bessel_y1
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sph_bessel_y1)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::sph_bessel_y1[mask](a0),
            eve::if_else(mask, eve::sph_bessel_y1(a0), a0));
};
