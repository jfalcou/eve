//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check return types of minorant(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS(eve::minorant(eve::as<T>()), T);
};

TTS_CASE_TPL("Check return types of minorant(wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS(eve::minorant(eve::as<T>()), T);
};

TTS_CASE_TPL("Check behavior of minorant(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  if constexpr (eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::minorant(eve::as<T>()), eve::minf(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(eve::minorant(eve::as<T>()), eve::valmin(eve::as<T>()));
  }
};

TTS_CASE_TPL("Check behavior of minorant(wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr (eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::minorant(eve::as<T>()), eve::minf(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(eve::minorant(eve::as<T>()), eve::valmin(eve::as<T>()));
  }
};

TTS_CASE_WITH("Check behavior of minorant[mask] on :wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmin),
              tts::logicals(0, 3)))
<typename T, typename M>(T, M m)
{
  if constexpr (eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::minorant[m](eve::as<T>()), eve::if_else(m, eve::minf(eve::as<T>()), eve::zero));
  }
  else
  {
    TTS_EQUAL(eve::minorant[m](eve::as<T>()), eve::if_else(m, eve::valmin(eve::as<T>()), eve::zero));
  }
};
