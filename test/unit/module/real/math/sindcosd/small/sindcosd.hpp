//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sindcosd.hpp>
#include <eve/function/cosd.hpp>
#include <eve/function/sind.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/pi.hpp>
#include <tuple>

TTS_CASE_TPL("Check eve::small(eve::sindcosd) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small(eve::sindcosd)(T()), (std::tuple<T, T>));
}

TTS_CASE_TPL("Check eve::small(eve::sindcosd) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto base = v_t(180);

  v_t x[] = { base/8, -base/8, base/4, -base/4, base/2, -base/2};

  for(auto v : x)
  {
    auto [sin_, cos_] = eve::small(eve::sindcosd)(T(v));
    TTS_ULP_EQUAL(sin_, eve::sind(T(v)), 0.5);
    TTS_ULP_EQUAL(cos_, eve::cosd(T(v)), 0.5);
  }

}
