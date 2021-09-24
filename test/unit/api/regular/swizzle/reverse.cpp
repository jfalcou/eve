//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/function/reverse.hpp>
#include <eve/wide.hpp>

namespace {

template <typename T>
void reverse_test(T x) {
  T expected([&](int i, int size) { return x.get(size - i - 1); });
  TTS_EQUAL(eve::reverse(x), expected);
}

EVE_TEST( "Check behavior of reverse"
        , eve::test::simd::restricted::all_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::logicals(0,3))
        )
<typename T, typename L>(T const& a, L const& l)
{
  reverse_test(a);
  reverse_test(l);
};

}
