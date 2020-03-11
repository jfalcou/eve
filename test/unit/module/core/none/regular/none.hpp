//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
  TTS_EXPR_IS( (eve::none(eve::logical<EVE_TYPE>())) , bool);
  TTS_EXPR_IS( (eve::none(EVE_TYPE()))               , bool);
}

TTS_CASE("Check eve::none behavior on arithmetic")
{
  TTS_EXPECT_NOT    ( (eve::none(EVE_TYPE{1})) );
  TTS_EXPECT      ( (eve::none(EVE_TYPE{0})) );

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    if constexpr( eve::platform::supports_nans )
    {
      TTS_EXPECT_NOT(eve::none(eve::Nan<EVE_TYPE>()));
    }

    TTS_EXPECT(eve::none(eve::Mzero<EVE_TYPE>()));
  }

#if defined(EVE_SIMD_TESTS)
  for(int j=0; j < EVE_CARDINAL; ++j)
  {
    EVE_TYPE rhs1,rhs2, rhs3, rhs4;

    for(int i=0; i< EVE_CARDINAL; ++i)
    {
      rhs1[i] = i >= j ? 1 : 0;
      rhs2[i] = i <= j ? 0 : 1;
      rhs3[i] = i == j ? 1 : 0;
      rhs4[i] = i == j ? 0 : 1;
    }

    TTS_EXPECT_NOT(eve::none(rhs1));
    if (EVE_CARDINAL != j+1) TTS_EXPECT_NOT(eve::none(rhs2));
    else               TTS_EXPECT(eve::none(rhs2));
    TTS_EXPECT_NOT(eve::none(rhs3));

    if constexpr(EVE_CARDINAL == 1) TTS_EXPECT(eve::none(rhs4));
    else                        TTS_EXPECT_NOT(eve::none(rhs4));
  }
#endif
}

TTS_CASE("Check eve::none behavior on logical")
{
  TTS_EXPECT_NOT    (eve::none(eve::True<EVE_TYPE>()));
  TTS_EXPECT        (eve::none(eve::False<EVE_TYPE>()));
}
