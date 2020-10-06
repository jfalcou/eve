//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/add.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>

TTS_CASE("Check aturated conditional add return type")
{
  TTS_EXPR_IS( (eve::saturated(eve::add[ eve::if_not_(EVE_TYPE())              ])(EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::saturated(eve::add[ eve::if_not_(eve::logical<EVE_TYPE>())])(EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::saturated(eve::add[ eve::if_not_(true)                    ])(EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
}

TTS_CASE("Check saturated conditional add behavior")
{
  EVE_TYPE tv{eve::valmax(eve::as<EVE_TYPE>())};
  EVE_TYPE fv{3};
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  TTS_EQUAL(eve::saturated(eve::add[ eve::if_not_(1) ])(tv, fv)    , eve::saturated(eve::add)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::add[ eve::if_not_(1.0) ])(tv, fv)  , eve::saturated(eve::add)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::add[ eve::if_not_(true) ])(tv, fv) , eve::saturated(eve::add)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::add[ eve::if_not_(t) ])(tv, fv)    , eve::saturated(eve::add)(tv,fv));

  TTS_EQUAL(eve::saturated(eve::add[ eve::if_not_(0) ])(tv, fv)    , tv);
  TTS_EQUAL(eve::saturated(eve::add[ eve::if_not_(0.0) ])(tv, fv)  , tv);
  TTS_EQUAL(eve::saturated(eve::add[ eve::if_not_(false) ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated(eve::add[ eve::if_not_(f) ])(tv, fv)    , tv);

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

  TTS_EQUAL ( eve::saturated(eve::add[ eve::if_not_(m) ])(tv, fv),
                  eve::if_else(m, eve::saturated(eve::add)(tv,fv), tv)
                );

}
