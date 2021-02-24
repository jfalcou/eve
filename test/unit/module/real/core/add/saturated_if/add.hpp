//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/add.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>

TTS_CASE_TPL("Check add return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::saturated(eve::add[ T()              ])(T(), T())), T);
  TTS_EXPR_IS( (eve::saturated(eve::add[ eve::logical<T>()])(T(), T())), T);
  TTS_EXPR_IS( (eve::saturated(eve::add[ true                ])(T(), T())), T);
}

TTS_CASE_TPL("Check saturated conditional add behavior", EVE_TYPE)
{
  T tv{eve::valmax(eve::as<T>())};
  T fv{3};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  TTS_EQUAL(eve::saturated(eve::add[ 1 ])(tv, fv)    , eve::saturated(eve::add)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::add[ 1.0 ])(tv, fv)  , eve::saturated(eve::add)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::add[ true ])(tv, fv) , eve::saturated(eve::add)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::add[ t ])(tv, fv)    , eve::saturated(eve::add)(tv,fv));

  TTS_EQUAL(eve::saturated(eve::add[ 0 ])(tv, fv)    , tv);
  TTS_EQUAL(eve::saturated(eve::add[ 0.0 ])(tv, fv)  , tv);
  TTS_EQUAL(eve::saturated(eve::add[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated(eve::add[ f ])(tv, fv)    , tv);

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

  TTS_EQUAL ( eve::saturated(eve::add[ m ])(tv, fv),
                  eve::if_else(m, eve::saturated(eve::add)(tv,fv), tv)
                );

}
