//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/inc.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check conditional saturated(eve::inc) return type", EVE_TYPE)
{
  using eve::saturated;
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS((saturated(eve::inc[T()])(T()))                , T);
  TTS_EXPR_IS((saturated(eve::inc[v_t()])(T()))              , T);
  TTS_EXPR_IS((saturated(eve::inc[true])(T()))               , T);
  TTS_EXPR_IS((saturated(eve::inc[eve::logical<T>()])(T()))  , T);
  TTS_EXPR_IS((saturated(eve::inc[eve::logical<v_t>()])(T())), T);
}

TTS_CASE_TPL("Check conditional saturated(eve::inc) behavior", EVE_TYPE)
{
  using eve::saturated;

  T tv(2);
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(saturated(eve::inc[ 1 ])(eve::valmax(eve::as<T>()))     , eve::valmax(eve::as<T>()));
  TTS_EQUAL(saturated(eve::inc[ 1.0 ])(eve::valmax(eve::as<T>()))   , eve::valmax(eve::as<T>()));
  TTS_EQUAL(saturated(eve::inc[ true ])(eve::valmax(eve::as<T>()))  , eve::valmax(eve::as<T>()));
  TTS_EQUAL(saturated(eve::inc[ t ])(eve::valmax(eve::as<T>()))     , eve::valmax(eve::as<T>()));

  // All basic FALSE
  TTS_EQUAL(saturated(eve::inc[ 0 ])(tv)     , tv);
  TTS_EQUAL(saturated(eve::inc[ 0.0 ])(tv)   , tv);
  TTS_EQUAL(saturated(eve::inc[ false ])(tv) , tv);
  TTS_EQUAL(saturated(eve::inc[ f ])(tv)     , tv);

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

  TTS_EQUAL(saturated(eve::inc[ m ])(tv) , eve::if_else(m,saturated(eve::inc)(tv), tv) );
}
