//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include <algorithm>

template <typename Tgt, typename Alg>
struct swap_ranges_ptr_test
{
  eve::as<Tgt> tgt;
  Alg alg;

  swap_ranges_ptr_test(eve::as<Tgt> tgt, Alg alg) : tgt(tgt), alg(alg) {}

  void init(auto& page_1, auto& page_2) const
  {
    std::fill(page_1.begin(), page_1.end(), 0);
    std::fill(page_2.begin(), page_2.end(), 1);
  }

  void generate_answer(auto*, auto*, auto*, auto*) {}

  template <typename R1, typename R2>
  void run(R1 range_or_it1, R2 range_or_it2)
  {
    auto zipped_range = eve::algo::views::zip(range_or_it1, range_or_it2);
    // To operate with both ends always
    auto r1 = get<0>(zipped_range);
    auto r2 = get<1>(zipped_range);

    TTS_EXPECT(std::all_of(eve::unalign(r1.begin()),
                           eve::unalign(r1.end()),
                           [](auto x) { return x == 0; }));
    TTS_EXPECT(std::all_of(eve::unalign(r2.begin()),
                           eve::unalign(r2.end()),
                           [](auto x) { return x == 1; }));

    alg(range_or_it1, range_or_it2);

    TTS_EXPECT(std::all_of(eve::unalign(r1.begin()),
                           eve::unalign(r1.end()),
                           [](auto x) { return x == 1; }));
    TTS_EXPECT(std::all_of(eve::unalign(r2.begin()),
                           eve::unalign(r2.end()),
                           [](auto x) { return x == 0; }));

    alg(range_or_it1, range_or_it2);
  }
};

void swap_ranges_test_page_ends(auto tgt, auto alg)
{
  swap_ranges_ptr_test test{tgt, alg};
  algo_test::two_ranges_test(tgt, test);
}

TTS_CASE_TPL("Check swap ranges", algo_test::selected_pairs_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto native_tgt = eve::as<eve::wide<e_t>>{};

  swap_ranges_test_page_ends(native_tgt, eve::algo::swap_ranges);

  auto with_cardinal = eve::algo::swap_ranges[eve::algo::force_cardinal<T::size()>];

  swap_ranges_test_page_ends(eve::as<T>{}, with_cardinal[eve::algo::unroll<1>][eve::algo::no_aligning]);
};
