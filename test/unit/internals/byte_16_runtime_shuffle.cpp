//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/detail/function/byte_16_runtime_shuffle.hpp>


EVE_TEST_TYPES("byte 16 runtime shuffle 4 elements",
               eve::test::simd::uints_8)
<typename T>(eve::as<T>)
{
  if constexpr (T::size() > 16)
  {
    TTS_PASS("bigger than 16 bytes");
  }
  else
  {
    T what([](int i, int) { return -i; });
    T pattern([](int i, int) { return i / 2; });
    T actual = eve::detail::byte_16_runtime_shuffle(what, pattern);
    T expected = -pattern;

    TTS_EQUAL(actual, expected);
  }
};
