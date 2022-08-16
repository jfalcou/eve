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
TTS_CASE_TPL("Check return types of radinpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::radinpi(T()), T);
  TTS_EXPR_IS(eve::radinpi(v_t()), v_t);
};

//==================================================================================================
// radinpi  tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of radinpi on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  TTS_ULP_EQUAL(eve::radinpi(a0), a0 * T(0.31830988618379067153776752674502872406891929148092), 2);
};
