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
TTS_CASE_TPL("Check return types of cyl_bessel_kn", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(eve::cyl_bessel_kn(T(), T()), T);
  TTS_EXPR_IS(eve::cyl_bessel_kn(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::cyl_bessel_kn(i_t(), T()), T);
  TTS_EXPR_IS(eve::cyl_bessel_kn(I_t(), T()), T);
  TTS_EXPR_IS(eve::cyl_bessel_kn(i_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::cyl_bessel_kn(I_t(), v_t()), T);
};

//==================================================================================================
//== integral orders
//==================================================================================================
TTS_CASE_WITH("Check behavior of cyl_bessel_kn on wide with integral order",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0), tts::randoms(0.0, 10.0)))
<typename T>([[maybe_unused]] T n, [[maybe_unused]] T a0)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;


  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(0, eve::minf(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(3, eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(0, eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(3, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(0), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(2), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(0), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(2), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

#if defined(__cpp_lib_math_special_functions)
  auto std_cyl_bessel_kn =  [](auto n, auto x)->v_t { return std::cyl_bessel_k(n, double(x)); };
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(3, v_t(1500)), eve::zero(eve::as<v_t>()), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, v_t(50)), std_cyl_bessel_kn(2, v_t(50)), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(0, v_t(10)), std_cyl_bessel_kn(0, v_t(10)), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(1, v_t(5)), std_cyl_bessel_kn(1, v_t(5)), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, v_t(10)), std_cyl_bessel_kn(2, v_t(10)), 35.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(3, v_t(5)), std_cyl_bessel_kn(3, v_t(5)), 35.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(0, v_t(0.1)), std_cyl_bessel_kn(0, v_t(0.1)), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(1, v_t(0.2)), std_cyl_bessel_kn(1, v_t(0.2)), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, v_t(0.1)), std_cyl_bessel_kn(2, v_t(0.1)), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(3, v_t(0.2)), std_cyl_bessel_kn(3, v_t(0.2)), 5.0);

  TTS_ULP_EQUAL(eve::cyl_bessel_kn(10, v_t(8)), std_cyl_bessel_kn(10, v_t(8)), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(20, v_t(8)), std_cyl_bessel_kn(20, v_t(8)), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, v_t(1.9010021686554)),std_cyl_bessel_kn(2, v_t(1.9010021686554)),15.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, v_t(244.708321520116)),std_cyl_bessel_kn(2, v_t(244.708321520116)),15.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(3, v_t(517.048069608611)),std_cyl_bessel_kn(3, v_t(517.048069608611)),15.0);

  TTS_ULP_EQUAL(eve::cyl_bessel_kn(3, T(1500)), eve::zero(eve::as<T>()), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, T(50)), T(std_cyl_bessel_kn(2, v_t(50))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, T(10)), T(std_cyl_bessel_kn(2, v_t(10))), 35.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(3, T(5)), T(std_cyl_bessel_kn(3, v_t(5))), 35.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(0, T(0.1)), T(std_cyl_bessel_kn(0, v_t(0.1))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(1, T(0.2)), T(std_cyl_bessel_kn(1, v_t(0.2))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, T(0.1)), T(std_cyl_bessel_kn(2, v_t(0.1))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(3, T(0.2)), T(std_cyl_bessel_kn(3, v_t(0.2))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(10, T(8)), T(std_cyl_bessel_kn(10, v_t(8))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(20, T(8)), T(std_cyl_bessel_kn(20, v_t(8))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, T(1.9010021686554)),T(std_cyl_bessel_kn(2, v_t(1.9010021686554))),15.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(2, T(244.708321520116)),T(std_cyl_bessel_kn(2, v_t(244.708321520116))),15.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(3, T(517.048069608611)),T(std_cyl_bessel_kn(3, v_t(517.048069608611))),15.0);

  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(3), T(1500)), eve::zero(eve::as<T>()), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(2), T(50)), T(std_cyl_bessel_kn(2, v_t(50))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(2), T(10)), T(std_cyl_bessel_kn(2, v_t(10))), 35.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(3), T(5)), T(std_cyl_bessel_kn(3, v_t(5))), 35.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(2), T(0.1)), T(std_cyl_bessel_kn(2, v_t(0.1))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(3), T(0.2)), T(std_cyl_bessel_kn(3, v_t(0.2))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(10), T(8)), T(std_cyl_bessel_kn(10, v_t(8))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(20), T(8)), T(std_cyl_bessel_kn(20, v_t(8))), 5.0);

  TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(3), T(1500)), eve::zero(eve::as<T>()), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(2), T(50)), T(std_cyl_bessel_kn(2, v_t(50))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(2), T(10)), T(std_cyl_bessel_kn(2, v_t(10))), 35.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(3), T(5)), T(std_cyl_bessel_kn(3, v_t(5))), 35.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(2), T(0.1)), T(std_cyl_bessel_kn(2, v_t(0.1))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(3), T(0.2)), T(std_cyl_bessel_kn(3, v_t(0.2))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(10), T(8)), T(std_cyl_bessel_kn(10, v_t(8))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(I_t(20), T(8)), T(std_cyl_bessel_kn(20, v_t(8))), 5.0);

  TTS_RELATIVE_EQUAL(eve::cyl_bessel_kn(n, a0), map(std_cyl_bessel_kn, n, a0), 1.0e-4);
