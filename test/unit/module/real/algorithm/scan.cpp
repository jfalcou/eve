//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <eve/function/scan.hpp>
#include <eve/function/store.hpp>
#include <eve/function/min.hpp>

#include <algorithm>
#include <array>

template <typename T, typename Op>
T std_scan(T simd, Op op)
{
  using e_t = eve::element_type_t<T>;

  std::array<e_t, T::size()> arr;
  eve::store(simd, arr.data());
  std::inclusive_scan(arr.begin(), arr.end(), arr.begin(), op);

  return T{arr.data()};
}

EVE_TEST( "Check behavior of default scan"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-50, 50) )
        )
<typename T>(T simd)
{
  T expected = std_scan(simd, eve::plus);
  T actual = eve::scan(simd);

  TTS_RELATIVE_EQUAL(expected, actual, 0.0001);
};

EVE_TEST( "Check behavior of scan with min"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-50, 50) )
        )
<typename T>(T simd)
{
  T expected = std_scan(simd, eve::min);
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
