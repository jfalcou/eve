//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/algo/unroll_op.hpp>

TTS_CASE("eve.algo check unroll op") {
  {
    int i = 0;
    eve::algo::unroll_op<4>([&]<std::ptrdiff_t j>(eve::index_t<j>)mutable {
      TTS_EXPECT(i == j);
      ++i;
      return false;
    });
    TTS_EXPECT(i == 4);
  }
  {
    int i = 0;
    eve::algo::unroll_op<4>([&]<std::ptrdiff_t j>(eve::index_t<j>)mutable {
      TTS_EXPECT(i == j);
      ++i;
      return i == 2;
    });
    TTS_EXPECT(i == 2);
  }
}
