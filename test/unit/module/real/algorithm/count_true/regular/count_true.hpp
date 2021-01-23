//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/count_true.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/platform.hpp>
#include <eve/logical.hpp>

TTS_CASE_TPL("Check eve::count_true return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::count_true(eve::logical<T>())) , std::ptrdiff_t);
  TTS_EXPR_IS( (eve::count_true(T()))               , std::ptrdiff_t);
}

TTS_CASE_TPL("Check eve::count_true behavior on arithmetic", EVE_TYPE)
{
  auto cardinal = EVE_CARDINAL;

  TTS_EQUAL(eve::count_true(T(1)), cardinal);
  TTS_EQUAL(eve::count_true(T(0)), 0u);

  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_nans )
    {
      TTS_EQUAL(eve::count_true(eve::nan(eve::as<T>())), cardinal);
    }

    TTS_EQUAL(eve::count_true(T(-0.)), 0u);
  }

#if defined(EVE_SIMD_TESTS)
  for(std::ptrdiff_t j=0; j<cardinal; ++j)
  {
    T rhs1,rhs2, rhs3, rhs4;

    for(std::ptrdiff_t i=0; i<cardinal; ++i)
    {
      rhs1.set(i, i >= j ? 1 : 0);
      rhs2.set(i, i <= j ? 0 : 1);
      rhs3.set(i, i == j ? 1 : 0);
      rhs4.set(i, i == j ? 0 : 1);
    }

    TTS_EQUAL(eve::count_true(rhs1), (cardinal-j)  );
    TTS_EQUAL(eve::count_true(rhs2), (cardinal-j-1));
    TTS_EQUAL(eve::count_true(rhs3), 1u                       );
    TTS_EQUAL(eve::count_true(rhs4), (cardinal-1u) );
  }
#endif
}

TTS_CASE_TPL("Check eve::count_true behavior on logical", EVE_TYPE)
{
  auto cardinal = EVE_CARDINAL;

  TTS_EQUAL(eve::count_true(eve::true_(eve::as<T>())) , cardinal);
  TTS_EQUAL(eve::count_true(eve::false_(eve::as<T>())), 0u      );
}
