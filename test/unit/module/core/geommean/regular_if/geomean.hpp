//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/geommean.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <eve/function/if_else.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE_TPL("Check eve::geommean[condition] return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::geommean[ T() ](T(), T())), T);
  TTS_EXPR_IS( (eve::geommean[ eve::logical<T>() ](T(), T())), T);
  TTS_EXPR_IS( (eve::geommean[ true ](T(), T())), T);
  TTS_EXPR_IS( (eve::geommean[ eve::if_(true)](T(), T())), T);
}

TTS_CASE_TPL("Check eve::geommean[condition] behavior", EVE_TYPE)
{
  T tv{2};
  T fv{3};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(eve::geommean[ 1 ](tv, fv)     , eve::geommean(fv,tv));
  TTS_EQUAL(eve::geommean[ 1.0 ](tv, fv)   , eve::geommean(fv,tv));
  TTS_EQUAL(eve::geommean[ true ](tv, fv)  , eve::geommean(fv,tv));
  TTS_EQUAL(eve::geommean[ t ](tv, fv)     , eve::geommean(fv,tv));

  // All basic FALSE
  TTS_EQUAL(eve::geommean[ 0 ](tv, fv)     , tv);
  TTS_EQUAL(eve::geommean[ 0.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::geommean[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::geommean[ f ](tv, fv)     , tv);

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

  TTS_EQUAL(eve::geommean[ m ](tv, fv) , eve::if_else(m, eve::geommean(tv, fv), tv) );
}
