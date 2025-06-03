//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of lbeta", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::lbeta(T(), T()), T);
  TTS_EXPR_IS(eve::lbeta(T(), v_t()), T);
  TTS_EXPR_IS(eve::lbeta(v_t(), T()), T);
  TTS_EXPR_IS(eve::lbeta(v_t(), v_t()), v_t);
};

//==================================================================================================
// lbeta  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of lbeta on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 10.0), tts::randoms(0.0, 10.0)))
<typename T>([[maybe_unused]] T const& a0, [[maybe_unused]] T const& a1)
{
  using eve::as;
  using eve::lbeta;

#if defined(__cpp_lib_math_special_functions)
  using elt_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(
    eve::lbeta(a0, a1), tts::map([&](auto e, auto f) -> elt_t { return std::log(std::beta(e, f)); }, a0, a1), 64);
  TTS_ULP_EQUAL(lbeta(T(-0.0), T(-0.0)), T(std::log(std::beta(elt_t(-0.0), elt_t(-0.0)))), 0);
  TTS_ULP_EQUAL(lbeta(T(0.0), T(0.0)), T(std::log(std::beta(elt_t(0.0), elt_t(0.0)))), 0);
  TTS_ULP_EQUAL(lbeta(T(1.0), T(1.0)), T(std::log(std::beta(elt_t(1.0), elt_t(1.0)))), 0);
  TTS_ULP_EQUAL(lbeta(T(2.0), T(3.0)), T(std::log(std::beta(elt_t(2.0), elt_t(3.0)))), 0.5);
  TTS_ULP_EQUAL(lbeta(T(2.5), T(3.7)), T(std::log(std::beta(elt_t(2.5), elt_t(3.7)))), 0);
#endif // __cpp_lib_math_special_functions

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(lbeta(eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(lbeta(eve::inf(eve::as<T>()), T(1)), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(lbeta(T(1), eve::inf(eve::as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(lbeta(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(lbeta(eve::minf(eve::as<T>()), T(1)), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(lbeta(T(1), eve::minf(eve::as<T>())), eve::nan(as<T>()), 0);

    TTS_ULP_EQUAL(lbeta(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(lbeta(eve::nan(eve::as<T>()), T(1)), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(lbeta(T(1), eve::nan(eve::as<T>())), eve::nan(as<T>()), 0);
  }
};


//==================================================================================================
// Tests for masked lbeta
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::lbeta)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 10.0),
                            tts::randoms(0.0, 10.0),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::lbeta[mask](a0, a1),
            eve::if_else(mask, eve::lbeta(a0, a1), a0));
};
