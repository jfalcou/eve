//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_TPL("Check valmax constant", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;
  TTS_EQUAL(eve::next(eve::valmax(eve::as<doublereal_t>())), eve::inf(eve::as<doublereal_t>()));
  TTS_NOT_EQUAL(eve::valmax(eve::as<doublereal_t>()), eve::inf(eve::as<doublereal_t>()));
  using wdoublereal_t = eve::as_doublereal_t<T>;
  TTS_EQUAL(eve::next(eve::valmax(eve::as<wdoublereal_t>())), eve::inf(eve::as<wdoublereal_t>()));
  TTS_NOT_EQUAL(eve::valmax(eve::as<wdoublereal_t>()), eve::inf(eve::as<wdoublereal_t>()));

};
