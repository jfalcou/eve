//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <eve/function/count_true.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/platform.hpp>
#include <eve/logical.hpp>

EVE_TEST_TYPES("Check eve::count_true return type", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  TTS_EXPR_IS( (eve::count_true(eve::logical<T>())) , std::ptrdiff_t);
};

EVE_TEST_TYPES("Check eve::count_true behavior", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  constexpr auto cardinal = eve::cardinal_v<T>;

  TTS_EQUAL(eve::count_true(eve::true_(eve::as<T>())) , cardinal);
  TTS_EQUAL(eve::count_true(eve::false_(eve::as<T>())), 0       );

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
};

EVE_TEST_TYPES("Check eve::count_true behavior with ignore", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  eve::logical<T> data(true);
  constexpr auto cardinal = eve::cardinal_v<T>;

  TTS_EQUAL( eve::count_true[eve::ignore_none](data)                  , cardinal  );
  TTS_EQUAL( eve::count_true[eve::ignore_all](data)                   , 0             );
  TTS_EQUAL( eve::count_true[eve::ignore_first(cardinal-1)](data) , 1             );
  TTS_EQUAL( eve::count_true[eve::keep_first  (cardinal-1)](data) , cardinal-1);
  TTS_EQUAL( eve::count_true[eve::ignore_last (cardinal-1)](data) , 1             );
  TTS_EQUAL( eve::count_true[eve::keep_last   (cardinal-1)](data) , cardinal-1);

  if constexpr(cardinal >= 2)
  {
    TTS_EQUAL( eve::count_true[eve::ignore_first(1) && eve::ignore_last(1)](data), cardinal-2);
  }
  else
  {
    //   TTS_EQUAL( eve::count_true[eve::ignore_first(1) && eve::ignore_last(1)](data), 0);
  }
};

EVE_TEST_TYPES("Check eve::count_true top_bits", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  eve::logical<T> x(false);

  auto test = [&] {
    std::ptrdiff_t expected = 0;
    for (int i = 0; i != x.size(); ++i) expected += x.get(i);

    eve::top_bits mmask{x};
    TTS_EQUAL(expected, eve::count_true(mmask));
  };

  for (int i = 0; i != x.size(); ++i)
  {
    x.set(i, true);
    test();

    for (int j = i + 1; j < x.size(); ++j)
    {
      x.set(j, true);
      test();
      x.set(j, false);
    }

    x.set(i, false);
  }
};
