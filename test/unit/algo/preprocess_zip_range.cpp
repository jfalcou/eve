//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/zip_iterator.hpp>
#include <eve/algo/zip.hpp>

#include <eve/algo/as_range.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/ptr_iterator.hpp>

#include <eve/algo/find.hpp>

#include <array>
#include <vector>

TTS_CASE("zip_iterator, preprocess range, scalar end")
{
  std::vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 4};

  using v_i = std::vector<int>::iterator;
  using zip_vi = eve::algo::zip_iterator<v_i, v_i>;

  using N = eve::fixed<eve::expected_cardinal_v<int>>;
  using ui_it = eve::algo::unaligned_ptr_iterator<int, N>;
  using zip_ui = eve::algo::zip_iterator<ui_it, ui_it>;

  zip_vi zf{v1.begin(), v2.begin()};

  auto processed = eve::algo::preprocess_range(eve::algo::traits{}, eve::algo::as_range(zf, v1.end()));

  zip_ui processed_f = processed.begin();
  zip_ui processed_l = processed.end();

  TTS_EQUAL((processed_l - processed_f), 3);

  zip_vi back_zf = processed.to_output_iterator(processed_f);
  TTS_EQUAL(back_zf, zf);
}

TTS_CASE("zip_iterator, preprocess range, zip end")
{
  using u      = int const*;
  using a      = eve::aligned_ptr<int const>;
  using zip_au = eve::algo::zip_iterator<a, u>;
  using zip_uu = eve::algo::zip_iterator<u, u>;

  using N = eve::fixed<eve::expected_cardinal_v<int>>;
  using a_it = eve::algo::aligned_ptr_iterator  <int const, N>;
  using u_it = eve::algo::unaligned_ptr_iterator<int const, N>;
  using zip_au_it = eve::algo::zip_iterator<a_it, u_it>;
  using zip_uu_it = eve::algo::zip_iterator<u_it, u_it>;

  // au_uu
  {
    using zip_au_uu_rng = decltype(eve::algo::as_range(zip_au{}, zip_uu{}));

    using processed =
      decltype(eve::algo::preprocess_range(eve::algo::traits{}, zip_au_uu_rng{}));

    TTS_TYPE_IS(decltype(std::declval<processed>().begin()), zip_au_it);
    TTS_TYPE_IS(decltype(std::declval<processed>().end()),   zip_uu_it);
  }

  // au_au
  {
    using zip_au_au_rng = decltype(eve::algo::as_range(zip_au{}, zip_au{}));

    using processed =
      decltype(eve::algo::preprocess_range(eve::algo::traits{}, zip_au_au_rng{}));

    TTS_TYPE_IS(decltype(std::declval<processed>().begin()), zip_au_it);
    TTS_TYPE_IS(decltype(std::declval<processed>().end()),   zip_au_it);
  }

  // au_u
  {
    using zip_au_u_rng = decltype(eve::algo::as_range(zip_au{}, u{}));

    using processed =
      decltype(eve::algo::preprocess_range(eve::algo::traits{}, zip_au_u_rng{}));

    TTS_TYPE_IS(decltype(std::declval<processed>().begin()), zip_au_it);
    TTS_TYPE_IS(decltype(std::declval<processed>().end()),   zip_uu_it);
  }

  // au_a
  {
    using zip_au_a_rng = decltype(eve::algo::as_range(zip_au{}, a{}));

    using processed =
      decltype(eve::algo::preprocess_range(eve::algo::traits{}, zip_au_a_rng{}));

    TTS_TYPE_IS(decltype(std::declval<processed>().begin()), zip_au_it);
    TTS_TYPE_IS(decltype(std::declval<processed>().end()),   zip_au_it);
  }
}

