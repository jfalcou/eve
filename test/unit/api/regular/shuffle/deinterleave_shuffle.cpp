//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/function/deinterleave_shuffle.hpp>

EVE_TEST_TYPES("Check behavior of deinterleave_shuffle shuffle", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  T field_markers { [](int i, int) { return ((i & 1) ? 0xB : 0xA) << 4; } };

  T a { [](int i, int) { return ( i / 2 ) & 7; }};
  T b { [](int i, int) { return ( i / 2 + T::size() / 2) & 7; }};

  a += field_markers;
  b += field_markers;

  // These inputs are not properly interleaved
  // for 1 element.
  if constexpr (T::size() == 1)
  {
    a = T{0xA0};
    b = T{0xB0};
  }

  eve::wide<eve::element_type_t<T>, eve::fixed<T::size() * 2>>
   expected { [](int i, int size) {
    if (i < size / 2 || size == 1) return 0xA0 | (i & 7);
    i -= size / 2;
    return 0xB0 | (i & 7);
  }};

  auto actual = eve::deinterleave_shuffle(a, b);

  std::cout << std::hex << "a : " << a << std::endl;
  std::cout << std::hex << "b : " << b << std::endl;
  std::cout << std::hex << "e : " << expected << std::endl;
  std::cout << std::hex << "r : " << actual << std::endl;
  std::cout << std::dec << std::endl;

  TTS_EQUAL(expected, actual);
};
