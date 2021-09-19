//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/detail/function/compress_store_swizzle_mask_num.hpp>

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

  for (bool m0 : {false, true}) {
    for (bool m1 : {false, true}) {
      for (bool m2 : {false, true}) {
        for (bool m3 : {false, true}) {
          mask_t mask{m0, m1, m2, m3};

          auto [actual_num, actual_4th] = eve::detail::compress_store_swizzle_mask_num(mask);

          int expected_num = expected_shuffle_num(mask);

          TTS_EQUAL(expected_num, actual_num);
          TTS_EQUAL(m3, actual_4th);
        }
      }
    }
  }
};
