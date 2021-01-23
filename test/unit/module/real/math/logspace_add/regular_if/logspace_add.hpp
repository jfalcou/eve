//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logspace_add.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <eve/function/if_else.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE_TPL("Check eve::logspace_add[condition] return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::logspace_add[ T() ](T(), T())), T);
  TTS_EXPR_IS( (eve::logspace_add[ eve::logical<T>() ](T(), T())), T);
  TTS_EXPR_IS( (eve::logspace_add[ true ](T(), T())), T);
  TTS_EXPR_IS( (eve::logspace_add[ eve::if_(true)](T(), T())), T);
}

TTS_CASE_TPL("Check eve::logspace_add[condition] behavior", EVE_TYPE)
{
  T tv{2};
  T fv{3};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(eve::logspace_add[ 1 ](tv, fv)     , eve::logspace_add(fv,tv));
  TTS_EQUAL(eve::logspace_add[ 1.0 ](tv, fv)   , eve::logspace_add(fv,tv));
  TTS_EQUAL(eve::logspace_add[ true ](tv, fv)  , eve::logspace_add(fv,tv));
  TTS_EQUAL(eve::logspace_add[ t ](tv, fv)     , eve::logspace_add(fv,tv));

  // All basic FALSE
  TTS_EQUAL(eve::logspace_add[ 0 ](tv, fv)     , tv);
  TTS_EQUAL(eve::logspace_add[ 0.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::logspace_add[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::logspace_add[ f ](tv, fv)     , tv);

  // Mixed case
  bool k = true;
  #if defined(EVE_SIMD_TESTS)
  eve::as_logical_t<T> m{false};
  for(std::size_t i=0;i<eve::cardinal_v<T>;++i)
  {
    m.set(i, k);
    k = !k;
  }
  #else
  eve::as_logical_t<T> m{k};
  #endif

  TTS_EQUAL(eve::logspace_add[ m ](tv, fv) , eve::if_else(m, eve::logspace_add(tv, fv), tv) );
}
