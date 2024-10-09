//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/bessel.hpp>

TTS_CASE_TPL("Check return types of cyl_bessel_i0", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::cyl_bessel_i0(T(0)), T);
  TTS_EXPR_IS(eve::cyl_bessel_i0(v_t(0)), v_t);
};

TTS_CASE_WITH ( "Check behavior of cyl_bessel_i0 on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(0.5, 5.5),tts::randoms(5.5, 9.5),tts::randoms(9.5, 20.0))
              )
<typename T>([[maybe_unused]] T const& a0, [[maybe_unused]] T const& a1, [[maybe_unused]] T const& a2)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::cyl_bessel_i0(eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_i0(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_i0(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_i0(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

#if defined(__cpp_lib_math_special_functions)
  auto std_cyl_bessel_i0 = [](auto x) -> v_t { return std::cyl_bessel_i(v_t(0), x); };
  TTS_ULP_EQUAL(eve::cyl_bessel_i0(a0), tts::map(std_cyl_bessel_i0, a0), 16.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_i0(a1), tts::map(std_cyl_bessel_i0, a1), 16.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_i0(a2), tts::map(std_cyl_bessel_i0, a2), 16.0);
#else
  TTS_PASS("No support for std::cyl_bessel_i");
#endif
};

//==================================================================================================
// Tests for masked cyl_bessel_i0
//==================================================================================================
TTS_CASE_WITH ( "Check behavior of eve::masked(eve::cyl_bessel_i0)(eve::wide)"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3))
              )
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::cyl_bessel_i0[mask](a0), eve::if_else(mask, eve::cyl_bessel_i0(a0), a0));
};
