//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
}

TTS_CASE_TPL("Check eve::count_true behavior", EVE_TYPE)
{
  auto cardinal = EVE_CARDINAL;

  TTS_EQUAL(eve::count_true(eve::true_(eve::as<T>())) , cardinal);
  TTS_EQUAL(eve::count_true(eve::false_(eve::as<T>())), 0       );

#if defined(EVE_SIMD_TESTS)
  for(std::ptrdiff_t j=0; j<cardinal; ++j)
  {
    eve::logical<T> rhs1,rhs2, rhs3, rhs4;

    for(std::ptrdiff_t i=0; i<cardinal; ++i)
    {
      rhs1.set(i, i >= j ? true : false);
      rhs2.set(i, i <= j ? false : true);
      rhs3.set(i, i == j ? true : false);
      rhs4.set(i, i == j ? false : true);
    }

    TTS_EQUAL(eve::count_true(rhs1), (cardinal-j)  );
    TTS_EQUAL(eve::count_true(rhs2), (cardinal-j-1));
    TTS_EQUAL(eve::count_true(rhs3), 1             );
    TTS_EQUAL(eve::count_true(rhs4), (cardinal-1)  );
  }
#endif
}

#if defined(EVE_SIMD_TESTS)
TTS_CASE_TPL("Check eve::count_true behavior with ignore", EVE_TYPE)
{
  eve::logical<T> data(true);

  TTS_EQUAL( eve::count_true[eve::ignore_none](data)                  , EVE_CARDINAL  );
  TTS_EQUAL( eve::count_true[eve::ignore_all](data)                   , 0             );
  TTS_EQUAL( eve::count_true[eve::ignore_first(EVE_CARDINAL-1)](data) , 1             );
  TTS_EQUAL( eve::count_true[eve::keep_first  (EVE_CARDINAL-1)](data) , EVE_CARDINAL-1);
  TTS_EQUAL( eve::count_true[eve::ignore_last (EVE_CARDINAL-1)](data) , 1             );
  TTS_EQUAL( eve::count_true[eve::keep_last   (EVE_CARDINAL-1)](data) , EVE_CARDINAL-1);

  if constexpr(EVE_CARDINAL >= 2)
  {
    TTS_EQUAL( eve::count_true[eve::ignore_first(1) && eve::ignore_last(1)](data), EVE_CARDINAL-2);
  }
  else
  {
    TTS_EQUAL( eve::count_true[eve::ignore_first(1) && eve::ignore_last(1)](data), 0);
  }
}
#endif
