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
#include <boost/math/special_functions/bessel_prime.hpp>

TTS_CASE_TPL("Check return types of cyl_bessel_k0", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::cyl_bessel_k0(T(0)), T);
  TTS_EXPR_IS(eve::cyl_bessel_k0(v_t(0)), v_t);
};

TTS_CASE_WITH("Check behavior of cyl_bessel_k0 on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 0.5),
                            tts::randoms(0.5, 1.5),
                            tts::randoms(1.5, 500.0)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_k0 = [](auto x) { return eve::cyl_bessel_k0(x); };
#if defined(__cpp_lib_math_special_functions)
  auto std__cyl_bessel_k0 = [](auto x) -> v_t { return std::cyl_bessel_k(v_t(0), x); };
#else
  auto std__cyl_bessel_k0 = [](auto x) -> v_t { return boost::math::cyl_bessel_k(v_t(0), x); };
#endif
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::inf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::zero(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::inf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::zero(eve::as<T>())), eve::inf(eve::as<T>()), 0);
  }
  TTS_IEEE_EQUAL(eve__cyl_bessel_k0(v_t(-1)), eve::nan(eve::as<v_t>()));
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(500)), std__cyl_bessel_k0(v_t(500)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(10)), std__cyl_bessel_k0(v_t(10)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(5)), std__cyl_bessel_k0(v_t(5)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(2)), std__cyl_bessel_k0(v_t(2)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(1.5)), std__cyl_bessel_k0(v_t(1.5)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(0.5)), std__cyl_bessel_k0(v_t(0.5)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(0.05)), std__cyl_bessel_k0(v_t(0.05)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(1)), std__cyl_bessel_k0(v_t(1)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(0)), eve::inf(eve::as<v_t>()), 0.0);

  TTS_IEEE_EQUAL(eve__cyl_bessel_k0(T(-1)), eve::nan(eve::as<T>()));
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(T(500)), T(std__cyl_bessel_k0(v_t(500))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(T(10)), T(std__cyl_bessel_k0(v_t(10))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(T(5)), T(std__cyl_bessel_k0(v_t(5))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(T(2)), T(std__cyl_bessel_k0(v_t(2))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(T(1.5)), T(std__cyl_bessel_k0(v_t(1.5))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(T(0.5)), T(std__cyl_bessel_k0(v_t(0.5))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(T(1)), T(std__cyl_bessel_k0(v_t(1))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(T(0)), eve::inf(eve::as<T>()), 0.0);

  TTS_ULP_EQUAL(eve__cyl_bessel_k0(a0), map(std__cyl_bessel_k0, a0), 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(a1), map(std__cyl_bessel_k0, a1), 10.0);
  TTS_RELATIVE_EQUAL(eve__cyl_bessel_k0(a2), map(std__cyl_bessel_k0, a2), 0.001);
};


//==================================================================================================
// Tests for masked cyl_bessel_k0
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::cyl_bessel_k0)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::cyl_bessel_k0[mask](a0),
            eve::if_else(mask, eve::cyl_bessel_k0(a0), a0));
};
