//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <eve/function/scan.hpp>
#include <eve/function/min.hpp>

#include <algorithm>

EVE_TEST( "Check behavior of default scan"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-50, 50) )
        )
<typename T>(T simd)
{
  eve::element_type_t<T> sum = 0;
  T expected { [&] (int i, int) mutable
  {
    sum += simd.get(i);
    return sum;
  }};

  T actual = eve::scan(simd);

  if constexpr ( std::floating_point<eve::element_type_t<T>> )
  {
    T diff = eve::abs(expected - actual);
    T eps {0.0001};
    TTS_EXPECT(eve::all(diff < eps));
  }
  else
  {
    TTS_EQUAL(expected, actual);
  }
};

EVE_TEST( "Check behavior of scan with min"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-50, 50) )
        )
<typename T>(T simd)
{
  eve::element_type_t<T> sum = simd.get(0);
  T expected { [&] (int i, int) mutable
  {
    sum = std::min(simd.get(i), sum);
    return sum;
  }};

  T actual = eve::scan(simd, eve::min, simd.get(0));
  TTS_EQUAL(expected, actual);
};

EVE_TEST_TYPES( "Check behavior of scan for logicals", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  eve::logical<T> input    {[](int i, int) { return i != 3; }};
  eve::logical<T> expected {[](int i, int) { return i <  3; }};
  eve::logical<T> actual = eve::scan(input, eve::logical_and, true);
  TTS_EQUAL(expected, actual);
};
