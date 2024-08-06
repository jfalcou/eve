/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of chi", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::chi(T(), T(), T()), T);
  TTS_EXPR_IS(eve::chi(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::chi(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::chi(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::chi(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::chi(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::chi(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// chi simd tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of chi(wide) and diff  on all types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10.0, 10.0),
                            tts::randoms(-4.0, 2.0),
                            tts::randoms(5.0, 12.0)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::chi;

  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(chi(a0, a1, a2),
             map([&](auto e, auto f, auto g) -> v_t { return e >= f && e < g; }, a0, a1, a2));

  auto b = [a1, a2](auto x){return (x <  a1) || (x >= a2); };
  TTS_EQUAL(chi(a0, b),
             map([](auto e, auto f, auto g) -> v_t { return (e < f || e >=  g); }, a0, a1, a2));
  TTS_EQUAL(chi(a0, a1, 2),
            map([&](auto e, auto f) -> v_t { return e >= f && e < 2; }, a0, a1));

};


//==================================================================================================
// Tests for masked chi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::chi)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10.0, 10.0),
                            tts::randoms(-10.0, 10.0),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::chi[mask](a0, eve::dec(a1), a1),
                 eve::if_else(mask, eve::chi(a0, eve::dec(a1), a1), a0));
  auto b = [a1](auto x){return (x >=   eve::dec(a1)) || (x < a1); };
  TTS_IEEE_EQUAL(eve::chi[mask](a0, b),
                 eve::if_else(mask, eve::chi(a0, b), a0));

};
