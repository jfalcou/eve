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

TTS_CASE("Check frexp return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::frexp)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check eve::pedantic_(eve::frexp) behavior")
{
  {
    auto [p0, p1] = eve::pedantic_(eve::frexp)(EVE_TYPE(1));
    TTS_EQUAL(p0, EVE_TYPE(0.5));
    TTS_EQUAL(p1, EVE_TYPE(1));
  }
  {
    auto [p0, p1] = eve::pedantic_(eve::frexp)(EVE_TYPE(0));
    TTS_EQUAL (p0 , EVE_TYPE(0));
    TTS_EQUAL (p1, EVE_TYPE(0));
  }
  if constexpr(eve::platform::supports_nans)
  {
    auto [r0, r1] = eve::pedantic_(eve::frexp)(eve::Nan<EVE_TYPE>());
    
    TTS_IEEE_EQUAL(r0 , (eve::Nan<EVE_TYPE>()));
    TTS_EQUAL     (r1, (EVE_TYPE(0)));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    auto [r0, r1] = eve::pedantic_(eve::frexp)(eve::Inf<EVE_TYPE>());
    auto [q0, q1] = eve::pedantic_(eve::frexp)(eve::Minf<EVE_TYPE>());
    
    TTS_IEEE_EQUAL(r0, (eve::Inf<EVE_TYPE>()));
    TTS_EQUAL     (r1, EVE_TYPE(0));
    
    TTS_IEEE_EQUAL(q0, (eve::Minf<EVE_TYPE>()));
    TTS_EQUAL     (q1, EVE_TYPE(0));
  }
  if constexpr(eve::platform::supports_denormals)
  {
    auto [r0, r1] = eve::pedantic_(eve::frexp)(eve::Mindenormal<EVE_TYPE>());
    
    TTS_ULP_EQUAL (r0, EVE_TYPE(0.5), 1);
    TTS_EQUAL     (r1, EVE_TYPE(eve::Minexponent<EVE_VALUE>()-eve::Nbmantissabits<EVE_VALUE>()+1));
  }
}
