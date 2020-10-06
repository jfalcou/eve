//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sub.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE("Check eve::sub[condition] return type")
{
  TTS_EXPR_IS( (eve::sub[ EVE_TYPE()                ](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::sub[ eve::logical<EVE_TYPE>()  ](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::sub[ true                      ](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
}

TTS_CASE("Check eve::sub[condition] behavior")
{
  EVE_TYPE tv{5};
  EVE_TYPE fv{3};
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  // All basic TRUE
  TTS_EQUAL(eve::sub[ 1     ](tv, fv) , eve::sub(tv,fv));
  TTS_EQUAL(eve::sub[ 1.0   ](tv, fv) , eve::sub(tv,fv));
  TTS_EQUAL(eve::sub[ true  ](tv, fv) , eve::sub(tv,fv));
  TTS_EQUAL(eve::sub[ t     ](tv, fv) , eve::sub(tv,fv));

  // All basic FALSE
  TTS_EQUAL(eve::sub[ 0     ](tv, fv) , tv);
  TTS_EQUAL(eve::sub[ 0.0   ](tv, fv) , tv);
  TTS_EQUAL(eve::sub[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::sub[ f     ](tv, fv) , tv);

  // Mixed case
  eve::as_logical_t<EVE_TYPE> m{};

  bool k = true;
  #if defined(EVE_SIMD_TESTS)
  for(std::size_t i=0;i<EVE_CARDINAL;++i)
  {
    m.set(i, k);
    k = !k;
  }
  #else
  m = k;
  #endif

  TTS_EQUAL(eve::sub[ m ](tv, fv) , eve::if_else(m,eve::sub(tv,fv), tv) );
}
