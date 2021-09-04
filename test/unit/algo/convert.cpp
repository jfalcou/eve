//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/convert.hpp>
#include <eve/algo/ptr_iterator.hpp>

#include <vector>

TTS_CASE("eve::algo::convert, vector basics")
{
  std::vector<int> v;

  eve::algo::relaxed_range auto converted = eve::algo::convert(v, eve::as<double>{});
  (void) converted;
  TTS_PASS("all types ok");
}

TTS_CASE("eve.algo.convert to/from")
{
  // pointer
  {
    using ap = eve::aligned_ptr<char>;
    ap                                        chars{};
    eve::algo::converting_iterator<ap, int>   ints   = eve::algo::convert(chars,   eve::as<int>{});
    eve::algo::converting_iterator<ap, short> shorts = eve::algo::convert(ints,    eve::as<short>{});
    ap                                        chars2 = eve::algo::convert(shorts,  eve::as<char>{});
    (void) chars2;
  }
  // eve::iterator
  {
    using ap_it = eve::algo::aligned_ptr_iterator<char, eve::fixed<4>>;
    ap_it                                        chars{};
    eve::algo::converting_iterator<ap_it, int>   ints   = eve::algo::convert(chars,  eve::as<int>{});
    eve::algo::converting_iterator<ap_it, short> shorts = eve::algo::convert(ints,   eve::as<short>{});
    ap_it                                        chars2 = eve::algo::convert(shorts, eve::as<char>{});
    (void)chars2;
  }
  // std::vector
  {
    std::vector<char> chars_v;

    using ref_vc = eve::algo::range_ref_wrapper<std::vector<char>>;

    ref_vc                                     chars  = eve::algo::convert(chars_v, eve::as<char>{});
    eve::algo::converting_range<ref_vc, int>   ints   = eve::algo::convert(chars,   eve::as<int>{});
    eve::algo::converting_range<ref_vc, short> shorts = eve::algo::convert(ints,    eve::as<short>{});
    ref_vc                                     chars2 = eve::algo::convert(shorts,  eve::as<char>{});
    (void) chars2;
  }

  TTS_PASS("all types ok");
}
