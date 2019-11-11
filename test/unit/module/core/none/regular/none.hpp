//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/none.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/platform.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::none return type")
{
  TTS_EXPR_IS( (eve::none(eve::logical<Type>())) , bool);
  TTS_EXPR_IS( (eve::none(Type()))               , bool);
}

TTS_CASE("Check eve::none behavior on arithmetic")
{
  TTS_EXPECT_NOT    ( (eve::none(Type{1})) );
  TTS_EXPECT      ( (eve::none(Type{0})) );

  if constexpr(std::is_floating_point_v<Value>)
  {
    if constexpr( eve::platform::supports_nans )
    {
      TTS_EXPECT_NOT(eve::none(eve::Nan<Type>()));
    }

    TTS_EXPECT(eve::none(eve::Mzero<Type>()));
  }

#if defined(EVE_SIMD_TESTS)
  for(int j=0; j < Cardinal; ++j)
  {
    Type rhs1,rhs2, rhs3, rhs4;

    for(int i=0; i< Cardinal; ++i)
    {
      rhs1[i] = i >= j ? 1 : 0;
      rhs2[i] = i <= j ? 0 : 1;
      rhs3[i] = i == j ? 1 : 0;
      rhs4[i] = i == j ? 0 : 1;
    }

    TTS_EXPECT_NOT(eve::none(rhs1));
    if (Cardinal != j+1) TTS_EXPECT_NOT(eve::none(rhs2));
    else               TTS_EXPECT(eve::none(rhs2));
    TTS_EXPECT_NOT(eve::none(rhs3));

    if constexpr(Cardinal == 1) TTS_EXPECT(eve::none(rhs4));
    else                        TTS_EXPECT_NOT(eve::none(rhs4));
  }
#endif
}

TTS_CASE("Check eve::none behavior on logical")
{
  TTS_EXPECT_NOT    (eve::none(eve::True<Type>()));
  TTS_EXPECT        (eve::none(eve::False<Type>()));
}
