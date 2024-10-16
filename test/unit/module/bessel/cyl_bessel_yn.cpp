//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/bessel.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of cyl_bessel_yn", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(eve::cyl_bessel_yn(T(), T()), T);
  TTS_EXPR_IS(eve::cyl_bessel_yn(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::cyl_bessel_yn(i_t(), T()), T);
  TTS_EXPR_IS(eve::cyl_bessel_yn(I_t(), T()), T);
  TTS_EXPR_IS(eve::cyl_bessel_yn(i_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::cyl_bessel_yn(I_t(), v_t()), T);
};

// #if defined(__cpp_lib_math_special_functions)

//==================================================================================================
//== integral orders
//==================================================================================================
TTS_CASE_WITH("Check behavior of cyl_bessel_yn on wide with integral order",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0), tts::randoms(0.5, 100.0)))
<typename T>([[maybe_unused]] T n, [[maybe_unused]] T a0)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(0, eve::minf(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(2, eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(3, eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(0, eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(2, eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(3, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(0), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(2), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(0), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(2), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

#if defined(__cpp_lib_math_special_functions)
  auto std_cyl_bessel_yn = [](auto nn, auto xx) -> v_t { return std::cyl_neumann(nn, xx); };
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(3, v_t(1500)), std_cyl_bessel_yn(3, v_t(1500)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(2, v_t(500)), std_cyl_bessel_yn(2, v_t(500)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(0, v_t(10)), std_cyl_bessel_yn(0, v_t(10)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(1, v_t(5)), std_cyl_bessel_yn(1, v_t(5)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(2, v_t(10)), std_cyl_bessel_yn(2, v_t(10)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(3, v_t(5)), std_cyl_bessel_yn(3, v_t(5)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(0, v_t(0.1)), std_cyl_bessel_yn(0, v_t(0.1)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(1, v_t(0.2)), std_cyl_bessel_yn(1, v_t(0.2)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(2, v_t(0.1)), std_cyl_bessel_yn(2, v_t(0.1)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(3, v_t(0.2)), std_cyl_bessel_yn(3, v_t(0.2)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(10, v_t(8)), std_cyl_bessel_yn(10, v_t(8)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(10, v_t(8)), std_cyl_bessel_yn(10, v_t(8)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(3, T(1500)), T(std_cyl_bessel_yn(3, v_t(1500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(2, T(500)), T(std_cyl_bessel_yn(2, v_t(500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(2, T(10)), T(std_cyl_bessel_yn(2, v_t(10))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(3, T(5)), T(std_cyl_bessel_yn(3, v_t(5))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(0, T(0.1)), T(std_cyl_bessel_yn(0, v_t(0.1))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(1, T(0.2)), T(std_cyl_bessel_yn(1, v_t(0.2))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(2, T(0.1)), T(std_cyl_bessel_yn(2, v_t(0.1))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(3, T(0.2)), T(std_cyl_bessel_yn(3, v_t(0.2))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(10, T(8)), T(std_cyl_bessel_yn(10, v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(10, T(8)), T(std_cyl_bessel_yn(10, v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(3), T(1500)), T(std_cyl_bessel_yn(3, v_t(1500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(2), T(500)), T(std_cyl_bessel_yn(2, v_t(500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(2), T(10)), T(std_cyl_bessel_yn(2, v_t(10))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(3), T(5)), T(std_cyl_bessel_yn(3, v_t(5))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(2), T(0.1)), T(std_cyl_bessel_yn(2, v_t(0.1))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(3), T(0.2)), T(std_cyl_bessel_yn(3, v_t(0.2))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(10), T(8)), T(std_cyl_bessel_yn(10, v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(10), T(8)), T(std_cyl_bessel_yn(10, v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(3), T(1500)), T(std_cyl_bessel_yn(3, v_t(1500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(2), T(500)), T(std_cyl_bessel_yn(2, v_t(500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(2), T(10)), T(std_cyl_bessel_yn(2, v_t(10))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(3), T(5)), T(std_cyl_bessel_yn(3, v_t(5))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(2), T(0.1)), T(std_cyl_bessel_yn(2, v_t(0.1))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(3), T(0.2)), T(std_cyl_bessel_yn(3, v_t(0.2))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(10), T(8)), T(std_cyl_bessel_yn(10, v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(I_t(10), T(8)), T(std_cyl_bessel_yn(10, v_t(8))), 20000.0);

  TTS_ULP_EQUAL(eve::cyl_bessel_yn(n, a0), tts::map(std_cyl_bessel_yn, n, a0), 100000.0);
#else
  TTS_PASS("No support for std::cyl_neumann");
#endif
};

//==================================================================================================
//== non integral orders
//==================================================================================================
TTS_CASE_WITH("Check behavior of cyl_bessel_yn on wide with non integral order",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.1, 10.0), tts::randoms(0.5, 100.0)))
<typename T>([[maybe_unused]] T n, [[maybe_unused]] T a0)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(0.5), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(2.5), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(3.5), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

#if defined(__cpp_lib_math_special_functions)
  using v_t = eve::element_type_t<T>;
  auto std_cyl_bessel_yn = [](auto nn, auto xx) -> v_t { return std::cyl_neumann(nn, xx); };
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(3.5), T(1500)), T(std_cyl_bessel_yn(v_t(3.5), v_t(1500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(2.5), T(500)), T(std_cyl_bessel_yn(v_t(2.5), v_t(500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(2.5), T(10)), T(std_cyl_bessel_yn(v_t(2.5), v_t(10))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(3.5), T(5)), T(std_cyl_bessel_yn(v_t(3.5), v_t(5))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(2.5), T(0.1)), T(std_cyl_bessel_yn(v_t(2.5), v_t(0.1))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(3.5), T(0.2)), T(std_cyl_bessel_yn(v_t(3.5), v_t(0.2))), 2.5);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(10.5), T(8)), T(std_cyl_bessel_yn(v_t(10.5), v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_yn(T(10.5), T(8)), T(std_cyl_bessel_yn(v_t(10.5), v_t(8))), 20000.0);

  TTS_RELATIVE_EQUAL(eve::cyl_bessel_yn(n, a0), tts::map(std_cyl_bessel_yn, n, a0), 0.22);
#else
  TTS_PASS("No support for std::cyl_neumann");
#endif
};
