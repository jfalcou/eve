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

TTS_CASE("Check eve::nbtrue return type")
{
  TTS_EXPR_IS( (eve::nbtrue(eve::logical<EVE_TYPE>())) , std::size_t);
  TTS_EXPR_IS( (eve::nbtrue(EVE_TYPE()))               , std::size_t);
}

TTS_CASE("Check eve::nbtrue behavior on arithmetic")
{
  auto cardinal = static_cast<std::size_t>(EVE_CARDINAL);

  TTS_EQUAL(eve::nbtrue(EVE_TYPE(1)), cardinal);
  TTS_EQUAL(eve::nbtrue(EVE_TYPE(0)), 0u);

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    if constexpr( eve::platform::supports_nans )
    {
      TTS_EQUAL(eve::nbtrue(eve::nan(eve::as<EVE_TYPE>())), cardinal);
    }

    TTS_EQUAL(eve::nbtrue(EVE_TYPE(-0.)), 0u);
  }

#if defined(EVE_SIMD_TESTS)
  for(std::size_t j=0; j<cardinal; ++j)
  {
    EVE_TYPE rhs1,rhs2, rhs3, rhs4;

    for(std::size_t i=0; i<cardinal; ++i)
    {
      rhs1.set(i, i >= j ? 1 : 0);
      rhs2.set(i, i <= j ? 0 : 1);
      rhs3.set(i, i == j ? 1 : 0);
      rhs4.set(i, i == j ? 0 : 1);
    }

    TTS_EQUAL(eve::nbtrue(rhs1), std::size_t(cardinal-j)  );
    TTS_EQUAL(eve::nbtrue(rhs2), std::size_t(cardinal-j-1));
    TTS_EQUAL(eve::nbtrue(rhs3), 1u                       );
    TTS_EQUAL(eve::nbtrue(rhs4), std::size_t(cardinal-1u) );
  }
#endif
}

TTS_CASE("Check eve::nbtrue behavior on logical")
{
  auto cardinal = static_cast<std::size_t>(EVE_CARDINAL);

  TTS_EQUAL(eve::nbtrue(eve::true_ (eve::as<EVE_TYPE>())), cardinal);
  TTS_EQUAL(eve::nbtrue(eve::false_(eve::as<EVE_TYPE>())), 0u      );
}
