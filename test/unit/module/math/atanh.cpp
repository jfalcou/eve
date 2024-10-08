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
TTS_CASE_TPL("Check return types of atanh", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::atanh(T()), T);
  TTS_EXPR_IS(eve::atanh(v_t()), v_t);
};

//==================================================================================================
// atanh  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of atanh on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::atanh(a0), tts::map([](auto e) -> v_t { return std::atanh(e); }, a0), 2);
};


//==================================================================================================
// Tests for masked atanh
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::atanh)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::atanh[mask](a0),
            eve::if_else(mask, eve::atanh(a0), a0));
};
