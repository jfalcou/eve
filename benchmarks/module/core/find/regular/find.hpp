//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/find.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/platform.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::find return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::find(eve::logical<T>())) , std::size_t);
  TTS_EXPR_IS( (eve::find(T()))               , std::size_t);
}

TTS_CASE_TPL("Check eve::find behavior on arithmetic", EVE_TYPE)
{
  auto cardinal = static_cast<std::size_t>(EVE_CARDINAL);

  TTS_EQUAL(eve::find(T(1)), cardinal);
  TTS_EQUAL(eve::find(T(0)), 0u);

  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_nans )
    {
      TTS_EQUAL(eve::find(eve::Nan<T>()), cardinal);
    }

    TTS_EQUAL(eve::find(T(-0.)), 0u);
  }

#if defined(EVE_SIMD_TESTS)
  for(std::size_t j=0; j<cardinal; ++j)
  {
    T rhs1,rhs2, rhs3, rhs4;

    for(std::size_t i=0; i<cardinal; ++i)
    {
      rhs1[i] = i >= j ? 1 : 0;
      rhs2[i] = i <= j ? 0 : 1;
      rhs3[i] = i == j ? 1 : 0;
      rhs4[i] = i == j ? 0 : 1;
    }

    TTS_EQUAL(eve::find(rhs1), std::size_t(cardinal-j)  );
    TTS_EQUAL(eve::find(rhs2), std::size_t(cardinal-j-1));
    TTS_EQUAL(eve::find(rhs3), 1u                       );
    TTS_EQUAL(eve::find(rhs4), std::size_t(cardinal-1u) );
  }
#endif
}

TTS_CASE_TPL("Check eve::find behavior on logical", EVE_TYPE)
{
  auto cardinal = static_cast<std::size_t>(EVE_CARDINAL);

  TTS_EQUAL(eve::find(eve::True<T>()) , cardinal);
  TTS_EQUAL(eve::find(eve::False<T>()), 0u      );
}
