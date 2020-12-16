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

TTS_CASE_TPL("Check eve::big(eve::sindcosd) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big(eve::sindcosd)(T()), (std::tuple<T, T>));
}

TTS_CASE_TPL("Check eve::big(eve::sindcosd) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto base = v_t(180);
  auto vmax = eve::valmax(eve::as<v_t>());
  auto vmin = eve::valmin(eve::as<v_t>());

  v_t x[] = { base/8, -base/8, base/4, -base/4
            , base, -base, 10*base, -10*base
            , v_t(1000000), v_t(-1000000), v_t(1000000000), v_t(-1000000000)
            , vmax, vmin, vmax/10000, vmin/10000
            };

  for(auto v : x)
  {
    auto [sin_, cos_] = eve::big(eve::sindcosd)(T(v));
    TTS_ULP_EQUAL(sin_, eve::sind(T(v)), 0.5);
    TTS_ULP_EQUAL(cos_, eve::cosd(T(v)), 0.5);
  }
}
