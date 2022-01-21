//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"

#include <eve/function/deinterleave_groups_shuffle.hpp>

TTS_CASE("Check behavior of deinterleave_groups_shuffle pattern")
{
  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<1, 1>), (eve::pattern_t<0>{}));

  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<1, 2>),
                                                (eve::pattern_t<0, 1>{}));
  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<2, 2>),
                                                (eve::pattern_t<0, 1>{}));

  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<1, 4>),
                      (eve::pattern_t<0, 2, 1, 3>{}));
  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<2, 4>),
                      (eve::pattern_t<0, 1, 2, 3>{}));

  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<1, 8>),
                      (eve::pattern_t<0, 2, 4, 6, 1, 3, 5, 7>{}));
  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<2, 8>),
                      (eve::pattern_t<0, 1, 4, 5, 2, 3, 6, 7>{}));

  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<4, 16>),
                      (eve::pattern_t<0, 1, 2, 3,  8,  9, 10, 11,
                                      4, 5, 6, 7, 12, 13, 14, 15>{}));
};

EVE_TEST_TYPES("Check behavior of deinterleave_groups_shuffle size 1, swizzle", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  T field_markers { [](int i, int) { return ((i & 1) ? 0xB : 0xA) << 4; } };
  T in { [](int i, int) {
    int field_marker = (i & 1) ? 0xB : 0xA;
    return field_marker << 4 | ( (i / 2) & 7);
  }};

  T expected { [](int i, int size) {
    if (i < size / 2 || size == 1) return 0xA0 | (i & 7);
    i -= size / 2;
    return 0xB0 | (i & 7);
  }};

  T res = eve::deinterleave_groups_shuffle(in, eve::lane<1>);

#if 0
  std::cerr << std::hex << "i : " << in << std::endl;
  std::cerr << std::hex << "e : " << expected << std::endl;
  std::cerr << std::hex << "r : " << res << std::endl;
#endif

  TTS_EQUAL(expected, res);
};

// This is identity
EVE_TEST_TYPES("Check behavior of deinterleave_groups_shuffle G >= N, swizzle", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  T expected { [](int i, int) { return i;  }};

  if constexpr ( T::size() != 1)
  {
    TTS_EQUAL(expected, (eve::deinterleave_groups_shuffle(expected, eve::lane<T::size() / 2>)));
  }

  TTS_EQUAL(expected, (eve::deinterleave_groups_shuffle(expected, eve::lane<T::size()>)));
};


EVE_TEST_TYPES("Check behavior of deinterleave_groups_shuffle swizzle 1 <= G < N, swizzle", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  T expected { [](int i, int size) {
    if (i < size / 2) return 0xA0 | (i & 0xf);
    else              return 0xB0 | ((i - size / 2) & 0xf);
  }};

  if constexpr ( T::size() == 1)
  {
    TTS_PASS("No G < N");
    return;
  }

  auto test = [&]<std::ptrdiff_t G>(eve::fixed<G>)
  {
    T in {[](int i, int)
          {
            int group_idx = i / G;

            int marker = (group_idx % 2) ? 0xB0 : 0xA0;
            int new_i  = (group_idx / 2) * (int)G + i % G;

            return marker | (new_i & 0xf);
          }};

    auto r = eve::deinterleave_groups_shuffle(in, eve::lane<G>);

#if 0
    std::cout << "G: "    << G << std::endl;
    std::cout << std::hex << "i : " << in << std::endl;
    std::cout << std::hex << "e : " << expected << std::endl;
    std::cout << std::hex << "r : " << r << std::endl;
    std::cout << std::dec << std::endl;
#endif

    TTS_EQUAL(expected, r);
  };

  [&]<std::size_t... I>( std::index_sequence<I...> )
  {
    (test( eve::lane<1 << I> ), ... );
  }( std::make_index_sequence<std::bit_width( std::size_t(T::size() / 2) )>{} );
};
