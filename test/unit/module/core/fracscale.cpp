//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of fracscale", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::fracscale(T(), int()), T);
  TTS_EXPR_IS(eve::fracscale(v_t(), int()), v_t);
};

//==================================================================================================
//== fracscale simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fracscale(wide) and diff on  floating types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100.0, 100.0)))
<typename T>(T const& a0)
{

  using eve::rec;
  using eve::sqr;
  TTS_ULP_EQUAL(eve::fracscale(a0, 4),
                tts::map([&](auto e) { return e - eve::ldexp(eve::nearest(eve::ldexp(e, 4)), -4); }, a0),
                2);
  TTS_ULP_EQUAL(
      eve::fracscale(a0, 10),
      tts::map([&](auto e) { return e - eve::ldexp(eve::nearest(eve::ldexp(e, 10)), -10); }, a0),
      2);
};

//==================================================================================================
// fracscale[cond](simd) tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fracscale[cond](wide) on  floating types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 100.0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& t)
{
  using eve::fracscale;

  TTS_EQUAL(fracscale(a0, 4), a0 - eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4));
  constexpr eve::index_t<4> four;
  TTS_ULP_EQUAL(fracscale[eve::to_nearest](a0, 4), a0 - eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), 0.5);
  TTS_ULP_EQUAL(fracscale[eve::upward](a0, 4), a0 - eve::ldexp(eve::ceil(eve::ldexp(a0, 4)), -4), 0.5);
  TTS_ULP_EQUAL(fracscale[eve::downward](a0, 4), a0 - eve::ldexp(eve::floor(eve::ldexp(a0, 4)), -4), 0.5);
  TTS_ULP_EQUAL(fracscale[eve::toward_zero](a0, 4), a0 - eve::ldexp(eve::trunc(eve::ldexp(a0, 4)), -4), 0.5);

  TTS_ULP_EQUAL(fracscale(a0, four), a0 - eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), 0.5);
  TTS_ULP_EQUAL(fracscale[eve::to_nearest](a0, four), a0 - eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), 0.5);
  TTS_ULP_EQUAL( fracscale[eve::upward](a0, four), a0 - eve::ldexp(eve::ceil(eve::ldexp(a0, 4)), -4), 0.5);
  TTS_ULP_EQUAL(fracscale[eve::downward](a0, four), a0 - eve::ldexp(eve::floor(eve::ldexp(a0, 4)), -4), 0.5);
  TTS_ULP_EQUAL(fracscale[eve::toward_zero](a0, four), a0 - eve::ldexp(eve::trunc(eve::ldexp(a0, 4)), -4), 0.5);

  TTS_ULP_EQUAL(fracscale[t](a0, four), eve::if_else(t, a0 - eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0), 0.5);
  TTS_ULP_EQUAL(fracscale[eve::to_nearest][t](a0, four), eve::if_else(t, a0 - eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0), 0.5);
  TTS_ULP_EQUAL(fracscale[eve::upward][t](a0, four), eve::if_else(t, a0 - eve::ldexp(eve::ceil(eve::ldexp(a0, 4)), -4), a0), 0.5);
  TTS_ULP_EQUAL(fracscale[eve::downward][t](a0, four), eve::if_else(t, a0 - eve::ldexp(eve::floor(eve::ldexp(a0, 4)), -4), a0), 0.5);
  TTS_ULP_EQUAL(fracscale[eve::toward_zero][t](a0, four), eve::if_else(t, a0 - eve::ldexp(eve::trunc(eve::ldexp(a0, 4)), -4), a0), 0.5);

  TTS_ULP_EQUAL(fracscale[t](a0, 4), eve::if_else(t, a0 - eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0),  0.5);
  TTS_ULP_EQUAL(fracscale[eve::to_nearest][t](a0, 4),  eve::if_else(t, a0 - eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0),  0.5);
  TTS_ULP_EQUAL(fracscale[eve::upward][t](a0, 4),  eve::if_else(t, a0 - eve::ldexp(eve::ceil(eve::ldexp(a0, 4)), -4), a0),  0.5);
  TTS_ULP_EQUAL(fracscale[eve::downward][t][t](a0, 4),  eve::if_else(t, a0 - eve::ldexp(eve::floor(eve::ldexp(a0, 4)), -4), a0),  0.5);
  TTS_ULP_EQUAL(fracscale[eve::toward_zero][t](a0, 4),  eve::if_else(t, a0 - eve::ldexp(eve::trunc(eve::ldexp(a0, 4)), -4), a0),  0.5);
};


//==================================================================================================
// Tests for masked fracscale
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::fracscale)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::fracscale[mask](a0, 4),
            eve::if_else(mask, eve::fracscale(a0, 4), a0));
};
