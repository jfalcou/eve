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

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sph_bessel_jn", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(eve::sph_bessel_jn(T(), T()), T);
  TTS_EXPR_IS(eve::sph_bessel_jn(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::sph_bessel_jn(i_t(), T()), T);
  TTS_EXPR_IS(eve::sph_bessel_jn(I_t(), T()), T);
  TTS_EXPR_IS(eve::sph_bessel_jn(i_t(), v_t()), v_t);
};

//==================================================================================================
//== integral orders
//==================================================================================================
TTS_CASE_WITH( "Check behavior of sph_bessel_jn on wide with integral order"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::ramp(0), tts::randoms(0.1, 200.0))
        )
  <typename T>(T n, T a0)
{
  using v_t               = eve::element_type_t<T>;
  auto eve__sph_bessel_jn = [](auto n, auto x) { return eve::sph_bessel_jn(n, x); };
  auto std__sph_bessel_jn = [](auto n, auto x) -> v_t
  { return NAMESPACE::sph_bessel(unsigned(n), double(x)); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_jn(2, eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_jn(3, eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, v_t(1500)), std__sph_bessel_jn(3u, v_t(1500)), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, v_t(500)), std__sph_bessel_jn(2u, v_t(500)), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, v_t(10)), std__sph_bessel_jn(2u, v_t(10)), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, v_t(5)), std__sph_bessel_jn(3u, v_t(5)), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, v_t(0.1)), std__sph_bessel_jn(2u, v_t(0.1)), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, v_t(0.2)), std__sph_bessel_jn(3u, v_t(0.2)), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(10, v_t(8)), std__sph_bessel_jn(10u, v_t(8)), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(10, v_t(8)), std__sph_bessel_jn(10u, v_t(8)), 500000.0);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_jn(2, eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_jn(3, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, T(1500)), T(std__sph_bessel_jn(3u, v_t(1500))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, T(500)), T(std__sph_bessel_jn(2u, v_t(500))), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, T(10)), T(std__sph_bessel_jn(2u, v_t(10))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, T(5)), T(std__sph_bessel_jn(3u, v_t(5))), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, T(0.1)), T(std__sph_bessel_jn(2u, v_t(0.1))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, T(0.2)), T(std__sph_bessel_jn(3u, v_t(0.2))), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(10, T(8)), T(std__sph_bessel_jn(10u, v_t(8))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(10, T(8)), T(std__sph_bessel_jn(10u, v_t(8))), 500000.0);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_jn(T(2), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_jn(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(3), T(1500)), T(std__sph_bessel_jn(3u, v_t(1500))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(2), T(500)), T(std__sph_bessel_jn(2u, v_t(500))), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(2), T(10)), T(std__sph_bessel_jn(2u, v_t(10))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(3), T(5)), T(std__sph_bessel_jn(3u, v_t(5))), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(2), T(0.1)), T(std__sph_bessel_jn(2u, v_t(0.1))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(3), T(0.2)), T(std__sph_bessel_jn(3u, v_t(0.2))), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(10), T(8)), T(std__sph_bessel_jn(10u, v_t(8))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(10), T(8)), T(std__sph_bessel_jn(10u, v_t(8))), 500000.0);

  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(2), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(3), T(1500)), T(std__sph_bessel_jn(3u, v_t(1500))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(2), T(500)), T(std__sph_bessel_jn(2u, v_t(500))), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(2), T(10)), T(std__sph_bessel_jn(2u, v_t(10))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(3), T(5)), T(std__sph_bessel_jn(3u, v_t(5))), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(2), T(0.1)), T(std__sph_bessel_jn(2u, v_t(0.1))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(3), T(0.2)), T(std__sph_bessel_jn(3u, v_t(0.2))), 500000.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(10), T(8)), T(std__sph_bessel_jn(10u, v_t(8))), 500000.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(10), T(8)), T(std__sph_bessel_jn(10u, v_t(8))), 500000.0);

  TTS_RELATIVE_EQUAL(eve__sph_bessel_jn(n, a0), map(std__sph_bessel_jn, n, a0), 0.005);
};
