//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of conj", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::conj(T()), T);
  TTS_EXPR_IS(eve::conj(v_t()), v_t);
};

//==================================================================================================
// conj  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of conj on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0) { TTS_EQUAL(eve::conj(a0), a0); };


//==================================================================================================
// Tests for masked conj
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::conj)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::conj[mask](a0),
            eve::if_else(mask, eve::conj(a0), a0));
};
