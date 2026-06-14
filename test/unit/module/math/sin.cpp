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
TTS_CASE_TPL("Check return types of sin", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sin(T()), T);
  TTS_EXPR_IS(eve::sin(v_t()), v_t);
};

//==================================================================================================
// sin  tests
//==================================================================================================
auto mquarter_c = []<typename T>(eve::as<T> const& tgt) { return -eve::pio_4(tgt); };
auto quarter_c  = []<typename T>(eve::as<T> const& tgt) { return  eve::pio_4(tgt); };
auto mhalf_c    = []<typename T>(eve::as<T> const& tgt) { return -eve::pio_2(tgt); };
auto half_c     = []<typename T>(eve::as<T> const& tgt) { return  eve::pio_2(tgt); };
auto mfull_c    = []<typename T>(eve::as<T> const& tgt) { return -eve::pi(tgt); };
auto full_c     = []<typename T>(eve::as<T> const& tgt) { return  eve::pi(tgt); };
auto mmed       = []<typename T>(eve::as<T> const& tgt) { return -eve::Rempio2_limit[eve::medium](tgt); };
auto med        = []<typename T>(eve::as<T> const& tgt) { return  eve::Rempio2_limit[eve::medium](tgt); };

TTS_CASE_WITH("Check behavior of sin on wide",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(tts::constant(mquarter_c), tts::constant(quarter_c)),
                            tts::randoms(tts::constant(mhalf_c), tts::constant(half_c)),
                            tts::randoms(tts::constant(mfull_c), tts::constant(full_c)),
                            tts::randoms(tts::constant(mmed), tts::constant(med)),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3, T const& a4)
{
  using eve::sin;

  using v_t = eve::element_type_t<T>;
  auto ref  = [](auto e) -> v_t { return static_cast<v_t>(std_sin(e)); };
  TTS_ULP_EQUAL(sin[eve::quarter_circle](a0), tts::map(ref, a0), 2);
  TTS_ULP_EQUAL(sin[eve::half_circle](a0), tts::map(ref, a0), 2);
  TTS_ULP_EQUAL(sin[eve::half_circle](a1), tts::map(ref, a1), 2);
  TTS_ULP_EQUAL(sin[eve::full_circle](a0), tts::map(ref, a0), 2);
  TTS_ULP_EQUAL(sin[eve::full_circle](a1), tts::map(ref, a1), 2);
  TTS_ULP_EQUAL(sin[eve::full_circle](a2), tts::map(ref, a2), 2);
  TTS_ULP_EQUAL(sin(a0), tts::map(ref, a0), 2);
  TTS_ULP_EQUAL(sin(a1), tts::map(ref, a1), 2);
  TTS_ULP_EQUAL(sin(a2), tts::map(ref, a2), 2);
  TTS_ULP_EQUAL(sin(a3), tts::map(ref, a3), 2);
  TTS_ULP_EQUAL(sin(a4), tts::map(ref, a4), 2);
};


//==================================================================================================
// Tests for masked sin
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sin)(eve::wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sin[mask](a0),
            eve::if_else(mask, eve::sin(a0), a0));
};


TTS_CASE_WITH("Check behavior of sin on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1.5, 1.5), tts::randoms(-1, 1)))
<typename T>(T const& a0, T const& a1)
{
  auto pa1 = a1*eve::pio_2(eve::as(a1));
   using eve::raw;
   using eve::quarter_circle;
   auto prec = tts::prec<T>(0.005, 0.005);
   TTS_RELATIVE_EQUAL(eve::sin(a0), eve::sin[quarter_circle][raw](a0), prec);
   TTS_RELATIVE_EQUAL(eve::sin(pa1), eve::sin[quarter_circle][raw][raw](pa1), prec);
   using eve::fast;
   auto prec1 = tts::prec<T>(0.002, 0.002);
   TTS_RELATIVE_EQUAL(eve::sin(a0), eve::sin[quarter_circle][raw][fast](a0), prec1);
   TTS_RELATIVE_EQUAL(eve::sin(pa1), eve::sin[quarter_circle][raw][fast](pa1), prec1);

};
