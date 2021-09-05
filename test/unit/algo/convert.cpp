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

TTS_CASE("eve::algo::convert, preprocess test")
{
  auto common_test = []<typename R, typename T,
                        typename ExpectedRawF,
                        typename ExpectedRawS,
                        typename ExpectedTraits>
      (R&& r, eve::as<T> tgt, auto input_tr, ExpectedRawF, ExpectedRawS, ExpectedTraits) {
    eve::algo::relaxed_range auto converted = eve::algo::convert(std::forward<R>(r), tgt);
    auto processed = eve::algo::preprocess_range(input_tr, converted);

    using I = eve::algo::converting_iterator<ExpectedRawF, T>;
    using S = eve::algo::converting_iterator<ExpectedRawS, T>;

    TTS_TYPE_IS(decltype(processed.traits()), ExpectedTraits);
    TTS_TYPE_IS(decltype(processed.begin()), I);
    TTS_TYPE_IS(decltype(processed.end()), S);

    // Two converting iterators is mostly the same thing, except for when the range has more info
    auto cf = eve::algo::convert(r.begin(), tgt);
    auto cl = eve::algo::convert(r.end(), tgt);
    auto as_iterators = eve::algo::preprocess_range(input_tr, eve::algo::as_range(cf, cl));
    TTS_TYPE_IS(decltype(processed.traits()), decltype(as_iterators.traits()));
    TTS_TYPE_IS(decltype(processed.begin()),  decltype(as_iterators.begin()));
    TTS_TYPE_IS(decltype(processed.end()),    decltype(as_iterators.end()));
  };

  {
    using u_it = eve::algo::unaligned_ptr_iterator<int, eve::fixed<eve::expected_cardinal_v<double>>>;

    std::vector<int> v;
    common_test(v, eve::as<double>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
    common_test(eve::algo::as_range(v.data(), v.data()),
                eve::as<double>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
    common_test(eve::algo::as_range(u_it{}, u_it{}),
                eve::as<double>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});

    common_test(v, eve::as<double>{}, eve::algo::traits{eve::algo::no_aligning},
               u_it{}, u_it{},        eve::algo::traits{eve::algo::no_aligning});
  }
  {
    using u_it = eve::algo::unaligned_ptr_iterator<int const, eve::fixed<eve::expected_cardinal_v<double>>>;

    const std::vector<int> v;
    common_test(v, eve::as<double>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
    common_test(eve::algo::as_range(v.data(), v.data()),
                eve::as<double>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
    common_test(eve::algo::as_range(u_it{}, u_it{}),
                eve::as<double>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
  }
  {
    using a_it = eve::algo::aligned_ptr_iterator  <int, eve::fixed<eve::expected_cardinal_v<double>>>;
    using u_it = eve::algo::unaligned_ptr_iterator<int, eve::fixed<eve::expected_cardinal_v<double>>>;

    eve::aligned_ptr<int> f;
    int* l = nullptr;

    common_test(eve::algo::as_range(f, l),
                eve::as<double>{}, eve::algo::traits{}, a_it{}, u_it{},
                eve::algo::traits{eve::algo::no_aligning});
  }

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
