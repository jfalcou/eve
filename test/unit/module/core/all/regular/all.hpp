//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/all.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/platform.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check all return type")
{
  TTS_EXPR_IS( (eve::all(eve::logical<Type>())) , bool);
  TTS_EXPR_IS( (eve::all(Type()))               , bool);
}

TTS_CASE("Check eve::all behavior on arithmetic")
{
  TTS_EXPECT    ( (eve::all(Type{1})) );
  TTS_EXPECT_NOT( (eve::all(Type{0})) );

  if constexpr(std::is_floating_point_v<Value>)
  {
    if constexpr( eve::platform::supports_nans )
    {
      TTS_EXPECT(eve::all(eve::Nan<Type>()));
    }

    TTS_EXPECT_NOT(eve::all(eve::Mzero<Type>()));
  }

#if defined(EVE_SIMD_TESTS)
  for(int j=0; j < Cardinal; ++j)
  {
    Type rhs1,rhs2, rhs3, rhs4;

    for(int i=0; i< Cardinal; ++i)
    {
      rhs1[i] = i >= j ? 0 : 1;
      rhs2[i] = i <= j ? 0 : 1;
      rhs3[i] = i == j ? 0 : 1;
      rhs4[i] = i == j ? 1 : 0;
    }

    TTS_EXPECT_NOT(eve::all(rhs1));
    TTS_EXPECT_NOT(eve::all(rhs2));
    TTS_EXPECT_NOT(eve::all(rhs3));

    if constexpr(Cardinal == 1) TTS_EXPECT(eve::all(rhs4));
    else                        TTS_EXPECT_NOT(eve::all(rhs4));
  }
#endif
}

TTS_CASE("Check eve::all behavior on logical")
{
  TTS_EXPECT    (eve::all(eve::True<Type>()));
  TTS_EXPECT_NOT(eve::all(eve::False<Type>()));
}
