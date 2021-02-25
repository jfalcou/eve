//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cbrt.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE_TPL("Check eve::cbrt[condition] return type", EVE_TYPE)
{
  TTS_EXPR_IS( eve::cbrt[ T() ](T())               , T);
  TTS_EXPR_IS( eve::cbrt[ eve::logical<T>() ](T()) , T);
  TTS_EXPR_IS( eve::cbrt[ true ](T())              , T);
}

TTS_CASE_TPL("Check eve::cbrt[condition] behavior", EVE_TYPE)
{
  T tv{2};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(eve::cbrt[ 1 ](tv)     , eve::cbrt(tv));
  TTS_EQUAL(eve::cbrt[ 1.0 ](tv)   , eve::cbrt(tv));
  TTS_EQUAL(eve::cbrt[ true ](tv)  , eve::cbrt(tv));
  TTS_EQUAL(eve::cbrt[ t ](tv)     , eve::cbrt(tv));

  // All basic FALSE
  TTS_EQUAL(eve::cbrt[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::cbrt[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::cbrt[ false ](tv) , tv);
  TTS_EQUAL(eve::cbrt[ f ](tv)     , tv);

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

  TTS_EQUAL(eve::cbrt[ m ](tv) , eve::if_else(m,eve::cbrt(tv), tv) );
}
