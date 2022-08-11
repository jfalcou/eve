//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check eve::last_true return type", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::last_true(eve::logical<T>())), std::optional<std::ptrdiff_t>);
};

TTS_CASE("Check eve::last_true bool")
{
  TTS_EXPR_IS((eve::last_true(bool {})), std::optional<std::ptrdiff_t>);
  TTS_EQUAL((eve::last_true(true)), 0);
  TTS_EQUAL((eve::last_true(false)), std::nullopt);
};

TTS_CASE_TPL("Check eve::last_true behavior on logical", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::last_true(eve::true_(eve::as<T>())), T::size() - 1);
  TTS_EQUAL(eve::last_true(eve::false_(eve::as<T>())), std::nullopt);
};

TTS_CASE_TPL("Check eve::last_true", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using l_t = eve::logical<T>;

  // false
  {
    l_t x(false);
    TTS_EQUAL(eve::last_true(x), std::nullopt);
    TTS_EQUAL(eve::last_true[eve::ignore_none](x), std::nullopt);
  }

  // ignore_all
  {
    l_t x(true);
    TTS_EQUAL(eve::last_true[eve::ignore_all](x), std::nullopt);
  }

  // no ignore/ignore none
  {
    l_t x(false);

    for( int i = 0; i != T::size(); ++i )
    {
      x.set(i, true);
      TTS_EQUAL(eve::last_true(x), i);
      TTS_EQUAL(eve::last_true[eve::ignore_none](x), i);
    }
  }

  // ignore first
  {
    l_t x(false);

    for( int i = 0; i != T::size(); ++i )
    {
      x.set(i, true);

      auto ifirst        = eve::ignore_first(i);
      auto ifirst_bigger = eve::ignore_first(i + 1);

      TTS_EQUAL(eve::last_true[ifirst](x), i);
      TTS_EQUAL(eve::last_true[ifirst_bigger](x), std::nullopt);

      if( i > 0 )
      {
        auto iextrema = ifirst && eve::ignore_last(T::size() - i - 1);
        TTS_EQUAL(eve::last_true[iextrema](x), i);

        iextrema = ifirst_bigger && eve::ignore_last(T::size() - i - 1);
        TTS_EQUAL(eve::last_true[iextrema](x), std::nullopt);
      }

      x.set(i, false);
    }

    x = true;
    TTS_EQUAL(eve::last_true[eve::ignore_first(T::size())](x), std::nullopt);
  }

  // ignore last
  {
    l_t x(true);

    for( int i = 0; i != T::size(); ++i )
    {
      auto ilast = eve::ignore_last(T::size() - i - 1);
      TTS_EQUAL(eve::last_true[ilast](x), i);

      auto iextrema = eve::ignore_first(i) && ilast;
      TTS_EQUAL(eve::first_true[iextrema](x), i);
    }
    TTS_EQUAL(eve::first_true[eve::ignore_last(T::size())](x), std::nullopt);
  }
};

TTS_CASE_TPL("Check last_true(top_bits)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using logical = eve::logical<T>;
  TTS_EQUAL(T::size() - 1, eve::last_true(eve::top_bits(logical(true))));

  for( int i = 0; i != T::size() - 1; ++i )
  {
    logical       v([=](auto e, auto) { return e <= i; });
    std::optional res = eve::last_true(eve::top_bits(v));
    TTS_EXPECT(res);

    int expected = i;
    TTS_EQUAL(expected, *res);
  }

  TTS_EXPECT_NOT(eve::last_true(eve::top_bits(logical(false))));
};
