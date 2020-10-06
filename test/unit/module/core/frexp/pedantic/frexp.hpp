//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/frexp.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <tuple>

TTS_CASE("Check frexp return type")
{
  TTS_EXPR_IS(eve::pedantic(eve::frexp)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check eve::pedantic(eve::frexp) behavior")
{
  {
    auto [p0, p1] = eve::pedantic(eve::frexp)(EVE_TYPE(1));
    TTS_EQUAL(p0, EVE_TYPE(0.5));
    TTS_EQUAL(p1, EVE_TYPE(1));
  }
  {
    auto [p0, p1] = eve::pedantic(eve::frexp)(EVE_TYPE(0));
    TTS_EQUAL (p0 , EVE_TYPE(0));
    TTS_EQUAL (p1, EVE_TYPE(0));
  }
  if constexpr(eve::platform::supports_nans)
  {
    auto [r0, r1] = eve::pedantic(eve::frexp)(eve::nan(eve::as<EVE_TYPE>()));

    TTS_IEEE_EQUAL(r0 , (eve::nan(eve::as<EVE_TYPE>())));
    TTS_EQUAL     (r1, (EVE_TYPE(0)));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    auto [r0, r1] = eve::pedantic(eve::frexp)(eve::inf(eve::as<EVE_TYPE>()));
    auto [q0, q1] = eve::pedantic(eve::frexp)(eve::minf(eve::as<EVE_TYPE>()));

    TTS_IEEE_EQUAL(r0, (eve::inf(eve::as<EVE_TYPE>())));
    TTS_EQUAL     (r1, EVE_TYPE(0));

    TTS_IEEE_EQUAL(q0, (eve::minf(eve::as<EVE_TYPE>())));
    TTS_EQUAL     (q1, EVE_TYPE(0));
  }
  if constexpr(eve::platform::supports_denormals)
  {
      auto [r0, r1] = eve::pedantic(eve::frexp)(eve::mindenormal(eve::as<EVE_TYPE>()));

    TTS_ULP_EQUAL (r0, EVE_TYPE(0.5), 1);
    TTS_EQUAL     (r1, EVE_TYPE(eve::minexponent(eve::as<EVE_VALUE>())-eve::nbmantissabits(eve::as<EVE_VALUE>())+1));
  }
}
