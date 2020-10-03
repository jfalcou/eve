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

TTS_CASE("Check eve::medium(eve::sindcosd) return type")
{
  TTS_EXPR_IS(eve::medium(eve::sindcosd)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check eve::medium(eve::sindcosd) behavior")
{
  auto base = EVE_VALUE(180);
  auto vmax = eve::valmax(eve::as<EVE_VALUE>());
  auto vmin = eve::valmin(eve::as<EVE_VALUE>());

  EVE_VALUE x[] = { base/8, -base/8, base/4, -base/4
            , base, -base, 10*base, -10*base
            , EVE_VALUE(1000000), EVE_VALUE(-1000000), EVE_VALUE(1000000000), EVE_VALUE(-1000000000)
            , vmax, vmin, vmax/10000, vmin/10000
            };

  for(auto v : x)
  {
    auto [sin_, cos_] = eve::medium(eve::sindcosd)(EVE_TYPE(v));
    TTS_ULP_EQUAL(sin_, eve::sind(EVE_TYPE(v)), 0.5);
    TTS_ULP_EQUAL(cos_, eve::cosd(EVE_TYPE(v)), 0.5);
  }
}
