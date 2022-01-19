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

EVE_TEST_TYPES("Check behavior of deinterleave_groups_shuffle all group sizes, shuffle", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using res_t = eve::wide<eve::element_type_t<T>, eve::fixed<T::size() * 2>>;


  res_t expected { [](int i, int size) {
    if (i < size / 2) return 0xA0 | (i & 0xf);
    else              return 0xB0 | ((i - size / 2) & 0xf);
  }};

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto test = [&]<std::ptrdiff_t G>(eve::fixed<G>)
    {
      res_t a_b { [](int i, int) {
        int group_idx    = i / G;

        int marker = (group_idx % 2) ? 0xB0 : 0xA0;
        int new_i = ( group_idx / 2 ) * (int)G + i % G;

        return marker | (new_i & 0xf);
      }};
      auto [a, b] = a_b.slice();

      auto r = eve::deinterleave_groups_shuffle(a, b, eve::lane<G>);

#if 0
      std::cout << "G: "    << G << std::endl;
      std::cout << std::hex << "a : " << a << std::endl;
      std::cout << std::hex << "b : " << b << std::endl;
      std::cout << std::hex << "e : " << expected << std::endl;
      std::cout << std::hex << "r : " << r << std::endl;
      std::cout << std::dec << std::endl;
#endif

      TTS_EQUAL(expected, r);
    };

    (test( eve::lane<1 << I> ), ... );
  }( std::make_index_sequence<std::bit_width( std::size_t(T::size()) )>{} );
};
