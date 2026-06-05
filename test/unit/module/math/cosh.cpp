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
TTS_CASE_TPL("Check return types of cosh", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::cosh(T()), T);
  TTS_EXPR_IS(eve::cosh(v_t()), v_t);
};

//==================================================================================================
// cosh  tests
//==================================================================================================
auto maxi = []<typename T>(eve::as<T> const&)
{
 return eve::maxlog(eve::as<T>())-eve::log_2(eve::as<T>());
};

auto mini = []<typename T>(eve::as<T> const& tgt) { return -maxi(tgt); };

TTS_CASE_WITH("Check behavior of cosh on wide",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(tts::constant(mini), tts::constant(maxi)),
                            tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1)
{
  using v_t = eve::element_type_t<T>;
  using eve::cosh;
  using eve::sinh;

  TTS_ULP_EQUAL(cosh(a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(std_cosh(e)); }, a0), 2);
  TTS_ULP_EQUAL(cosh(a1), tts::map([](auto e) -> v_t { return static_cast<v_t>(std_cosh(e)); }, a1), 2);
};


//==================================================================================================
// Tests for masked cosh
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::cosh)(eve::wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(mini, maxi),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::cosh[mask](a0),
            eve::if_else(mask, eve::cosh(a0), a0));
};

TTS_CASE_WITH("Check behavior of cosh on wide",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(mini, maxi), tts::randoms(-1, 1)))
<typename T>(T const& a0, T const& a1)
{
   using eve::raw;
   auto prec = tts::prec<T>(0.05, 0.05);
   TTS_RELATIVE_EQUAL(eve::cosh(a0), eve::cosh[raw](a0), prec);
   TTS_RELATIVE_EQUAL(eve::cosh(a1), eve::cosh[raw](a1), prec);
   using eve::fast;
   auto prec1 = tts::prec<T>(0.00009, 0.001);
   TTS_RELATIVE_EQUAL(eve::cosh(a0), eve::cosh[fast](a0), prec1);
   TTS_RELATIVE_EQUAL(eve::cosh(a1), eve::cosh[fast](a1), prec1);

};
