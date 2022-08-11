//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check eve::first_true return type", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::first_true(eve::logical<T>())), std::optional<std::ptrdiff_t>);
};

TTS_CASE("Check eve::first_true bool")
{
  TTS_EXPR_IS((eve::first_true(bool {})), std::optional<std::ptrdiff_t>);
  TTS_EQUAL((eve::first_true(true)), 0);
  TTS_EQUAL((eve::first_true(false)), std::nullopt);
};

TTS_CASE_TPL("Check eve::first_true behavior on logical", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::first_true(eve::true_(eve::as<T>())), 0);
  TTS_EQUAL(eve::first_true(eve::false_(eve::as<T>())), std::nullopt);
};

TTS_CASE_TPL("Check eve::first_true", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using l_t = eve::logical<T>;

  // false
  {
    l_t x(false);
    TTS_EQUAL(eve::first_true(x), std::nullopt);
    TTS_EQUAL(eve::first_true[eve::ignore_none](x), std::nullopt);
  }

  // ignore_all
  {
    l_t x(true);
    TTS_EQUAL(eve::first_true[eve::ignore_all](x), std::nullopt);
  }

  // no ignore/ignore none
  {
    l_t x(true);

    for( int i = 0; i != T::size(); ++i )
    {
      TTS_EQUAL(eve::first_true(x), i);
      TTS_EQUAL(eve::first_true[eve::ignore_none](x), i);
      x.set(i, false);
    }
  }

  // ignore first
  {
    l_t x(true);

    for( int i = 0; i != T::size(); ++i )
    {
      auto ifirst = eve::ignore_first(i);
      TTS_EQUAL(eve::first_true[ifirst](x), i);

      auto iextrema = ifirst && eve::ignore_last(T::size() - i - 1);
      TTS_EQUAL(eve::first_true[iextrema](x), i);
    }
    TTS_EQUAL(eve::first_true[eve::ignore_first(T::size())](x), std::nullopt);
  }

  // ignore last
  {
    l_t x(false);

    for( int i = 0; i != T::size(); ++i )
    {
      x.set(i, true);

      auto ilast        = eve::ignore_last(T::size() - i - 1);
      auto ilast_bigger = eve::ignore_last(T::size() - i);

      TTS_EQUAL(eve::first_true[ilast](x), i);
      TTS_EQUAL(eve::first_true[ilast_bigger](x), std::nullopt);

      if( i > 0 )
      {
        auto iextrema = ilast && eve::ignore_first(i - 1);
        TTS_EQUAL(eve::first_true[iextrema](x), i);

        iextrema = ilast_bigger && eve::ignore_first(i - 1);
        TTS_EQUAL(eve::first_true[iextrema](x), std::nullopt);
      }

      x.set(i, false);
    }

    x = true;
    TTS_EQUAL(eve::first_true[eve::ignore_last(T::size())](x), std::nullopt);
  }
};

TTS_CASE_TPL("Check first_true(top_bits)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using logical = eve::logical<T>;
  TTS_EQUAL(0, eve::first_true(eve::top_bits(logical(true))));

  for( int i = 0; i != T::size() - 1; ++i )
  {
    logical       v([=](auto e, auto) { return e > i; });
    std::optional res = eve::first_true(eve::top_bits(v));
    TTS_EXPECT(res);

    int expected = i + 1;
    TTS_EQUAL(expected, *res);
  }

  TTS_EXPECT_NOT(eve::first_true(eve::top_bits(logical(false))));
};
