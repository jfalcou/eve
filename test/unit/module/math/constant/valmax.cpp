//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check return types of valmax(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS(eve::valmax(eve::as<T>()), T);
};

TTS_CASE_TPL("Check return types of valmax(wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS(eve::valmax(eve::as<T>()), T);
};

TTS_CASE_TPL("Check behavior of valmax(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::valmax(eve::as<T>()), std::numeric_limits<T>::max());
};

TTS_CASE_TPL("Check behavior of valmax(wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::valmax(eve::as<T>()), T{ std::numeric_limits<eve::element_type_t<T>>::max() });
};

TTS_CASE_WITH("Check behavior of valmax[mask] on :wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmax, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T, M m)
{
  TTS_EQUAL(eve::valmax[m](eve::as<T>()), eve::if_else(m, T{ std::numeric_limits<eve::element_type_t<T>>::max() }, eve::zero));
};
