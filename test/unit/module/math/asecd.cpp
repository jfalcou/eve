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
TTS_CASE_TPL("Check return types of asecd", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::asecd(T()), T);
  TTS_EXPR_IS(eve::asecd(v_t()), v_t);
};

//==================================================================================================
// asecd  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of asecd on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(1.0, 100.0),
                            tts::randoms(1.0, eve::valmax),
                            tts::randoms(eve::valmin, -1.0),
                            tts::randoms(-100.0, -1.0)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using v_t = eve::element_type_t<T>;

  auto sasecd = [](auto e) -> v_t { return eve::radindeg(std::acos(1 / e)); };
  TTS_ULP_EQUAL(eve::asecd(a0), tts::map(sasecd, a0), 2);

  TTS_ULP_EQUAL(eve::asecd(a1), tts::map(sasecd, a1), 2);

  TTS_ULP_EQUAL(eve::asecd(a2), tts::map(sasecd, a2), 2);

  TTS_ULP_EQUAL(eve::asecd(a3), tts::map(sasecd, a3), 2);
};


//==================================================================================================
// Tests for masked asecd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::asecd)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::asecd[mask](a0),
            eve::if_else(mask, eve::asecd(a0), a0));
};
