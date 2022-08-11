//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/views/convert.hpp>
#include <eve/algo/ptr_iterator.hpp>

#include <vector>

TTS_CASE("eve::views::convert, read/write")
{
  std::vector<int> v{1, 2, 3, 4};

  auto as_doubles = eve::views::convert(v, eve::as<double>{});

  int i = 0;
  for (auto f = as_doubles.begin(); f != as_doubles.end(); ++f)
  {
    TTS_TYPE_IS(decltype(eve::read(f)), double);
    TTS_EQUAL(eve::read(f), v[i]);

    eve::write(0.0, f);

    TTS_EQUAL(v[i], 0);
    ++i;
  }
};

TTS_CASE("eve::views::convert, preprocess test")
{
  using From      = float;
  using To        = int;
  using SmallerTo = short;
  using N         = eve::fixed<eve::expected_cardinal_v<To>>;

  auto common_test = []<typename R, typename T,
                        typename ExpectedRawF,
                        typename ExpectedRawS,
                        typename ExpectedTraits>
      (R&& r, eve::as<T> tgt, auto input_tr, ExpectedRawF, ExpectedRawS, ExpectedTraits) {
    eve::algo::relaxed_range auto converted = eve::views::convert(std::forward<R>(r), tgt);
    auto processed = eve::algo::preprocess_range(input_tr, converted);

    using I = eve::views::converting_iterator<ExpectedRawF, T>;
    using S = eve::views::converting_iterator<ExpectedRawS, T>;

    TTS_TYPE_IS(decltype(processed.traits()), ExpectedTraits);
    TTS_TYPE_IS(decltype(processed.begin()), I);
    TTS_TYPE_IS(decltype(processed.end()), S);

    TTS_CONSTEXPR_EQUAL(eve::algo::partially_aligned_iterator<decltype(processed.begin())>,
                        eve::algo::partially_aligned_iterator<ExpectedRawF>);

    // Two converting iterators is mostly the same thing, except for when the range has more info
    auto cf = eve::views::convert(r.begin(), tgt);
    auto cl = eve::views::convert(r.end(), tgt);
    auto as_iterators = eve::algo::preprocess_range(input_tr, eve::algo::as_range(cf, cl));
    TTS_TYPE_IS(decltype(processed.traits()), decltype(as_iterators.traits()));
    TTS_TYPE_IS(decltype(processed.begin()),  decltype(as_iterators.begin()));
    TTS_TYPE_IS(decltype(processed.end()),    decltype(as_iterators.end()));
  };

  {
    using u_it = eve::algo::ptr_iterator<From*, N>;

    std::vector<From> v;
    common_test(v, eve::as<To>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
    common_test(eve::algo::as_range(v.data(), v.data()),
                eve::as<To>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
    common_test(eve::algo::as_range(u_it{}, u_it{}),
                eve::as<To>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
    common_test(eve::algo::as_range(u_it{}, u_it{}),
                eve::as<SmallerTo>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});

    common_test(v, eve::as<To>{}, eve::algo::traits{eve::algo::no_aligning},
               u_it{}, u_it{},    eve::algo::traits{eve::algo::no_aligning});
  }
  {
    using u_it = eve::algo::ptr_iterator<From const*, N>;

    const std::vector<From> v;
    common_test(v, eve::as<To>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
    common_test(eve::algo::as_range(v.data(), v.data()),
                eve::as<To>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
    common_test(eve::algo::as_range(u_it{}, u_it{}),
                eve::as<To>{}, eve::algo::traits{}, u_it{}, u_it{}, eve::algo::traits{});
  }
  {
    using a_it = eve::algo::ptr_iterator<eve::aligned_ptr<From, N>, N>;
    using u_it = eve::algo::ptr_iterator<From*, N>;

    eve::aligned_ptr<From> f;
    From* l = nullptr;

    common_test(eve::algo::as_range(f, l),
                eve::as<To>{}, eve::algo::traits{}, a_it{}, u_it{},
                eve::algo::traits{});
  }
};

TTS_CASE("views.convert to/from")
{
  // pointer
  {
    using ap = eve::aligned_ptr<std::int8_t>;
    ap                                        chars{};
    eve::views::converting_iterator<ap, int>   ints   = eve::views::convert(chars,   eve::as<int>{});
    eve::views::converting_iterator<ap, short> shorts = eve::views::convert(ints,    eve::as<short>{});
    ap                                         chars2 = eve::views::convert(shorts,  eve::as<std::int8_t>{});
    (void) chars2;
  }
  // eve::iterator
  {
    using ap_it = eve::algo::ptr_iterator<eve::aligned_ptr<std::int8_t, eve::fixed<4>>, eve::fixed<4>>;
    ap_it                                         chars{};
    eve::views::converting_iterator<ap_it, int>   ints   = eve::views::convert(chars,  eve::as<int>{});
    eve::views::converting_iterator<ap_it, short> shorts = eve::views::convert(ints,   eve::as<short>{});
    ap_it                                         chars2 = eve::views::convert(shorts, eve::as<std::int8_t>{});
    (void)chars2;
  }
  // std::vector
  {
    std::vector<std::int8_t> chars_v;

    using ref_vc = eve::algo::range_ref_wrapper<std::vector<std::int8_t>>;

    ref_vc                                      chars  = eve::views::convert(chars_v, eve::as<std::int8_t>{});
    eve::views::converting_range<ref_vc, int>   ints   = eve::views::convert(chars,   eve::as<int>{});
    eve::views::converting_range<ref_vc, short> shorts = eve::views::convert(ints,    eve::as<short>{});
    ref_vc                                      chars2 = eve::views::convert(shorts,  eve::as<std::int8_t>{});
    (void) chars2;
  }

  TTS_PASS("all types ok");
};

TTS_CASE("eve.algo.views.convert_iterator const/non-const")
{
  using ap             = eve::aligned_ptr<std::int8_t>;
  using acp            = eve::aligned_ptr<std::int8_t const>;
  using converting_it  = eve::views::converting_iterator<ap,  int>;
  using converting_cit = eve::views::converting_iterator<acp, int>;

  TTS_CONSTEXPR_EXPECT( (std::convertible_to<converting_it, converting_cit>) );
};
