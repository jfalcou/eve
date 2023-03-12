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
  std::cout << tts::typename_<T> << std::endl;
  TTS_EQUAL(eve::prev(eve::valmin(eve::as<doublereal_t>())), eve::minf(eve::as<doublereal_t>()));
  TTS_NOT_EQUAL(eve::valmin(eve::as<doublereal_t>()), eve::minf(eve::as<doublereal_t>()));
  using wdoublereal_t = eve::as_doublereal_t<T>;
  TTS_EQUAL(eve::prev(eve::valmin(eve::as<wdoublereal_t>())), eve::minf(eve::as<wdoublereal_t>()));
  TTS_NOT_EQUAL(eve::valmin(eve::as<wdoublereal_t>()), eve::minf(eve::as<wdoublereal_t>()));
};
