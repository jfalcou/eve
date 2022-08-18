//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/bessel.hpp>
#include <eve/module/core.hpp>

#include <boost/math/special_functions/airy.hpp>

TTS_CASE_TPL("Check return types of airy_ai", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::airy_ai(T(0)), T);
  TTS_EXPR_IS(eve::airy_ai(v_t(0)), v_t);
};

TTS_CASE_WITH("Check behavior of airy_ai on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-20.0, 0.0), tts::randoms(0.0, 20.0)))
<typename T>(T a0, T a1)
{
  using v_t         = eve::element_type_t<T>;
  v_t  abstol       = 1000 * eve::eps(eve::as<v_t>());
  auto eve__airy_ai = [](auto x) { return eve::airy_ai(x); };
  auto std__airy_ai = [](auto x) -> v_t { return boost::math::airy_ai(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__airy_ai(eve::minf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::minf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  TTS_ULP_EQUAL(eve__airy_ai(v_t(1500)), std__airy_ai(v_t(1500)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(500)), std__airy_ai(v_t(500)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(10)), std__airy_ai(v_t(10)), 13.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(5)), std__airy_ai(v_t(5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(2)), std__airy_ai(v_t(2)), 35.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(1.5)), std__airy_ai(v_t(1.5)), 11.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(0.5)), std__airy_ai(v_t(0.5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(1)), std__airy_ai(v_t(1)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(0)), v_t(0.355028053887817), 0.5);

  TTS_ULP_EQUAL(eve__airy_ai(T(1500)), T(std__airy_ai(v_t(1500))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(500)), T(std__airy_ai(v_t(500))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(10)), T(std__airy_ai(v_t(10))), 13.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(5)), T(std__airy_ai(v_t(5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(2)), T(std__airy_ai(v_t(2))), 37.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(1.5)), T(std__airy_ai(v_t(1.5))), 11.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(0.5)), T(std__airy_ai(v_t(0.5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(1)), T(std__airy_ai(v_t(1))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(0)), T(0.355028053887817), 0.5);

  TTS_ABSOLUTE_EQUAL(eve__airy_ai(v_t(-1500)), std__airy_ai(v_t(-1500)), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_ai(v_t(-500)), std__airy_ai(v_t(-500)), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_ai(v_t(-10)), std__airy_ai(v_t(-10)), abstol);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(-5)), std__airy_ai(v_t(-5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(-2)), std__airy_ai(v_t(-2)), 35.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(-1.5)), std__airy_ai(v_t(-1.5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(-0.5)), std__airy_ai(v_t(-0.5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(-1)), std__airy_ai(v_t(-1)), 10.0);

  TTS_ABSOLUTE_EQUAL(eve__airy_ai(T(-1500)), T(std__airy_ai(v_t(-1500))), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_ai(T(-500)), T(std__airy_ai(v_t(-500))), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_ai(T(-10)), T(std__airy_ai(v_t(-10))), abstol);
  TTS_ULP_EQUAL(eve__airy_ai(T(-5)), T(std__airy_ai(v_t(-5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(-2)), T(std__airy_ai(v_t(-2))), 36.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(-1.5)), T(std__airy_ai(v_t(-1.5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(-0.5)), T(std__airy_ai(v_t(-0.5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(T(-1)), T(std__airy_ai(v_t(-1))), 10.0);

  TTS_ABSOLUTE_EQUAL(eve__airy_ai(a0), map(std__airy_ai, a0), 0.0005);
  TTS_RELATIVE_EQUAL(eve__airy_ai(a1), map(std__airy_ai, a1), 0.0005);
};


//==================================================================================================
// Tests for masked airy_ai
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::airy_ai)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::airy_ai[mask](a0),
            eve::if_else(mask, eve::airy_ai(a0), a0));
};
