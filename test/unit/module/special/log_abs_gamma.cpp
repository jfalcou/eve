//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of log_abs_gamma", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::log_abs_gamma(T()), T);
  TTS_EXPR_IS(eve::log_abs_gamma(v_t()), v_t);
};

//==================================================================================================
// log_abs_gamma  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of log_abs_gamma on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10000.0, 10000.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using eve::log_abs_gamma;
  TTS_RELATIVE_EQUAL(log_abs_gamma(a0), map([&](auto e) -> v_t { return std::lgamma(e); }, a0), 5e-2);

  TTS_ULP_EQUAL(log_abs_gamma(T(0.5)), T(std::lgamma(v_t(0.5))), 1.);
  TTS_ULP_EQUAL(log_abs_gamma(T(-35)), T(std::lgamma(v_t(-35))), 0.5);
  TTS_ULP_EQUAL(log_abs_gamma(T(-75.3)), T(std::lgamma(v_t(-75.3))), 0.5);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(log_abs_gamma(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(log_abs_gamma(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(log_abs_gamma(eve::minf(eve::as<T>())), eve::inf(eve::as<T>()));
  }
  TTS_IEEE_EQUAL(log_abs_gamma(T(0)), eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(log_abs_gamma(T(-0.)), eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(log_abs_gamma(T(1)), T(0));
  TTS_IEEE_EQUAL(log_abs_gamma(T(2)), T(0));
  TTS_IEEE_EQUAL(log_abs_gamma(T(3)), T(std::log(2.0)));
  TTS_IEEE_EQUAL(log_abs_gamma(T(5)), T(std::log(24.0)));
};


//==================================================================================================
// Tests for masked log_abs_gamma
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::log_abs_gamma)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10000.0, 10000.0),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::log_abs_gamma[mask](a0),
                 eve::if_else(mask, eve::log_abs_gamma(a0), a0));
};
