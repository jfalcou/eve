//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

TTS_CASE_TPL("Check eve::any return type", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::any(eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::any(bool {})), bool);
  TTS_EXPECT((eve::any(true)));
  TTS_EXPECT_NOT((eve::any(false)));
  TTS_EXPECT(eve::any(eve::true_(eve::as<T>())));
  TTS_EXPECT_NOT(eve::any(eve::false_(eve::as<T>())));
};

TTS_CASE_TPL("Check eve::any[ignore]", eve::test::simd::all_types)
<typename T>(tts::type<T>) {// complete
                            {eve::logical<T> mask(false);

TTS_EXPECT_NOT(eve::any(mask));
TTS_EXPECT_NOT(eve::any[eve::ignore_none](mask));
TTS_EXPECT_NOT(eve::any[eve::ignore_all](mask));

mask.set(0, true);

TTS_EXPECT(eve::any(mask));
TTS_EXPECT(eve::any[eve::ignore_none](mask));
TTS_EXPECT_NOT(eve::any[eve::ignore_all](mask));
}

// some special cases
{
  eve::logical<T> mask(false);

  TTS_EXPECT_NOT(eve::any[eve::ignore_first(1)](mask));
  TTS_EXPECT_NOT(eve::any[eve::ignore_last(1)](mask));

  mask.set(0, true);
  TTS_EXPECT_NOT(eve::any[eve::ignore_first(1)](mask));
  TTS_EXPECT_NOT(eve::any[eve::ignore_last(T::size())](mask));
  TTS_EXPECT(eve::any[eve::ignore_last(T::size() - 1)](mask));
}

// every element
{
  eve::logical<T> mask(false);

  for( int i = 0; i != T::size(); ++i )
  {
    mask.set(i, true);
    TTS_EXPECT(eve::any(mask));
    mask.set(i, false);
  }
}

// ignore_first
{
  eve::logical<T> mask(false);

  for( int i = 0; i != T::size(); ++i )
  {
    TTS_EXPECT_NOT(eve::any[eve::ignore_first(i)](mask));
    mask.set(i, true);
    TTS_EXPECT(eve::any[eve::ignore_first(i)](mask));
    TTS_EXPECT_NOT(eve::any[eve::ignore_first(i + 1)](mask));
  }
}

// ignore_last
{
  eve::logical<T> mask(false);

  for( int i = 0; i != T::size(); ++i )
  {
    TTS_EXPECT_NOT(eve::any[eve::ignore_last(i)](mask));
    mask.set(T::size() - i - 1, true);
    TTS_EXPECT(eve::any[eve::ignore_last(i)](mask));
    TTS_EXPECT_NOT(eve::any[eve::ignore_last(i + 1)](mask));
  }
}

// ignore_extrema
{
  for( int i = 0; i < T::size() + 1; ++i )
  {
    for( int j = T::size() - i; j; --j )
    {
      eve::logical<T> mask([&](int k, int) { return (k < i) || (T::size() - k) < j; });
      TTS_EXPECT_NOT(eve::any[eve::ignore_extrema(i, j)](mask));

      if( i + j == T::size() ) continue;

      mask.set(i, true);

      TTS_EXPECT(eve::any[eve::ignore_extrema(i, j)](mask));
      TTS_EXPECT_NOT(eve::any[eve::ignore_extrema(i + 1, j)](mask));
      mask.set(i, false);

      mask.set(T::size() - j - 1, true);
      TTS_EXPECT(eve::any[eve::ignore_extrema(i, j)](mask));
      TTS_EXPECT_NOT(eve::any[eve::ignore_extrema(i, j + 1)](mask));
    }
  }
}
}
;

TTS_CASE_TPL("Check any(top_bits)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using logical = eve::logical<T>;
  TTS_EXPECT_NOT(eve::any(eve::top_bits(logical(false))));

  for( int i = 0; i != T::size(); ++i )
  {
    logical v([=](auto e, auto) { return e == i; });
    TTS_EXPECT(eve::any(eve::top_bits(v)));
  }
};
