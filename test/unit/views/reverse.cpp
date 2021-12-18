//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/views/reverse.hpp>

#include <array>
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

TTS_CASE("eve::views::reverse, reverse of reverse")
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
    using ap_it = eve::algo::ptr_iterator<eve::aligned_ptr<char, eve::fixed<4>>, eve::fixed<4>>;
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

TTS_CASE("eve::views::reverse, preprocess_range")
{
  using ap = eve::aligned_ptr<int>;
  using up = int*;
  using a_it = eve::algo::ptr_iterator<ap, eve::fixed<eve::expected_cardinal_v<int>>>;
  using u_it = eve::algo::ptr_iterator<up, eve::fixed<eve::expected_cardinal_v<int>>>;

  {
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, eve::views::reverse(eve::algo::as_range(ap{}, up{})));
    TTS_TYPE_IS(decltype(processed.begin()), eve::views::reverse_iterator<u_it>);
    TTS_TYPE_IS(decltype(processed.end()),   eve::views::reverse_iterator<a_it>);
  }
  {
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, eve::views::reverse(eve::algo::as_range(up{}, up{})));
    TTS_TYPE_IS(decltype(processed.begin()), eve::views::reverse_iterator<u_it>);
    TTS_TYPE_IS(decltype(processed.end()),   eve::views::reverse_iterator<u_it>);
  }
  {
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, eve::views::reverse(eve::algo::as_range(up{}, ap{})));
    TTS_TYPE_IS(decltype(processed.begin()), eve::views::reverse_iterator<a_it>);
    TTS_TYPE_IS(decltype(processed.end()),   eve::views::reverse_iterator<u_it>);
  }
};

TTS_CASE("eve::views::reverse, basic_load_store")
{
  std::array<int, eve::expected_cardinal_v<int>> a;
  a.fill(0);

  eve::wide<int> iota  = [](int i, int) { return i; };
  eve::wide<int> riota = [](int i, int size) { return size - i - 1; };

  auto processed = eve::algo::preprocess_range(eve::algo::traits{}, eve::views::reverse(a));

  eve::store(iota, processed.begin());

  TTS_EQUAL(riota, eve::wide<int>{a.data()});
  TTS_EQUAL(iota,  eve::load(processed.begin()));
};
