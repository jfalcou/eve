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
//==================================================================================================
TTS_CASE_TPL("Check return types of sind", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sind(T()), T);
  TTS_EXPR_IS(eve::sind(v_t()), v_t);
};

//==================================================================================================
// sind  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of sind on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-45, 45),
                            tts::randoms(-90, 90),
                            tts::randoms(-5000, 5000)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::sind;
  using eve::detail::map;

  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref  = [](auto e) -> v_t { return eve::sinpi(double(e / 180.0l)); };

  TTS_ULP_EQUAL(eve::quarter_circle(sind)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(sind)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(sind)(a1), map(ref, a1), 30);
  TTS_ULP_EQUAL(sind(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(sind(a1), map(ref, a1), 30);
  TTS_ULP_EQUAL(sind(a2), map(ref, a2), 1024);
};

TTS_CASE_TPL("Check return types of sind", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_ULP_EQUAL(eve::sind(T(1)), T(1.745240643728351281941897851631619247225272030714e-2), 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(1)), T(-1.745240643728351281941897851631619247225272030714e-2), 4.0);
  TTS_ULP_EQUAL(eve::sind(T(45.0)), T(0.70710678118654752440084436210484903928483593768847), 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(45.0)), T(-0.70710678118654752440084436210484903928483593768847), 4.0);
  TTS_ULP_EQUAL(eve::sind(T(500.0)), T(0.64278760968653932632264340990726343290755988420567), 4.0);
  TTS_ULP_EQUAL(
      eve::sind(-T(500.0)), T(-0.64278760968653932632264340990726343290755988420567), 4.0);
};


//==================================================================================================
// Tests for masked sind
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sind)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sind[mask](a0),
            eve::if_else(mask, eve::sind(a0), a0));
};
