//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"


TTS_CASE_TPL("combine", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  constexpr std::size_t max_size_bit = 7; // 128 bytes max

  std::array<T, 1 << max_size_bit> data;
  for(int i = 0; i < (1 << max_size_bit); i++) data[i] = 1 + i;

  [&]<std::size_t... TB>(std::index_sequence<TB...>)
  {
    auto outer = [&](auto tbv)
    {
      constexpr std::size_t target_bit = decltype(tbv)::value;

      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        auto r = [&](auto N)
        {
          constexpr std::size_t card_in = (1 << N);
          constexpr std::size_t K = (1 << (target_bit - N));
          std::array<eve::wide<T, eve::fixed<card_in>>, K> wides;

          for(std::size_t i = 0; i < K; ++i)
          {
            wides[i] = eve::wide<T, eve::fixed<card_in>>(&data[i * card_in]);
          }

          eve::wide<T, eve::fixed<card_in * K>> ref(&data[0]);
          auto combined = [&]<std::size_t... J>(std::index_sequence<J...>)
          {
            return eve::combine(wides[J]...);
          }(std::make_index_sequence<K>{});

          TTS_EQUAL(combined, ref);
        };

        (r(std::integral_constant<std::size_t, I>{}), ...);
      }(std::make_index_sequence<target_bit>{});
    };

    (outer(std::integral_constant<std::size_t, TB + 1>{}), ...);
  }(std::make_index_sequence<max_size_bit>{});
};
