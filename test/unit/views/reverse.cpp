//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/views/reverse.hpp>

#include <vector>

TTS_CASE("eve::views::reverse, read/write")
{
  std::vector<int> v{1, 2, 3, 4};

  eve::views::reverse_range rev = eve::views::reverse(v);
  TTS_EQUAL(eve::read(rev.begin() + 0), 4);
  TTS_EQUAL(eve::read(rev.begin() + 1), 3);
  TTS_EQUAL(eve::read(rev.begin() + 2), 2);
  TTS_EQUAL(eve::read(rev.begin() + 3), 1);

  TTS_EQUAL((rev.end() - rev.begin()), 4);

  eve::write(rev.begin() + 0, 1);
  eve::write(rev.begin() + 1, 2);
  eve::write(rev.begin() + 2, 3);
  eve::write(rev.begin() + 3, 4);

  TTS_EQUAL(v, (std::vector<int>{4, 3, 2, 1}));
};


TTS_CASE("ve::views::reverse, reverse of reverse")
{
  // pointer
  {
    using ap = eve::aligned_ptr<char>;
    ap                                  in{};
    eve::views::reverse_iterator<ap>    rev  = eve::views::reverse(in);
    ap                                  back = eve::views::reverse(rev);

    (void)back;
  }
  // eve::iterator
  {
    using ap_it = eve::algo::aligned_ptr_iterator<char, eve::fixed<4>>;
    ap_it                               in;
    eve::views::reverse_iterator<ap_it> rev = eve::views::reverse(in);
    ap_it                               back = eve::views::reverse(rev);

    (void)back;
  }
  // std::vector
  {
    using ref_vc = eve::algo::range_ref_wrapper<std::vector<char>>;

    std::vector<char>                 in;
    eve::views::reverse_range<ref_vc> rev = eve::views::reverse(in);
    ref_vc                            back = eve::views::reverse(rev);

    (void) back;
  }

  TTS_PASS("all types ok");
};
