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

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::sqr_abs", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::sqr_abs;

  TTS_EXPR_IS(sqr_abs(T()), T);
  TTS_EXPR_IS(sqr_abs(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sqr_abs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sqr_abs(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::as;
  using eve::sqr_abs;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(sqr_abs(a0), map([](auto e) -> v_t { return e * e; }, a0));
};


//==================================================================================================
// Tests for masked sqr_abs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sqr_abs)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sqr_abs[mask](a0),
            eve::if_else(mask, eve::sqr_abs(a0), a0));
};
