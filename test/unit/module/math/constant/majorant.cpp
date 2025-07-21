//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check return types of majorant(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS(eve::majorant(eve::as<T>()), T);
};

TTS_CASE_TPL("Check return types of majorant(wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS(eve::majorant(eve::as<T>()), T);
};

TTS_CASE_TPL("Check behavior of majorant(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  if constexpr (eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::majorant(eve::as<T>()), eve::inf(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(eve::majorant(eve::as<T>()), eve::valmax(eve::as<T>()));
  }
};

TTS_CASE_TPL("Check behavior of majorant(wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr (eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::majorant(eve::as<T>()), eve::inf(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(eve::majorant(eve::as<T>()), eve::valmax(eve::as<T>()));
  }
};

TTS_CASE_WITH("Check behavior of majorant[mask] on :wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T, M m)
{
  if constexpr (eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::majorant[m](eve::as<T>()), eve::if_else(m, eve::inf(eve::as<T>()), eve::zero));
  }
  else
  {
    TTS_EQUAL(eve::majorant[m](eve::as<T>()), eve::if_else(m, eve::valmax(eve::as<T>()), eve::zero));
  }
};