#else
  TTS_PASS("No support for std::cyl_bessel_k");
#endif
};

//==================================================================================================
//== non integral orders
//==================================================================================================
TTS_CASE_WITH( "Check behavior of cyl_bessel_kn on wide with non integral order"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(0.1, 10.0)
        , tts::randoms(0.0, 10.0))
        )
<typename T>([[maybe_unused]] T n,[[maybe_unused]] T a0 )
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(0.5), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(2.5), eve::inf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(3.5), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(0.5), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(2.5), eve::inf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(3.5), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

#if defined(__cpp_lib_math_special_functions)
  using v_t = eve::element_type_t<T>;
  auto std_cyl_bessel_kn =  [](auto n, auto x)->v_t { return std::cyl_bessel_k(n, double(x)); };
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(v_t(3.5), v_t(1500)), eve::zero(eve::as<v_t>()), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(v_t(2.5), v_t(50)), std_cyl_bessel_kn(v_t(2.5), v_t(50)), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(v_t(2.5), v_t(10)), std_cyl_bessel_kn(v_t(2.5), v_t(10)), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(v_t(3.5), v_t(5)), std_cyl_bessel_kn(v_t(3.5), v_t(5)), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(v_t(2.5), v_t(0.1)), std_cyl_bessel_kn(v_t(2.5), v_t(0.1)), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(v_t(3.5), v_t(0.2)), std_cyl_bessel_kn(v_t(3.5), v_t(0.2)), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(v_t(10.5), v_t(8)), std_cyl_bessel_kn(v_t(10.5), v_t(8)), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(v_t(10.5), v_t(8)), std_cyl_bessel_kn(v_t(10.5), v_t(8)), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(3.5), T(1500)), eve::zero(eve::as<T>()), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(2.5), T(50)), T(std_cyl_bessel_kn(v_t(2.5), v_t(50))), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(2.5), T(10)), T(std_cyl_bessel_kn(v_t(2.5), v_t(10))), 310.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(3.5), T(5)), T(std_cyl_bessel_kn(v_t(3.5), v_t(5))), 310.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(2.5), T(0.1)), T(std_cyl_bessel_kn(v_t(2.5), v_t(0.1))), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(3.5), T(0.2)), T(std_cyl_bessel_kn(v_t(3.5), v_t(0.2))), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(10.5), T(8)), T(std_cyl_bessel_kn(v_t(10.5), v_t(8))), 10.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_kn(T(10.5), T(8)), T(std_cyl_bessel_kn(v_t(10.5), v_t(8))), 10.0);

  TTS_RELATIVE_EQUAL(eve::cyl_bessel_kn(n, a0), map(std_cyl_bessel_kn, n, a0), 1.0e-3);
#else
  TTS_PASS("No support for std::cyl_bessel_k");
#endif
};
