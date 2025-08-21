//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

TTS_CASE_TPL("combine - arithmetic", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  constexpr std::ptrdiff_t card_out = W::size();

  if constexpr (card_out > 1)
  {
    using T = eve::element_type_t<W>;
    using HW = typename W::split_type;
    using W1 = eve::wide<T, eve::fixed<1>>;

    std::array<T, card_out> data;
    for(std::ptrdiff_t i = 0; i < card_out; i++) data[i] = 1 + i;

    auto wref = W{ &data[0] };

    TTS_EQUAL(eve::combine(HW{ &data[0] }, HW{ &data[card_out / 2] }), wref);

    std::array<W1, card_out> wides;
    for(std::ptrdiff_t i = 0; i < card_out; ++i) wides[i] = W1{ &data[i] };

    auto from_w1 = [&wides]<std::size_t... I>(std::index_sequence<I...>)
    {
      return eve::combine(wides[I]...);
    }(std::make_index_sequence<card_out>{});

    TTS_EQUAL(from_w1, wref);
  }
};

TTS_CASE_TPL("combine - logical", eve::test::simd::all_types)
<typename BW>(tts::type<BW>)
{
  constexpr std::ptrdiff_t card_out = BW::size();

  if constexpr (card_out > 1)
  {
    using W = eve::logical<BW>;
    using T = eve::element_type_t<W>;
    using HW = typename W::split_type;
    using W1 = typename W::template rescale<eve::fixed<1>>;

    std::array<T, card_out> data;
    for(std::ptrdiff_t i = 0; i < card_out; i++) data[i] = (i % 3) == 0;

    auto wref = W{ &data[0] };

    TTS_EQUAL(eve::combine(HW{ &data[0] }, HW{ &data[card_out / 2] }), wref);

    std::array<W1, card_out> wides;
    for(std::ptrdiff_t i = 0; i < card_out; ++i) wides[i] = W1{ &data[i] };

    auto from_w1 = [&wides]<std::size_t... I>(std::index_sequence<I...>)
    {
      return eve::combine(wides[I]...);
    }(std::make_index_sequence<card_out>{});

    TTS_EQUAL(from_w1, wref);
  }
};
