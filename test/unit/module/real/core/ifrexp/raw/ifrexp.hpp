//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/ifrexp.hpp>
#include <tuple>

TTS_CASE_TPL("Check ifrexp return type", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  TTS_EXPR_IS(eve::raw(eve::ifrexp)(T()), (kumi::tuple<T,eve::as_integer_t<T,signed>>));
};

TTS_CASE_TPL("Check eve::raw(eve::ifrexp) behavior", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  using i_t = eve::as_integer_t<T,signed>;
  auto [p0, p1] = eve::raw(eve::ifrexp)(T(1));
  TTS_EQUAL(p0, T(0.5));
  TTS_EQUAL(p1, i_t(1));
};
