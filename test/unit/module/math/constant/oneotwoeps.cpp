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

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of oneotwoeps", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::oneotwoeps(as<T>()), T);
  TTS_EXPR_IS(eve::oneotwoeps(as<v_t>()), v_t);
};

//==================================================================================================
// oneotwoeps is defined by its relation to the constants it derives from
//==================================================================================================
TTS_CASE_TPL("Check behavior of oneotwoeps", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EQUAL(eve::oneotwoeps(as<T>()), eve::rec(2 * eve::eps(as<T>())));
};

//==================================================================================================
// masked oneotwoeps
//==================================================================================================
TTS_CASE_WITH("Check behavior of oneotwoeps[mask] on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::oneotwoeps[mask](eve::as(a0)), eve::if_else(mask, eve::oneotwoeps(eve::as(a0)), eve::zero));
};
