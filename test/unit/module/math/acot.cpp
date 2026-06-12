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
TTS_CASE_TPL("Check return types of acot", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::acot(T()), T);
  TTS_EXPR_IS(eve::acot(v_t()), v_t);
};

//==================================================================================================
// acot  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of acot on wide",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(-1000., +1000.)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acot(a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(std_atan(1/e)); }, a0), 2);
};


//==================================================================================================
// Tests for masked acot
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::acot)(eve::wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::acot[mask](a0),
            eve::if_else(mask, eve::acot(a0), a0));
};


TTS_CASE_WITH("Check behavior of acot on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10, 10), tts::randoms(-1, 1)))
<typename T>(T const& a0, T const& a1)
{
   using eve::raw;
   auto prec = tts::prec<T>(0.005, 0.005);
   TTS_RELATIVE_EQUAL(eve::acot(a0), eve::acot[raw](a0), prec);
   TTS_RELATIVE_EQUAL(eve::acot(a1), eve::acot[raw](a1), prec);
   using eve::fast;
   auto prec1 = tts::prec<T>(0.00002, 0.00002);
   TTS_RELATIVE_EQUAL(eve::acot(a0), eve::acot[fast](a0), prec1);
   TTS_RELATIVE_EQUAL(eve::acot(a1), eve::acot[fast](a1), prec1);

};
