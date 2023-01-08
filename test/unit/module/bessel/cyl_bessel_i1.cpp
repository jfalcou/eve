//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/bessel.hpp>
#if defined(__cpp_lib_math_special_functions)
#define NAMESPACE std
#else
#include <boost/math/special_functions/bessel.hpp>
#define NAMESPACE boost::math
#endif


TTS_CASE_TPL("Check return types of cyl_bessel_i1", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::cyl_bessel_i1(T(0)), T);
  TTS_EXPR_IS(eve::cyl_bessel_i1(v_t(0)), v_t);
};

TTS_CASE_WITH("Check behavior of cyl_bessel_i1 on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.5, 5.5),
                            tts::randoms(5.5, 9.5),
                            tts::randoms(9.5, 20.0)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using v_t               = eve::element_type_t<T>;
  auto eve__cyl_bessel_i1 = [](auto x) { return eve::cyl_bessel_i1(x); };
  auto std__cyl_bessel_i1 = [](auto x) -> v_t { return NAMESPACE::cyl_bessel_i(v_t(1), x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_i1(eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_i1(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_i1(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_i1(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(20)), std__cyl_bessel_i1(v_t(20)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(10)), std__cyl_bessel_i1(v_t(10)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(5)), std__cyl_bessel_i1(v_t(5)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(2)), std__cyl_bessel_i1(v_t(2)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(1.5)), std__cyl_bessel_i1(v_t(1.5)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(0.5)), std__cyl_bessel_i1(v_t(0.5)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(1)), std__cyl_bessel_i1(v_t(1)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(0)), eve::zero(eve::as<v_t>()), 0.0);

  TTS_ULP_EQUAL(eve__cyl_bessel_i1(T(20)), T(std__cyl_bessel_i1(v_t(20))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(T(10)), T(std__cyl_bessel_i1(v_t(10))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(T(5)), T(std__cyl_bessel_i1(v_t(5))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(T(2)), T(std__cyl_bessel_i1(v_t(2))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(T(1.5)), T(std__cyl_bessel_i1(v_t(1.5))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(T(0.5)), T(std__cyl_bessel_i1(v_t(0.5))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(T(1)), T(std__cyl_bessel_i1(v_t(1))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(T(0)), eve::zero(eve::as<T>()), 0.0);

  TTS_ULP_EQUAL(eve__cyl_bessel_i1(a0), map(std__cyl_bessel_i1, a0), 192.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(a1), map(std__cyl_bessel_i1, a1), 192.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(a2), map(std__cyl_bessel_i1, a2), 192.0);
};


//==================================================================================================
// Tests for masked cyl_bessel_i1
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::cyl_bessel_i1)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::cyl_bessel_i1[mask](a0),
            eve::if_else(mask, eve::cyl_bessel_i1(a0), a0));
};
