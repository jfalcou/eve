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
#include <tuple>

using i_t = eve::detail::as_integer_t<EVE_TYPE,signed>;

TTS_CASE("Check ifrexp return type")
{
  TTS_EXPR_IS(eve::raw(eve::ifrexp)(EVE_TYPE()), (std::tuple<EVE_TYPE,i_t>));
}

TTS_CASE("Check eve::raw(eve::ifrexp) behavior")
{
  auto [p0, p1] = eve::raw(eve::ifrexp)(EVE_TYPE(1));
  TTS_EQUAL(p0, EVE_TYPE(0.5));
  TTS_EQUAL(p1, i_t(1));
}