TTS_CASE("preprocess zip range, traits")
{
  using N = eve::fixed<eve::expected_cardinal_v<std::uint32_t>>;
  using uc_it = eve::algo::unaligned_ptr_iterator<std::int8_t, N>;
  using ui_it = eve::algo::unaligned_ptr_iterator<std::uint32_t, N>;
  using ac_it = eve::algo::aligned_ptr_iterator<std::int8_t, N>;
  using ai_it = eve::algo::aligned_ptr_iterator<std::uint32_t, N>;

  using zip_uc_it_ui_it = eve::algo::zip_iterator<uc_it, ui_it>;

  alignas(sizeof(std::int8_t) * N{}())   std::array<std::int8_t,   N{}()> c;
  alignas(sizeof(std::uint32_t) * N{}()) std::array<std::uint32_t, N{}()> i;

  auto af_ul = []<typename T>(std::array<T, N{}()> & rng) {
    return eve::algo::as_range(eve::aligned_ptr<T, N>(rng.begin()), rng.end());
  };

  auto af_al = []<typename T>(std::array<T, N{}()> & rng) {
    return eve::algo::as_range(eve::aligned_ptr<T, N>(rng.begin()), eve::aligned_ptr<T, N>(rng.end()));
  };

  // zip_u_u
  {
    auto zipped = eve::algo::zip(c, i);
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, zipped);

    eve::algo::traits expected_traits{ };

    TTS_TYPE_IS(decltype(processed.traits()), decltype(expected_traits));
    TTS_TYPE_IS(decltype(processed.begin()), zip_uc_it_ui_it);
    TTS_TYPE_IS(decltype(processed.end()), zip_uc_it_ui_it);
  }

  // first array aligned
  {
    using zip_ac_it_ui_it = eve::algo::zip_iterator<ac_it, ui_it>;

    auto zipped = eve::algo::zip(af_ul(c), i);
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, zipped);

    eve::algo::traits expected_traits{ eve::algo::no_aligning };

    TTS_TYPE_IS(decltype(processed.traits()), decltype(expected_traits));
    TTS_TYPE_IS(decltype(processed.begin()), zip_ac_it_ui_it);
    TTS_TYPE_IS(decltype(processed.end()), zip_uc_it_ui_it);
  }

  // second array aligned
  {
    using zip_uc_it_ai_it = eve::algo::zip_iterator<uc_it, ai_it>;

    auto zipped = eve::algo::zip(c, af_ul(i));
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, zipped);

    eve::algo::traits expected_traits{ eve::algo::no_aligning };

    TTS_TYPE_IS(decltype(processed.traits()), decltype(expected_traits));
    TTS_TYPE_IS(decltype(processed.begin()), zip_uc_it_ai_it);
    TTS_TYPE_IS(decltype(processed.end()), zip_uc_it_ui_it);
  }

  // first array, both ends aligned
  {
    using zip_ac_it_ui_it = eve::algo::zip_iterator<ac_it, ui_it>;

    auto zipped = eve::algo::zip(af_al(c), i);
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, zipped);

    eve::algo::traits expected_traits{ eve::algo::no_aligning, eve::algo::divisible_by_cardinal };

    TTS_TYPE_IS(decltype(processed.traits()), decltype(expected_traits));
    TTS_TYPE_IS(decltype(processed.begin()), zip_ac_it_ui_it);
    TTS_TYPE_IS(decltype(processed.end()), zip_ac_it_ui_it);
  }

}

TTS_CASE("missmatch prototype")
{
  std::vector<int> v1{1, 2, 3, 4};
  std::vector<int> v2{1, 2, 4, 5};

  auto found = eve::algo::find_if(eve::algo::zip(v1, v2), [](auto x1_x2) {
    auto [x1, x2] = x1_x2;
    return x1 != x2;
  });

  auto [r1, r2] = found;

  TTS_EQUAL((r1 - v1.begin()), 2);
  TTS_EQUAL((r2 - v2.begin()), 2);

  TTS_EQUAL(*r1, 3);
  TTS_EQUAL(*r2, 4);
}
