//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mul.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check eve::mul[condition] return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::mul[ T() ](T(), T())), T);
  TTS_EXPR_IS( (eve::mul[ eve::logical<T>() ](T(), T())), T);
  TTS_EXPR_IS( (eve::mul[ true ](T(), T())), T);
}

TTS_CASE_TPL("Check eve::mul[condition] behavior", EVE_TYPE)
{
  T tv{2};
  T fv{3};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(eve::mul[ 1 ](tv, fv)     , tv * fv);
  TTS_EQUAL(eve::mul[ 1.0 ](tv, fv)   , tv * fv);
  TTS_EQUAL(eve::mul[ true ](tv, fv)  , tv * fv);
  TTS_EQUAL(eve::mul[ t ](tv, fv)     , tv * fv);

  // All basic FALSE
  TTS_EQUAL(eve::mul[ 0 ](tv, fv)     , tv);
  TTS_EQUAL(eve::mul[ 0.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::mul[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::mul[ f ](tv, fv)     , tv);

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

  TTS_EQUAL(eve::mul[ m ](tv, fv) , eve::if_else(m,eve::mul(tv, fv), tv) );
}
