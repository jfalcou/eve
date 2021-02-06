//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU
  Copyright 2021 Jean-Thierry LAPRESTE
  Copyright 2021 Denis YAROSHEVSKIY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/first_true.hpp>

#include <eve/conditional.hpp>

#if defined(EVE_SIMD_TESTS)

TTS_CASE_TPL("Check eve::first_true", EVE_TYPE)
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

    for (int i = 0; i != T::static_size; ++i)
    {
      TTS_EQUAL(eve::first_true(x), i);
      TTS_EQUAL(eve::first_true[eve::ignore_none](x), i);
      x.set(i, false);
    }
  }

  // ignore first
  {
    l_t x(true);

    for (int i = 0; i != T::static_size; ++i)
    {
      auto ifirst = eve::ignore_first(i);
      TTS_EQUAL(eve::first_true[ifirst](x), i);

      auto iextrema = ifirst && eve::ignore_last(T::static_size - i - 1);
      TTS_EQUAL(eve::first_true[iextrema](x), i);

    }
    TTS_EQUAL(eve::first_true[eve::ignore_first(T::static_size)](x), std::nullopt);
  }

  // ignore last
  {
    l_t x(false);

    for (int i = 0; i != T::static_size; ++i)
    {
      x.set(i, true);

      auto ilast = eve::ignore_last(T::static_size - i - 1);
      auto ilast_bigger = eve::ignore_last(T::static_size - i);

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
    TTS_EQUAL(eve::first_true[eve::ignore_first(T::static_size)](x), std::nullopt);
  }
}


#endif
