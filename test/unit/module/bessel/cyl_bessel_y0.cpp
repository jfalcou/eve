//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/bessel.hpp>
#include <cmath>


TTS_CASE_TPL("Check return types of cyl_bessel_y0", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::cyl_bessel_y0(T(0)), T);
  TTS_EXPR_IS(eve::cyl_bessel_y0(v_t(0)), v_t);
};

TTS_CASE_WITH("Check behavior of cyl_bessel_y0 on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 20000.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_y0 = [](auto x) { return eve::cyl_bessel_y0(x); };
  auto std__cyl_bessel_y0 = [](auto x) -> v_t { return std::cyl_neumann(v_t(0), x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_y0(eve::minf(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y0(eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y0(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y0(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y0(eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y0(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(v_t(1500)), std__cyl_bessel_y0(v_t(1500)), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(v_t(500)), std__cyl_bessel_y0(v_t(500)), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(v_t(10)), std__cyl_bessel_y0(v_t(10)), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(v_t(5)), std__cyl_bessel_y0(v_t(5)), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(v_t(2)), std__cyl_bessel_y0(v_t(2)), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(v_t(1.5)), std__cyl_bessel_y0(v_t(1.5)), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(v_t(0.5)), std__cyl_bessel_y0(v_t(0.5)), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(v_t(1)), std__cyl_bessel_y0(v_t(1)), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(v_t(0)), eve::minf(eve::as<v_t>()), 0.0);

  TTS_ULP_EQUAL(eve__cyl_bessel_y0(T(1500)), T(std__cyl_bessel_y0(v_t(1500))), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(T(499)), T(std__cyl_bessel_y0(v_t(499))), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(T(10)), T(std__cyl_bessel_y0(v_t(10))), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(T(5)), T(std__cyl_bessel_y0(v_t(5))), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(T(2)), T(std__cyl_bessel_y0(v_t(2))), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(T(1.5)), T(std__cyl_bessel_y0(v_t(1.5))), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(T(0.5)), T(std__cyl_bessel_y0(v_t(0.5))), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(T(1)), T(std__cyl_bessel_y0(v_t(1))), 50000.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y0(T(0)), eve::minf(eve::as<T>()), 0.0);

  TTS_RELATIVE_EQUAL(eve__cyl_bessel_y0(a0), map(std__cyl_bessel_y0, a0), 0.007);
};


//==================================================================================================
// Tests for masked cyl_bessel_y0
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::cyl_bessel_y0)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::cyl_bessel_y0[mask](a0),
            eve::if_else(mask, eve::cyl_bessel_y0(a0), a0));
};
