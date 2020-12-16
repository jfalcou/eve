//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitofsign.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE_TPL("Check eve::bitofsign[condition] return type", EVE_TYPE)
{
  TTS_EXPR_IS( eve::bitofsign[ T() ](T())               , T);
  TTS_EXPR_IS( eve::bitofsign[ eve::logical<T>() ](T()) , T);
  TTS_EXPR_IS( eve::bitofsign[ true ](T())              , T);
}

TTS_CASE_TPL("Check eve::bitofsign[condition] behavior", EVE_TYPE)
{
  T tv{2};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(eve::bitofsign[ 1 ](tv)     , eve::bitofsign(tv));
  TTS_EQUAL(eve::bitofsign[ 1.0 ](tv)   , eve::bitofsign(tv));
  TTS_EQUAL(eve::bitofsign[ true ](tv)  , eve::bitofsign(tv));
  TTS_EQUAL(eve::bitofsign[ t ](tv)     , eve::bitofsign(tv));

  // All basic FALSE
  TTS_EQUAL(eve::bitofsign[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::bitofsign[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::bitofsign[ false ](tv) , tv);
  TTS_EQUAL(eve::bitofsign[ f ](tv)     , tv);

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

  TTS_EQUAL(eve::bitofsign[ m ](tv) , eve::if_else(m,eve::bitofsign(tv), tv) );
}
