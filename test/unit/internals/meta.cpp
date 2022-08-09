//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/detail/meta.hpp>

TTS_CASE("eve::detail::for_until_") {
  {
    int i = 0;
    bool res = eve::detail::for_until_<0, 1, 4>([&](auto j)mutable {
      TTS_EXPECT(i == j());
      ++i;
      return false;
    });
    TTS_EXPECT_NOT(res);
    TTS_EXPECT(i == 4);
  }
  {
    int i = 0;
    bool res = eve::detail::for_until_<0, 2, 8>([&](auto j) mutable {
      TTS_EXPECT(i == j());
      i += 2;
      return i == 4;
    });
    TTS_EXPECT(res);
    TTS_EXPECT(i == 4);
  }
  {
    int i = 0;
    bool res = eve::detail::for_until_<0, 2, 8>([&](auto j) mutable {
      TTS_EXPECT(i == j());
      i += 2;
      return false;
    });
    TTS_EXPECT_NOT(res);
    TTS_EXPECT(i == 8);
  }
};
