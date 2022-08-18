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
TTS_CASE_TPL("Check return types of roundscale", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::roundscale(T(), int()), T);
  TTS_EXPR_IS(eve::roundscale(v_t(), int()), v_t);
};

//==================================================================================================
//== roundscale simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of roundscale(wide) and diff on  floating types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100.0, 100.0)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  using eve::rec;
  using eve::sqr;
  TTS_ULP_EQUAL(eve::roundscale(a0, 4),
                map([&](auto e) { return eve::ldexp(eve::nearest(eve::ldexp(e, 4)), -4); }, a0),
                2);
  TTS_ULP_EQUAL(eve::roundscale(a0, 10),
                map([&](auto e) { return eve::ldexp(eve::nearest(eve::ldexp(e, 10)), -10); }, a0),
                2);
};

//==================================================================================================
// roundscale[cond](simd) tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of roundscale[cond](wide) on  floating types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 100.0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& t)
{
  using eve::roundscale;

  std::integral_constant<int, 4> four;
  TTS_EQUAL(roundscale(a0, 4), eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL(eve::to_nearest(roundscale)(a0, 4), eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL(eve::upward(roundscale)(a0, 4), eve::ldexp(eve::ceil(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL(eve::downward(roundscale)(a0, 4), eve::ldexp(eve::floor(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL(eve::toward_zero(roundscale)(a0, 4), eve::ldexp(eve::trunc(eve::ldexp(a0, 4)), -4));

  TTS_EQUAL(roundscale(a0, four), eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL(eve::to_nearest(roundscale)(a0, four), eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL(eve::upward(roundscale)(a0, four), eve::ldexp(eve::ceil(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL(eve::downward(roundscale)(a0, four), eve::ldexp(eve::floor(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL(eve::toward_zero(roundscale)(a0, four), eve::ldexp(eve::trunc(eve::ldexp(a0, 4)), -4));

  TTS_EQUAL(roundscale[t](a0, four),
            eve::if_else(t, eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL(eve::to_nearest(roundscale[t])(a0, four),
            eve::if_else(t, eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL(eve::upward(roundscale[t])(a0, four),
            eve::if_else(t, eve::ldexp(eve::ceil(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL(eve::downward(roundscale[t])(a0, four),
            eve::if_else(t, eve::ldexp(eve::floor(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL(eve::toward_zero(roundscale[t])(a0, four),
            eve::if_else(t, eve::ldexp(eve::trunc(eve::ldexp(a0, 4)), -4), a0));

  TTS_EQUAL(roundscale[t](a0, 4),
            eve::if_else(t, eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL(eve::to_nearest(roundscale[t])(a0, 4),
            eve::if_else(t, eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL(eve::upward(roundscale[t])(a0, 4),
            eve::if_else(t, eve::ldexp(eve::ceil(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL(eve::downward(roundscale[t])(a0, 4),
            eve::if_else(t, eve::ldexp(eve::floor(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL(eve::toward_zero(roundscale[t])(a0, 4),
            eve::if_else(t, eve::ldexp(eve::trunc(eve::ldexp(a0, 4)), -4), a0));
};


//==================================================================================================
// Tests for masked roundscale
//==================================================================================================
// TTS_CASE_WITH("Check behavior of eve::masked(eve::roundscale)(eve::wide)",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::randoms(eve::valmin, eve::valmax),
//               tts::logicals(0, 3)))
// <typename T, typename M>(T const& a0,
//                          M const& mask)
// {
//   TTS_IEEE_EQUAL(eve::roundscale[mask](a0, 4),
//             eve::if_else(mask, eve::roundscale(a0, 4), a0));
// };
