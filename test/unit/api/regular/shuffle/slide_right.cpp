//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>


//==================================================================================================
// slide_right test
//==================================================================================================

TTS_CASE_TPL("Check behavior of slide_right shuffle", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  T x{[](int i, int size) { return i - size; }};
  T y{[](int i, int     ) { return i; }};

  eve::logical<T> lx = x < -3;
  eve::logical<T> ly = y < 4;

  eve::detail::for_<0, 1, T::size()>(
    [&]<int Shift>(std::integral_constant<int, Shift>) {
      T expected([](int i, int) { return i - Shift; });
      T actual = eve::slide_right(x, y, eve::index<Shift>);
      TTS_EQUAL(expected, actual);

      eve::logical<T> lexpected([](int i, int) {
        int full_i = i - Shift;
        if (full_i < 0) return full_i < -3;
        else            return full_i < 4;
      });
      eve::logical<T> lactual = eve::slide_right(lx, ly, eve::index<Shift>);

      TTS_EQUAL(lexpected, lactual);
    }
  );
};

TTS_CASE("Check behaviour of slide_right, 4 ints")
{
  // Special case to check if everything makes sense
  using T = eve::wide<int, eve::fixed<4>>;

  T x{-4, -3, -2, -1};
  T y{0,   1,  2,  3};

  T shift_0 = {0,   1,  2,   3};
  T shift_1 = {-1,  0,  1,   2};
  T shift_2 = {-2, -1,  0,   1};
  T shift_3 = {-3, -2,  -1,  0};
  T shift_4 = {-4, -3,  -2, -1};

  TTS_EQUAL(shift_0, (eve::slide_right(x, y, eve::index<0>)));
  TTS_EQUAL(shift_1, (eve::slide_right(x, y, eve::index<1>)));
  TTS_EQUAL(shift_2, (eve::slide_right(x, y, eve::index<2>)));
  TTS_EQUAL(shift_3, (eve::slide_right(x, y, eve::index<3>)));
  TTS_EQUAL(shift_4, (eve::slide_right(x, y, eve::index<4>)));
};
