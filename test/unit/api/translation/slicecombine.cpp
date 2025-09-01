//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/translation/common.hpp"

TTS_CASE_TPL("Translatable wide - slice", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;
  using trans_t = BaseStruct<T>;
  using WT = eve::as_wide_as_t<trans_t, W>;

  if constexpr (W::size() > 1)
  {
    if constexpr (std::integral<T>)
    {
      enum class E: T { };
      using WE = eve::as_wide_as_t<E, W>;

      W wr_enum = [](auto i, auto) { return static_cast<T>(i + 1); };
      WE wt_enum = [](auto i, auto) { return static_cast<E>(i + 1); };

      TTS_EQUAL(eve::translate(wt_enum), wr_enum);

      auto [wr_lo_enum, wr_hi_enum] = wr_enum.slice();
      auto [wt_lo_enum, wt_hi_enum] = wt_enum.slice();

      TTS_EQUAL(eve::translate(wt_lo_enum), wr_lo_enum);
      TTS_EQUAL(eve::translate(wt_hi_enum), wr_hi_enum);

      auto wr_lower_enum = wr_enum.slice(eve::lower_);
      auto wt_lower_enum = wt_enum.slice(eve::lower_);

      TTS_EQUAL(eve::translate(wt_lower_enum), wr_lower_enum);

      auto wr_upper_enum = wr_enum.slice(eve::upper_);
      auto wt_upper_enum = wt_enum.slice(eve::upper_);

      TTS_EQUAL(eve::translate(wt_upper_enum), wr_upper_enum);
    }

    W wr = [](auto i, auto) { return static_cast<T>(i + 1); };
    WT wt = [](auto i, auto) { return trans_t { static_cast<T>(i + 1) }; };

    TTS_EQUAL(eve::translate(wt), wr);

    auto [wr_lo, wr_hi] = wr.slice();
    auto [wt_lo, wt_hi] = wt.slice();

    TTS_EQUAL(eve::translate(wt_lo), wr_lo);
    TTS_EQUAL(eve::translate(wt_hi), wr_hi);

    auto wr_lower = wr.slice(eve::lower_);
    auto wt_lower = wt.slice(eve::lower_);

    TTS_EQUAL(eve::translate(wt_lower), wr_lower);

    auto wr_upper = wr.slice(eve::upper_);
    auto wt_upper = wt.slice(eve::upper_);

    TTS_EQUAL(eve::translate(wt_upper), wr_upper);
  }
};

TTS_CASE_TPL("Translatable wide - combine", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;
  using trans_t = BaseStruct<T>;
  using WT = eve::as_wide_as_t<trans_t, W>;

  if constexpr (std::integral<T>)
  {
    enum class E: T { };
    using WE = eve::as_wide_as_t<E, W>;

    W wr1 = [](auto i, auto) { return static_cast<T>(i + 1); };
    W wr2 = [](auto i, auto) { return static_cast<T>(i * 2 + 3); };
    WE wt1 = [](auto i, auto) { return static_cast<E>(i + 1); };
    WE wt2 = [](auto i, auto) { return static_cast<E>(i * 2 + 3); };

    auto wr_combined = eve::combine(wr1, wr2);
    auto wt_combined = eve::combine(wt1, wt2);

    TTS_EQUAL(eve::translate(wt_combined), wr_combined);
  }

  W wr1 = [](auto i, auto) { return static_cast<T>(i + 1); };
  W wr2 = [](auto i, auto) { return static_cast<T>(i * 2 + 3); };
  WT wt1 = [](auto i, auto) { return trans_t { static_cast<T>(i + 1) }; };
  WT wt2 = [](auto i, auto) { return trans_t { static_cast<T>(i * 2 + 3) }; };

  auto wr_combined = eve::combine(wr1, wr2);
  auto wt_combined = eve::combine(wt1, wt2);

  TTS_EQUAL(eve::translate(wt_combined), wr_combined);
};

TTS_CASE_TPL("Translatable wide - combine constructor", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;
  using trans_t = BaseStruct<T>;
  using WT = eve::as_wide_as_t<trans_t, W>;

  if constexpr (std::integral<T>)
  {
    enum class E: T { };
    using WE = eve::as_wide_as_t<E, W>;

    W wr1 = [](auto i, auto) { return static_cast<T>(i + 1); };
    W wr2 = [](auto i, auto) { return static_cast<T>(i * 2 + 3); };
    WE wt1 = [](auto i, auto) { return static_cast<E>(i + 1); };
    WE wt2 = [](auto i, auto) { return static_cast<E>(i * 2 + 3); };

    typename W::combined_type wr_combined { wr1, wr2 };
    typename WE::combined_type wt_combined { wt1, wt2 };

    TTS_EQUAL(eve::translate(wt_combined), wr_combined);
  }

  W wr1 = [](auto i, auto) { return static_cast<T>(i + 1); };
  W wr2 = [](auto i, auto) { return static_cast<T>(i * 2 + 3); };
  WT wt1 = [](auto i, auto) { return trans_t { static_cast<T>(i + 1) }; };
  WT wt2 = [](auto i, auto) { return trans_t { static_cast<T>(i * 2 + 3) }; };

  typename W::combined_type wr_combined { wr1, wr2 };
  typename WT::combined_type wt_combined { wt1, wt2 };

  TTS_EQUAL(eve::translate(wt_combined), wr_combined);
};

TTS_CASE_TPL("Translatable logical wide - combine constructor", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;
  using trans_t = eve::logical<BaseStruct<T>>;
  using WT = eve::as_wide_as_t<trans_t, W>;

  if constexpr (std::integral<T>)
  {
    enum class E: T { };
    using WE = eve::as_wide_as_t<eve::logical<E>, W>;

    eve::logical<W> wr1 = [](auto i, auto) { return (i % 2) == 0; };
    eve::logical<W> wr2 = [](auto i, auto) { return (i % 3) == 0; };
    WE wt1 = [](auto i, auto) { return eve::logical<E>((i % 2) == 0); };
    WE wt2 = [](auto i, auto) { return eve::logical<E>((i % 3) == 0); };

    typename eve::logical<W>::combined_type wr_combined { wr1, wr2 };
    typename WE::combined_type wt_combined { wt1, wt2 };

    TTS_EQUAL(eve::translate(wt_combined), wr_combined);
  }

  eve::logical<W> wr1 = [](auto i, auto) { return (i % 2) == 0; };
  eve::logical<W> wr2 = [](auto i, auto) { return (i % 3) == 0; };
  WT wt1 = [](auto i, auto) { return trans_t((i % 2) == 0); };
  WT wt2 = [](auto i, auto) { return trans_t((i % 3) == 0); };

  typename eve::logical<W>::combined_type wr_combined { wr1, wr2 };
  typename WT::combined_type wt_combined { wt1, wt2 };

  TTS_EQUAL(eve::translate(wt_combined), wr_combined);
};
