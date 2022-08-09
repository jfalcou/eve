//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/bessel.hpp>

#include <boost/math/special_functions/airy.hpp>

TTS_CASE_TPL("Check return types of airy_bi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::airy_bi(T(0)), T);
  TTS_EXPR_IS(eve::airy_bi(v_t(0)), v_t);
};

TTS_CASE_WITH("Check behavior of airy_bi on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-20.0, 0.0), tts::randoms(0.0, 20.0)))
<typename T>(T a0, T a1)
{
  using v_t         = eve::element_type_t<T>;
  v_t  abstol       = 1000 * eve::eps(eve::as<v_t>());
  auto eve__airy_bi = [](auto x) { return eve::airy_bi(x); };
  auto std__airy_bi = [](auto x) -> v_t { return boost::math::airy_bi(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__airy_bi(eve::minf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__airy_bi(eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__airy_bi(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__airy_bi(eve::minf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__airy_bi(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__airy_bi(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  TTS_ULP_EQUAL(eve__airy_bi(v_t(1500)), eve::inf(eve::as<v_t>()), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(500)), eve::inf(eve::as<v_t>()), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(10)), std__airy_bi(v_t(10)), 13.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(5)), std__airy_bi(v_t(5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(2)), std__airy_bi(v_t(2)), 35.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(1.5)), std__airy_bi(v_t(1.5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(0.5)), std__airy_bi(v_t(0.5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(1)), std__airy_bi(v_t(1)), 2.5);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(0)), std__airy_bi(v_t(0)), 1.5);

  TTS_ULP_EQUAL(eve__airy_bi(T(1500)), eve::inf(eve::as<T>()), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(500)), eve::inf(eve::as<T>()), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(10)), T(std__airy_bi(v_t(10))), 13.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(5)), T(std__airy_bi(v_t(5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(2)), T(std__airy_bi(v_t(2))), 36.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(1.5)), T(std__airy_bi(v_t(1.5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(0.5)), T(std__airy_bi(v_t(0.5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(1)), T(std__airy_bi(v_t(1))), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(0)), T(0.614926627446001), 0.5);

  TTS_ABSOLUTE_EQUAL(eve__airy_bi(v_t(-1500)), std__airy_bi(v_t(-1500)), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_bi(v_t(-500)), std__airy_bi(v_t(-500)), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_bi(v_t(-10)), std__airy_bi(v_t(-10)), abstol);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(-5)), std__airy_bi(v_t(-5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(-2)), std__airy_bi(v_t(-2)), 35.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(-1.5)), std__airy_bi(v_t(-1.5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(-0.5)), std__airy_bi(v_t(-0.5)), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(v_t(-1)), std__airy_bi(v_t(-1)), 7.5);

  TTS_ABSOLUTE_EQUAL(eve__airy_bi(T(-1500)), T(std__airy_bi(v_t(-1500))), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_bi(T(-500)), T(std__airy_bi(v_t(-500))), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_bi(T(-10)), T(std__airy_bi(v_t(-10))), abstol);
  TTS_ULP_EQUAL(eve__airy_bi(T(-5)), T(std__airy_bi(v_t(-5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(-2)), T(std__airy_bi(v_t(-2))), 36.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(-1.5)), T(std__airy_bi(v_t(-1.5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(-0.5)), T(std__airy_bi(v_t(-0.5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_bi(T(-1)), T(std__airy_bi(v_t(-1))), 10.0);

  TTS_ABSOLUTE_EQUAL(eve__airy_bi(a0), map(std__airy_bi, a0), abstol);
  TTS_RELATIVE_EQUAL(eve__airy_bi(a1), map(std__airy_bi, a1), 0.001);
};
