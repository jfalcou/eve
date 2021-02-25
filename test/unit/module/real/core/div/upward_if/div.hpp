//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>

TTS_CASE_TPL("Check conditional saturated(eve::div) return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::upward(eve::div[ T()              ])(T(), T())), T);
  TTS_EXPR_IS( (eve::upward(eve::div[ eve::logical<T>()])(T(), T())), T);
  TTS_EXPR_IS( (eve::upward(eve::div[ true             ])(T(), T())), T);
}

TTS_CASE_TPL("Check conditional saturated(eve::div) behavior", EVE_TYPE)
{
  T tv(eve::valmax(eve::as<T>()));
  T fv(3);
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  TTS_EQUAL(eve::upward(eve::div[ 1 ])(tv, fv)    , eve::upward(eve::div)(tv,fv));
  TTS_EQUAL(eve::upward(eve::div[ 1.0 ])(tv, fv)  , eve::upward(eve::div)(tv,fv));
  TTS_EQUAL(eve::upward(eve::div[ true ])(tv, fv) , eve::upward(eve::div)(tv,fv));
  TTS_EQUAL(eve::upward(eve::div[ t ])(tv, fv)    , eve::upward(eve::div)(tv,fv));

  TTS_EQUAL(eve::upward(eve::div[ 0 ])(tv, fv)    , tv);
  TTS_EQUAL(eve::upward(eve::div[ 0.0 ])(tv, fv)  , tv);
  TTS_EQUAL(eve::upward(eve::div[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::upward(eve::div[ f ])(tv, fv)    , tv);

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

  TTS_EQUAL ( eve::upward(eve::div[ m ])(tv, fv),
                  eve::if_else(m, eve::upward(eve::div)(tv,fv), tv)
                );

}
