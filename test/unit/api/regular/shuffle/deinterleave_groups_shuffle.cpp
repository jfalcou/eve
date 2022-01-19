//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/function/deinterleave_groups_shuffle.hpp>

EVE_TEST_TYPES("Check behavior of deinterleave_groups_shuffle group size 1, shuffle", eve::test::simd::all_types)
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

  auto actual = eve::deinterleave_groups_shuffle(a, b, eve::lane<1>);

  std::cout << std::hex << "a : " << a << std::endl;
  std::cout << std::hex << "b : " << b << std::endl;
  std::cout << std::hex << "e : " << expected << std::endl;
  std::cout << std::hex << "r : " << actual << std::endl;
  std::cout << std::dec << std::endl;

  TTS_EQUAL(expected, actual);
};


TTS_CASE("Deinterleave special cases")
{
  using T = eve::wide<std::uint64_t, eve::fixed<8>>;
  T field_marker { [](int i, int) {
   switch (i % 4) {
     case 0: return 0xA << 0x4;
     case 1: return 0xA << 0x4;
     case 2: return 0xB << 0x4;
     case 3: return 0xB << 0x4;
   }
   return -1;
  }};

  T a { 0x0, 0x1, 0x0, 0x1, 0x2, 0x3, 0x2, 0x3 };
  a += field_marker;
  T b = a + T::size() / 2;

  auto actual = eve::deinterleave_groups_shuffle(a, b, eve::lane<2>);

  eve::wide<eve::element_type_t<T>, eve::fixed<T::size() * 2>>
  expected { [](int i, int size) {
    if (i < size / 2) return 0xA0 + i;
    else              return 0xB0 + (i - size / 2);
  }};

  std::cout << std::hex << "a : " << a << std::endl;
  std::cout << std::hex << "b : " << b << std::endl;
  std::cout << std::hex << "e : " << expected << std::endl;
  std::cout << std::hex << "r : " << actual << std::endl;

  TTS_EQUAL(expected, actual);
};
