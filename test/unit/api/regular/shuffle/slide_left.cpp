//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
// slide_left test
//==================================================================================================
EVE_TEST_TYPES("Check behavior of slide_left shuffle", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  T x{[](int i, int)      { return i; }};
  T y{[](int i, int size) { return i + size; }};

  eve::logical<T> lx = x < 2;
  eve::logical<T> ly = y < 6;

  eve::detail::for_<0, 1, T::size()>(
    [&]<int Shift>(std::integral_constant<int, Shift>) {
    T expected([](int i, int) { return i + Shift; });
    T actual = eve::slide_left(x, y, eve::index<Shift>);
    TTS_EQUAL(expected, actual);

    eve::logical<T> lexpected([](int i, int size) {
      if ( i < size - Shift ) return (i + Shift) < 2;
      else                    return v_t(i + Shift) < 6;
    });
    eve::logical<T> lactual = eve::slide_left(lx, ly, eve::index<Shift>);

    TTS_EQUAL(lexpected, lactual);
  });
};
