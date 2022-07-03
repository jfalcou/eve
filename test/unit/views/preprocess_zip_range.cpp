//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/views/zip.hpp>

#include <eve/views/convert.hpp>

#include <eve/algo/as_range.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/ptr_iterator.hpp>

#include <array>
#include <vector>

TTS_CASE("zip_iterator, preprocess range, scalar end")
{
  std::vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 4};

  using v_i = std::vector<int>::iterator;
  using zip_vi = eve::views::zip_iterator<v_i, v_i>;

  using N = eve::fixed<eve::expected_cardinal_v<int>>;
  using ui_it = eve::algo::ptr_iterator<int*, N>;
  using zip_ui = eve::views::zip_iterator<ui_it, ui_it>;

  zip_vi zf{v1.begin(), v2.begin()};

  auto processed = eve::algo::preprocess_range(eve::algo::traits{}, eve::algo::as_range(zf, v1.end()));

  zip_ui processed_f = processed.begin();
  zip_ui processed_l = processed.end();

  TTS_EQUAL((processed_l - processed_f), 3);
};

TTS_CASE("zip_iterator, preprocess range, zip end")
{
  using u      = int const*;
  using a      = eve::aligned_ptr<int const>;
  using zip_au = eve::views::zip_iterator<a, u>;
  using zip_uu = eve::views::zip_iterator<u, u>;

  using N = eve::fixed<eve::expected_cardinal_v<int>>;
  using a_it = eve::algo::ptr_iterator<a, N>;
  using u_it = eve::algo::ptr_iterator<u, N>;
  using zip_au_it = eve::views::zip_iterator<a_it, u_it>;
  using zip_uu_it = eve::views::zip_iterator<u_it, u_it>;

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
};

TTS_CASE("preprocess zip range, traits")
{
  using N = eve::fixed<eve::expected_cardinal_v<std::uint32_t>>;
  using uc = std::int8_t*;
  using ac = eve::aligned_ptr<std::int8_t, N>;
  using ui = std::uint32_t*;
  using ai = eve::aligned_ptr<std::uint32_t>;

  using uc_it = eve::algo::ptr_iterator<uc, N>;
  using ui_it = eve::algo::ptr_iterator<ui, N>;
  using ac_it = eve::algo::ptr_iterator<ac, N>;
  using ai_it = eve::algo::ptr_iterator<ai, N>;

  using zip_uc_it_ui_it = eve::views::zip_iterator<uc_it, ui_it>;

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
    auto zipped = eve::views::zip(c, i);
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, zipped);

    TTS_TYPE_IS(decltype(processed.traits()), decltype(eve::algo::traits{}));
    TTS_TYPE_IS(decltype(processed.begin()), zip_uc_it_ui_it);
    TTS_TYPE_IS(decltype(processed.end()), zip_uc_it_ui_it);
  }

  // first array aligned
  {
    using zip_ac_it_ui_it = eve::views::zip_iterator<ac_it, ui_it>;

    auto zipped = eve::views::zip(af_ul(c), i);
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, zipped);

    TTS_CONSTEXPR_EXPECT(eve::algo::partially_aligned_iterator<zip_ac_it_ui_it>);
    TTS_TYPE_IS(decltype(processed.traits()), decltype(eve::algo::traits{}));
    TTS_TYPE_IS(decltype(processed.begin()), zip_ac_it_ui_it);
    TTS_TYPE_IS(decltype(processed.end()), zip_uc_it_ui_it);
  }

  // second array aligned
  {
    using zip_uc_it_ai_it = eve::views::zip_iterator<uc_it, ai_it>;

    auto zipped = eve::views::zip(c, af_ul(i));
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, zipped);

    TTS_CONSTEXPR_EXPECT(eve::algo::partially_aligned_iterator<zip_uc_it_ai_it>);

    TTS_TYPE_IS(decltype(processed.traits()), decltype(eve::algo::traits{}));
    TTS_TYPE_IS(decltype(processed.begin()), zip_uc_it_ai_it);
    TTS_TYPE_IS(decltype(processed.end()), zip_uc_it_ui_it);
  }

  // first array, both ends aligned
  {
    using zip_ac_it_ui_it = eve::views::zip_iterator<ac_it, ui_it>;

    auto zipped = eve::views::zip(af_al(c), i);
    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, zipped);

    eve::algo::traits expected_traits{ eve::algo::divisible_by_cardinal };

    TTS_CONSTEXPR_EXPECT(eve::algo::partially_aligned_iterator<zip_ac_it_ui_it>);
    TTS_TYPE_IS(decltype(processed.traits()), decltype(expected_traits));
    TTS_TYPE_IS(decltype(processed.begin()), zip_ac_it_ui_it);
    TTS_TYPE_IS(decltype(processed.end()), zip_ac_it_ui_it);
  }

  // force cardinal
  {
    eve::algo::traits tr{ eve::algo::force_cardinal<2> };

    auto zipped = eve::views::zip(c, i);
    auto processed = eve::algo::preprocess_range(tr, zipped);
    TTS_TYPE_IS(decltype(processed.traits()), decltype(tr));
    TTS_TYPE_IS(eve::iterator_cardinal_t<decltype(processed.begin())>, eve::fixed<2>);
  }

  // divisible by cardinal
  {
    eve::algo::traits tr{ eve::algo::divisible_by_cardinal };

    {
      auto zipped = eve::views::zip(c, i);

      auto processed = eve::algo::preprocess_range(tr, zipped);
      TTS_TYPE_IS(decltype(processed.traits()), decltype(tr));
    }
  }
};

TTS_CASE("preprocess zip range, common_type")
{

  std::array<std::int8_t,   64> c;
  std::array<std::uint32_t, 64> i;

  {
    using N           = eve::fixed<eve::expected_cardinal_v<std::uint32_t>>;
    using uc_it       = eve::algo::ptr_iterator<std::int8_t*, N>;
    using ui_it       = eve::algo::ptr_iterator<std::uint32_t*, N>;
    using conv_uc_it  = eve::views::converting_iterator<uc_it, std::uint32_t>;
    using expected_it = eve::views::zip_iterator<conv_uc_it, ui_it>;

    auto zipped = eve::views::zip[eve::algo::common_type](c, i);

    auto processed = eve::algo::preprocess_range(eve::algo::traits{}, zipped);

    TTS_TYPE_IS(decltype(processed.begin()), expected_it);
    TTS_TYPE_IS(decltype(processed.end()), expected_it);
  }

  {
    using N           = eve::fixed<2>;
    using uc_it       = eve::algo::ptr_iterator<std::int8_t*, N>;
    using ui_it       = eve::algo::ptr_iterator<std::uint32_t*, N>;
    using conv_uc_it  = eve::views::converting_iterator<uc_it, float>;
    using conv_ui_it  = eve::views::converting_iterator<ui_it, float>;
    using expected_it = eve::views::zip_iterator<conv_uc_it, conv_ui_it>;

    auto zipped = eve::views::zip[eve::algo::force_type<float>](c, i);

    auto processed = eve::algo::preprocess_range(eve::algo::traits{eve::algo::force_cardinal<2>}, zipped);

    TTS_TYPE_IS(decltype(processed.begin()), expected_it);
    TTS_TYPE_IS(decltype(processed.end()), expected_it);
  }
};
