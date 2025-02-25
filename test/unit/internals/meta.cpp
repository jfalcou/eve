//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/detail/meta.hpp>

constexpr int for_loop_count(int start, int step, int end)
{
  int count = 0;
  for (int i = start; i < end; i += step) ++count;
  return count;
}

TTS_CASE("eve::detail::for_")
{
  {
    int i = 0;
    eve::detail::for_<0, 1, 4>([&](auto j) mutable {
      TTS_EXPECT(i == j());
      ++i;
    });

    TTS_EQUAL(i, for_loop_count(0, 1, 4));
  }

  {
    int i = 0;
    eve::detail::for_<2, 1, 4>([&](auto j) mutable {
      TTS_EXPECT(i + 2 == j());
      ++i;
    });

    TTS_EQUAL(i, for_loop_count(2, 1, 4));
  }

  {
    int i = 0;
    eve::detail::for_<20, 10, 40>([&](auto j) mutable {
      TTS_EXPECT(i * 10 + 20 == j());
      ++i;
    });

    TTS_EQUAL(i, for_loop_count(20, 10, 40));
  }

  {
    int i = 0;
    eve::detail::for_<0, 2, 5>([&](auto j) mutable {
      TTS_EQUAL(i * 2, j());
      ++i;
    });

    TTS_EQUAL(i, for_loop_count(0, 2, 5));
  }
};

TTS_CASE("eve::detail::for_until_")
{
  {
    int i = 0;
    bool res = eve::detail::for_until_<0, 1, 4>([&](auto j) mutable {
      TTS_EQUAL(i, j());
      ++i;
      return false;
    });

    TTS_EXPECT_NOT(res);
    TTS_EQUAL(i, 4);
  }

  {
    int i = 0;
    bool res = eve::detail::for_until_<0, 2, 8>([&](auto j) mutable {
      TTS_EQUAL(i, j());
      i += 2;
      return i == 4;
    });

    TTS_EXPECT(res);
    TTS_EQUAL(i, 4);
  }

  {
    int i = 0;
    bool res = eve::detail::for_until_<0, 2, 8>([&](auto j) mutable {
      TTS_EQUAL(i, j());
      i += 2;
      return false;
    });

    TTS_EXPECT_NOT(res);
    TTS_EQUAL(i, 8);
  }

  {
    int i = 0;
    bool res = eve::detail::for_until_<20, 10, 40>([&](auto j) mutable {
      TTS_EQUAL(i * 10 + 20, j());
      ++i;
      return false;
    });
    
    TTS_EXPECT_NOT(res);
    TTS_EQUAL(i, 2);
  }

  {
    int i = 0;
    bool res = eve::detail::for_until_<0, 2, 11>([&](auto j) mutable {
      TTS_EQUAL(i * 2, j());
      ++i;
      return i == 4;
    });
    
    TTS_EXPECT(res);
    TTS_EQUAL(i, 4);
  }
};
