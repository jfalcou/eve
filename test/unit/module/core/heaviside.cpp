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
TTS_CASE_TPL("Check return types of heaviside", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::heaviside(T(), T()), T);
  TTS_EXPR_IS(eve::heaviside(T(), v_t()), T);
  TTS_EXPR_IS(eve::heaviside(v_t(), T()), T);
  TTS_EXPR_IS(eve::heaviside(T()), T);
  TTS_EXPR_IS(eve::heaviside(v_t()), v_t);
};

//==================================================================================================
// heaviside simd tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of heaviside(wide) on all types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10.0, 10.0),
                            tts::randoms(-4.0, 2.0))
             )
  <typename T>(T const& a0, T const& a1)
{
  using eve::heaviside;

  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(heaviside(a0, a1),
            tts::map([&](auto e, auto f) -> v_t { return e > f; }, a0, a1));
  TTS_EQUAL(heaviside(a0),
            tts::map([&](auto e) -> v_t { return e > 0; }, a0));
};


//==================================================================================================
// Tests for masked heaviside
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::heaviside)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10.0, 10.0),
                            tts::randoms(-10.0, 10.0),
                            tts::logicals(0, 3)))
  <typename T, typename M>(T const& a0,
                           T const& a1,
                           M const& mask)
{
  TTS_IEEE_EQUAL(eve::heaviside[mask](a0, a1),
                 eve::if_else(mask, eve::heaviside(a0, a1), a0));
};
