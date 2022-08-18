//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of radindeg", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::radindeg(T()), T);
  TTS_EXPR_IS(eve::radindeg(v_t()), v_t);
};

//==================================================================================================
// radindeg  tests
//==================================================================================================
auto mini = tts::constant([](auto const& tgt) { return eve::valmin(tgt) / 60; });
auto maxi = tts::constant([](auto const& tgt) { return eve::valmax(tgt) / 60; });

TTS_CASE_WITH("Check behavior of radindeg on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(mini, maxi)))
<typename T>(T const& a0)
{
  TTS_ULP_EQUAL(eve::radindeg(a0), a0 * T(57.295779513082320876798154814105170332405472466565), 2);
};


//==================================================================================================
// Tests for masked radindeg
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::radindeg)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::radindeg[mask](a0),
            eve::if_else(mask, eve::radindeg(a0), a0));
};
