//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ifrexp.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <utility>

TTS_CASE("Check ifrexp return type")
{
  TTS_EXPR_IS((eve::ifrexp(EVE_TYPE())), (std::tuple<EVE_TYPE,eve::detail::as_integer_t<EVE_TYPE,signed>>));
}

TTS_CASE("Check (eve::ifrexp behavior")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE,signed>; 
  {
    auto [p0, p1] = eve::ifrexp(EVE_TYPE(1));
    TTS_EQUAL(p0, EVE_TYPE(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
  {
    auto [p0, p1] = eve::ifrexp(EVE_TYPE(0));
    TTS_EQUAL (p0 , EVE_TYPE(0));
    TTS_EQUAL (p1, i_t(0));
  }
}
