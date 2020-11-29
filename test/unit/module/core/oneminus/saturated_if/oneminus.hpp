//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/oneminus.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check oneminus return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::saturated(eve::oneminus[ v_t(0)               ])(T(0)), T);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[ T(0)                 ])(T(0)), T);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[ eve::logical<T>(0)   ])(T(0)), T);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[ eve::logical<v_t>(0) ])(T(0)), T);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[ true                 ])(T(0)), T);
}

TTS_CASE_TPL("Check eve::saturated(eve::oneminus) behavior", EVE_TYPE)
{
  T tv, res;
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  if constexpr(eve::signed_value<T>)
  {
    tv  = eve::valmin(eve::as<T>());
    res = eve::valmax(eve::as<T>());
  }
  else
  {
    tv  = T{2};
    res = T{0};
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
  eve::as_logical_t<T> m;
  bool k = true;
  #if defined(EVE_SIMD_TESTS)
  for(std::size_t i=0;i<eve::cardinal_v<T>;++i)
  {
    m.set(i, k);
    k = !k;
  }
  #else
  m = k;
  #endif

  TTS_EQUAL(eve::saturated(eve::oneminus[ m ])(tv), eve::if_else(m, res, tv) );
}
