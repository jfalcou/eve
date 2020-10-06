//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE("Check oneminus return type")
{
  TTS_EXPR_IS(eve::saturated(eve::oneminus[ EVE_VALUE(0)              ])(EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[ EVE_TYPE(0)               ])(EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[ eve::logical<EVE_TYPE>(0) ])(EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[ eve::logical<EVE_VALUE>(0)])(EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[ true                      ])(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::saturated(eve::oneminus) behavior")
{
  EVE_TYPE tv, res;
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    tv  = eve::valmin(eve::as<EVE_TYPE>());
    res = eve::valmax(eve::as<EVE_TYPE>());
  }
  else
  {
    tv  = EVE_TYPE{2};
    res = EVE_TYPE{0};
  }

  TTS_EQUAL(eve::saturated(eve::oneminus[ 1    ])(tv), res);
  TTS_EQUAL(eve::saturated(eve::oneminus[ 1.0  ])(tv), res);
  TTS_EQUAL(eve::saturated(eve::oneminus[ true ])(tv), res);
  TTS_EQUAL(eve::saturated(eve::oneminus[ t    ])(tv), res);

  TTS_EQUAL(eve::saturated(eve::oneminus[ 0 ])(tv)     , tv);
  TTS_EQUAL(eve::saturated(eve::oneminus[ 0.0 ])(tv)   , tv);
  TTS_EQUAL(eve::saturated(eve::oneminus[ false ])(tv) , tv);
  TTS_EQUAL(eve::saturated(eve::oneminus[ f ])(tv)     , tv);

    // Mixed case
  eve::as_logical_t<EVE_TYPE> m;
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

  TTS_EQUAL(eve::saturated(eve::oneminus[ m ])(tv), eve::if_else(m, res, tv) );
}
