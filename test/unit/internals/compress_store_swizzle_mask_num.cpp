//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/detail/function/compress_store_swizzle_mask_num.hpp>

#include <bit>
#include <random>

EVE_TEST_TYPES("compress_store_swizzle_mask_num 4 elements",
               eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  using mask_t = eve::logical<eve::wide<T, eve::fixed<4>>>;

  auto expected_shuffle_num = [](mask_t mask) {
    int res = 0;
    if (mask.get(0)) res += 1;
    if (mask.get(1)) res += 2;
    if (mask.get(2)) res += 4;
    return res;
  };

  auto run = [&](auto ignore)
  {
    for( bool m0 : {false, true} ) {
      for( bool m1 : {false, true} ) {
        for( bool m2 : {false, true} ) {
          for( bool m3 : {false, true} ) {
            mask_t mask {m0, m1, m2, m3};
            mask_t mask_with_ignore = mask && ignore.mask(eve::as(mask));

            int expected_num = expected_shuffle_num(mask_with_ignore);

            // partial
            {
              auto [actual_num, actual_4th] = eve::detail::compress_store_swizzle_mask_num_partial(ignore, mask);
              TTS_EQUAL(expected_num, actual_num);

              if (ignore.roffset(eve::as(mask)) == 0) TTS_EQUAL(m3, actual_4th);
              else                                    TTS_EQUAL(false, actual_4th);
            }

            // complete
            {
              auto [actual_num, actual_count] = eve::detail::compress_store_swizzle_mask_num(ignore, mask);
              TTS_EQUAL(expected_num, actual_num);

              int expected_count = eve::count_true(mask_with_ignore);
              TTS_EQUAL(expected_count, actual_count);
            }
          }
        }
      }
    }
  };

  run(eve::ignore_none);
  run(eve::ignore_all);
  run(eve::ignore_first(2));
  run(eve::ignore_extrema(1, 1));
  run(eve::ignore_extrema(0, 2));
  run(eve::ignore_last(2));
};

EVE_TEST_TYPES("compress_store_swizzle_mask_num 8 elements",
               eve::test::scalar::all_types)<typename T>(eve::as<T>)
{
  using mask_t = eve::logical<eve::wide<T, eve::fixed<8>>>;

  std::array<int, 6> count_for_element {1, 1, 3, 3, 9, 9};

  for( std::uint32_t i = 0; i < (1 << 6); ++i )
  {
    mask_t l {false};

    int num   = 0;
    int count = std::popcount(i);

    for( std::uint32_t bit = 0; bit != 6; ++bit )
    {
      if( i & (1 << bit) )
      {
        l.set(bit, true);
        num += count_for_element[bit];
      }
    }

    {
      auto [actual_num, actual_count] = eve::detail::compress_store_swizzle_mask_num(l);
      TTS_EQUAL(num, actual_num);
      TTS_EQUAL(count, actual_count);
    }

    ++count;

    {
      l.set(6, true);
      auto [actual_num, actual_count] = eve::detail::compress_store_swizzle_mask_num(l);
      TTS_EQUAL(num, actual_num);
      TTS_EQUAL(count, actual_count);
      l.set(6, false);
    }

    {
      l.set(7, true);
      auto [actual_num, actual_count] = eve::detail::compress_store_swizzle_mask_num(l);
      TTS_EQUAL(num, actual_num);
      TTS_EQUAL(count, actual_count);
      l.set(7, false);
    }

    ++count;

    {
      l.set(6, true);
      l.set(7, true);
      auto [actual_num, actual_count] = eve::detail::compress_store_swizzle_mask_num(l);
      TTS_EQUAL(num, actual_num);
      TTS_EQUAL(count, actual_count);
    }
  }
};

EVE_TEST_TYPES("compress_store_swizzle_mask_num 16 elements",
               eve::test::scalar::all_types)<typename T>(eve::as<T>)
{
  using mask_t = eve::logical<eve::wide<T, eve::fixed<16>>>;

  if (eve::current_api == eve::avx512 && eve::has_aggregated_abi_v<eve::wide<T, eve::fixed<16>>>)
  {
    TTS_PASS("aggregated on avx512");
    return;
  }

  std::array<int, 1000> test_cases;

  std::mt19937 gen;
  std::uniform_int_distribution<> dis{0, 1 << 16};

  std::generate(test_cases.begin(), test_cases.end(), [&]()mutable{
    return dis(gen);
  });

  for( int test_case : test_cases) {
    mask_t l {false};

    for( std::uint32_t bit = 0; bit != 16; ++bit )
    {
      if( test_case & (1 << bit) )
      {
        l.set(bit, true);
      }
    }

    // For basic case a little bit testing itself but this is what we expect
    // and if there is an actual problem it will pop up in a upper layer test.

    auto [num1, count1, num2, count2] = eve::detail::compress_store_swizzle_mask_num(l);

    auto [lo, hi] = l.slice();
    auto [expected_num1, expected_count1] = eve::detail::compress_store_swizzle_mask_num(lo);
    auto [expected_num2, expected_count2] = eve::detail::compress_store_swizzle_mask_num(hi);

    TTS_EQUAL(expected_num1,     num1);
    TTS_EQUAL(expected_num2,     num2);
    TTS_EQUAL(expected_count1, count1);
    TTS_EQUAL(expected_count2, count2);
  }
};
