//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/dd.hpp>

TTS_CASE_TPL("Check valmax constant", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = typename T::value_type;
  using dd_t = eve::dd<e_t>;
  std::cout << tts::typename_<T> << std::endl;
  TTS_EQUAL(eve::next(eve::valmax(eve::as<dd_t>())), eve::inf(eve::as<dd_t>()));
  TTS_NOT_EQUAL(eve::valmax(eve::as<dd_t>()), eve::inf(eve::as<dd_t>()));
  using wdd_t = eve::as_dd_t<T>;
  TTS_EQUAL(eve::next(eve::valmax(eve::as<wdd_t>())), eve::inf(eve::as<wdd_t>()));
  TTS_NOT_EQUAL(eve::valmax(eve::as<wdd_t>()), eve::inf(eve::as<wdd_t>()));

};
