//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/bessel.hpp>

TTS_CASE_TPL("Check return types of cyl_bessel_y1", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::cyl_bessel_y1(T(0)), T);
  TTS_EXPR_IS(eve::cyl_bessel_y1(v_t(0)), v_t);
};

TTS_CASE_WITH ( "Check behavior of cyl_bessel_y1 on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(0.0, 2000.0)
                              )
              )
<typename T>( [[maybe_unused]] T const& a0 )
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::cyl_bessel_y1(eve::minf(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_y1(eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_y1(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_y1(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_y1(eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_y1(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

#if defined(__cpp_lib_math_special_functions)
  auto std_cyl_bessel_y1 = [](auto x) -> v_t { return std::cyl_neumann(v_t(1), x); };
  TTS_RELATIVE_EQUAL(eve::cyl_bessel_y1(a0), eve::detail::map(std_cyl_bessel_y1, a0), 7e-3);
#else
  TTS_PASS("No support for std::cyl_bessel_y");
#endif
};
