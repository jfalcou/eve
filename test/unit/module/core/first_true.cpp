//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/first_true.hpp>

#include "test.hpp"
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>

#include <eve/conditional.hpp>

EVE_TEST_TYPES("Check eve::first_true return type", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  TTS_EXPR_IS( (eve::first_true(eve::logical<T>())), std::optional<std::ptrdiff_t>);
};

TTS_CASE("Check eve::first_true bool")
{
  TTS_EXPR_IS( (eve::first_true(bool{})) , std::optional<std::ptrdiff_t>);
  TTS_EQUAL  ( (eve::first_true(true)), 0 );
  TTS_EQUAL  ( (eve::first_true(false)), std::nullopt );
};

EVE_TEST_TYPES("Check eve::first_true behavior on logical", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  TTS_EQUAL(eve::first_true(eve::true_(eve::as<T>())), 0);
  TTS_EQUAL(eve::first_true(eve::false_(eve::as<T>())), std::nullopt);
};

EVE_TEST_TYPES("Check eve::first_true", eve::test::simd::all_types)
<typename T>(eve::as<T>)
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

    for (int i = 0; i != T::size(); ++i)
    {
      TTS_EQUAL(eve::first_true(x), i);
      TTS_EQUAL(eve::first_true[eve::ignore_none](x), i);
      x.set(i, false);
    }
  }

  // ignore first
  {
    l_t x(true);

    for (int i = 0; i != T::size(); ++i)
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

    for (int i = 0; i != T::size(); ++i)
    {
      x.set(i, true);

      auto ilast = eve::ignore_last(T::size() - i - 1);
      auto ilast_bigger = eve::ignore_last(T::size() - i);

      TTS_EQUAL(eve::first_true[ilast](x), i);
      TTS_EQUAL(eve::first_true[ilast_bigger](x), std::nullopt);

      if (i > 0)
      {
        auto iextrema = ilast && eve::ignore_first(i - 1);
        TTS_EQUAL(eve::first_true[iextrema](x), i);

        iextrema = ilast_bigger && eve::ignore_first(i - 1);
        TTS_EQUAL(eve::first_true[iextrema](x), std::nullopt);
      }

      x.set(i, false);
    }

    x = true;
    TTS_EQUAL(eve::first_true[eve::ignore_first(T::size())](x), std::nullopt);
  }
};
