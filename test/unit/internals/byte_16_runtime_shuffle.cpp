//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/detail/function/byte_16_runtime_shuffle.hpp>

TTS_CASE_TPL("byte 16 runtime shuffle 4 elements", eve::test::wides_t<tts::types<std::uint8_t>>)
<typename T>(tts::type<T>)
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
