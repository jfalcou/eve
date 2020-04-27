//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nbtrue.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/platform.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::nbtrue return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::nbtrue(eve::logical<T>())) , size_t);
  TTS_EXPR_IS( (eve::nbtrue(T()))               , size_t);
}

TTS_CASE_TPL("Check eve::nbtrue behavior on arithmetic", EVE_TYPE)
{
  size_t c = EVE_CARDINAL;
  TTS_EQUAL( (eve::nbtrue(T{1})), c);
  TTS_EQUAL( (eve::nbtrue(T{0})), 0u);

  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_nans )
    {
      TTS_EQUAL(eve::nbtrue(eve::Nan<T>()), c);
    }

    TTS_EQUAL(eve::nbtrue(T(-0.)), 0u);
  }

#if defined(EVE_SIMD_TESTS)
  for( size_t j=0; j < c; ++j)
  {
    T rhs1,rhs2, rhs3, rhs4;

    for(size_t i=0; i< c; ++i)
    {
      rhs1[i] = i >= j ? 1 : 0;
      rhs2[i] = i <= j ? 0 : 1;
      rhs3[i] = i == j ? 1 : 0;
      rhs4[i] = i == j ? 0 : 1;
    }

    TTS_EQUAL(eve::nbtrue(rhs1), size_t(c-j));
    TTS_EQUAL(eve::nbtrue(rhs2), size_t(c-j-1));
    TTS_EQUAL(eve::nbtrue(rhs3), 1u);
    TTS_EQUAL(eve::nbtrue(rhs4), size_t(c-1u));

  }
#endif
}

TTS_CASE_TPL("Check eve::nbtrue behavior on logical", EVE_TYPE)
{
  size_t c = EVE_CARDINAL;
  TTS_EQUAL(eve::nbtrue(eve::True<T>()), c);
  TTS_EQUAL(eve::nbtrue(eve::False<T>()), 0u);
}
