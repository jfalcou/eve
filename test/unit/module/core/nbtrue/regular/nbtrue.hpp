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

TTS_CASE("Check eve::nbtrue return type")
{
  TTS_EXPR_IS( (eve::nbtrue(eve::logical<EVE_TYPE>())) , size_t);
  TTS_EXPR_IS( (eve::nbtrue(EVE_TYPE()))               , size_t);
}

TTS_CASE("Check eve::nbtrue behavior on arithmetic")
{
  size_t c = EVE_CARDINAL; 
  TTS_EQUAL( (eve::nbtrue(EVE_TYPE{1})), c);
  TTS_EQUAL( (eve::nbtrue(EVE_TYPE{0})), 0u);

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    if constexpr( eve::platform::supports_nans )
    {
      TTS_EQUAL(eve::nbtrue(eve::Nan<EVE_TYPE>()), c);
    }

    TTS_EQUAL(eve::nbtrue(eve::Mzero<EVE_TYPE>()), 0u);
  }

#if defined(EVE_SIMD_TESTS)
  for( size_t j=0; j < c; ++j)
  {
    EVE_TYPE rhs1,rhs2, rhs3, rhs4;

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

TTS_CASE("Check eve::nbtrue behavior on logical")
{
  size_t c = EVE_CARDINAL; 
  TTS_EQUAL(eve::nbtrue(eve::True<EVE_TYPE>()), c);
  TTS_EQUAL(eve::nbtrue(eve::False<EVE_TYPE>()), 0u);
}
