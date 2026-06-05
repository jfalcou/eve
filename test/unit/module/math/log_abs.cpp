//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "std_proxy.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of log_abs", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::log_abs(T()), T);
  TTS_EXPR_IS(eve::log_abs(v_t()), v_t);
};

//==================================================================================================
// log_abs  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of log_abs on wide",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(-1, 1)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::log_abs(a0), tts::map([](auto e) -> v_t { return eve::convert(std_log(std_abs(e)), eve::as<v_t>()); }, a0), 2);
};


//==================================================================================================
// Tests for masked log_abs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::log_abs)(eve::wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::log_abs[mask](a0),
            eve::if_else(mask, eve::log_abs(a0), a0));
};


//==================================================================================================
// Tests for fast and raw  log_abs
//==================================================================================================
TTS_CASE_WITH("Check behavior of log_abs on wide",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::eps, eve::valmax), tts::randoms(0.5, 2.01)))
<typename T>(T const& a0, T const& a1)
{
   using eve::raw;
    auto prec = tts::prec<T>(0.07, 0.07);
   TTS_RELATIVE_EQUAL(eve::log_abs(a0), eve::log_abs[raw](a0), prec);
   TTS_RELATIVE_EQUAL(eve::log_abs(a1), eve::log_abs[raw](a1), prec);
   using eve::fast;;
   auto prec1 = tts::prec<T>(0.0009, 0.0009);
   TTS_RELATIVE_EQUAL(eve::log_abs(a0), eve::log_abs[fast](a0), prec1);
   TTS_RELATIVE_EQUAL(eve::log_abs(a1), eve::log_abs[fast](a1), prec1);

};
