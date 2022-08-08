//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

#include <eve/wide.hpp>

namespace {

template <typename T>
void reverse_test(T x)
{
  T expected([&](int i, int size) { return x.get(size - i - 1); });
  TTS_EQUAL(eve::reverse(x), expected);
  TTS_EQUAL(eve::shuffle(x, eve::as_pattern([](auto i, auto c) { return c-i-1;})), expected);
}

TTS_CASE_WITH( "Check behavior of reverse"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              , tts::logicals(0,3))
        )
<typename T, typename L>(T const& a, L const& l)
{
  reverse_test(a);
  reverse_test(l);
};

}
