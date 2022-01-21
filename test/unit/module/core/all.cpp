//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/all.hpp>

#include "test.hpp"
#include <eve/function/all.hpp>
#include <eve/conditional.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

EVE_TEST_TYPES("Check eve::all return type", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  TTS_EXPR_IS( (eve::all(eve::logical<T>())) , bool);
  TTS_EXPR_IS( (eve::all(bool{})) , bool);
  TTS_EXPECT    ( (eve::all(true)) );
  TTS_EXPECT_NOT( (eve::all(false)) );
  TTS_EXPECT    (eve::all(eve::true_(eve::as<T>())));
  TTS_EXPECT_NOT(eve::all(eve::false_(eve::as<T>())));
};

EVE_TEST_TYPES("Check eve::all[ignore](simd)", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  // complete
  {
    eve::logical<T> mask(true);
    TTS_EXPECT(eve::all(mask));
    TTS_EXPECT(eve::all[eve::ignore_none](mask));

    mask = eve::logical<T>{false};
    TTS_EXPECT(eve::all[eve::ignore_all](mask));
  }

  // some special cases
  {
    eve::logical<T> mask(true);

    TTS_EXPECT(eve::all[eve::ignore_first(1)](mask));
    TTS_EXPECT(eve::all[eve::ignore_last(1)](mask));

    mask.set(0, false);
    TTS_EXPECT(eve::all[eve::ignore_first(1)](mask));
    TTS_EXPECT(eve::all[eve::ignore_last(T::size())](mask));
    TTS_EXPECT_NOT(eve::all[eve::ignore_last(T::size() - 1)](mask));
  }

  // every element
  {
    eve::logical<T> mask(true);

    for( int i = 0; i != T::size(); ++i)
    {
      mask.set(i, false);
      TTS_EXPECT_NOT(eve::all(mask));
      mask.set(i, true);
    }
  }

  // ignore_first, keep_last
  {
    eve::logical<T> mask(true);

    for(int i = 0; i != T::size(); ++i)
    {
      TTS_EXPECT(eve::all[eve::ignore_first(i)](mask));
      mask.set(i, false);
      TTS_EXPECT_NOT(eve::all[eve::ignore_first(i)](mask));
      TTS_EXPECT(eve::all[eve::ignore_first(i + 1)](mask));

      TTS_EXPECT_NOT(eve::all[eve::keep_last(T::size() - i)](mask));
      TTS_EXPECT(eve::all[eve::keep_last(T::size() - i - 1)](mask));
    }
  }

  // ignore_last
  {
    eve::logical<T> mask(true);

    for(int i = 0; i != T::size(); ++i)
    {
      TTS_EXPECT(eve::all[eve::ignore_last(i)](mask));
      mask.set(T::size() - i - 1, false);
      TTS_EXPECT_NOT(eve::all[eve::ignore_last(i)](mask));
      TTS_EXPECT(eve::all[eve::ignore_last(i + 1)](mask));

      TTS_EXPECT_NOT(eve::all[eve::keep_first(T::size() - i)](mask));
      TTS_EXPECT(eve::all[eve::keep_first(T::size() - i - 1)](mask));
    }
  }

  // ignore_extrema, keep_between
  {
    for (int i = 0; i < T::size() + 1; ++i)
    {
      for (int j = T::size() - i; j ; --j)
      {
        eve::logical<T> mask([&](int k, int) { return (k >= i) && (T::size() - k) > j; });
        TTS_EXPECT(eve::all[eve::ignore_extrema(i, j)](mask));

        if (i + j == T::size()) continue;

        mask.set(i, false);

        TTS_EXPECT_NOT(eve::all[eve::ignore_extrema(i, j)](mask));
        TTS_EXPECT(eve::all[eve::ignore_extrema(i + 1, j)](mask));

        TTS_EXPECT_NOT(eve::all[eve::keep_between(i, T::size() - j)](mask));
        TTS_EXPECT(eve::all[eve::keep_between(i + 1, T::size() - j)](mask));

        mask.set(i, true);

        mask.set(T::size() - j - 1, false);
        TTS_EXPECT_NOT(eve::all[eve::ignore_extrema(i, j)](mask));
        TTS_EXPECT(eve::all[eve::ignore_extrema(i, j + 1)](mask));

        TTS_EXPECT_NOT(eve::all[eve::keep_between(i, T::size() - j)](mask));
        TTS_EXPECT(eve::all[eve::keep_between(i, T::size() - j - 1)](mask));
      }
    }
  }
};
