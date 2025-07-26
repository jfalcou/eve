//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/translation/common.hpp"

TTS_CASE_TPL("Translatable wide - store", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using W = eve::wide<T>;
  constexpr auto N = W::size();

  if constexpr (std::integral<T>)
  {
    enum class E: T { };
    eve::wide<E> wt = [](auto i, auto) { return static_cast<E>(i + 1); };

    std::array<E, N> tdata{};
    eve::store(wt, tdata.data());

    for(std::size_t i = 0; i < N; ++i) {
      TTS_EQUAL(static_cast<T>(tdata[i]), static_cast<T>(i + 1));
    }

    std::array<T, N> data{};
    eve::store(wt, data.data());

    for(std::size_t i = 0; i < N; ++i) {
      TTS_EQUAL(data[i], static_cast<T>(i + 1));
    }
  }

  using trans_t = BaseStruct<T>;
  eve::wide<trans_t> wt = [](auto i, auto) { return trans_t{ static_cast<T>(i + 1) }; };

  std::array<trans_t, N> tdata{};
  eve::store(wt, tdata.data());

  for(std::size_t i = 0; i < N; ++i) {
    TTS_EQUAL(tdata[i].value, static_cast<T>(i + 1));
  }

  std::array<T, N> data{};
  eve::store(wt, data.data());

  for(std::size_t i = 0; i < N; ++i) {
    TTS_EQUAL(data[i], static_cast<T>(i + 1));
  }
};

TTS_CASE_TPL("Translatable logical wide - store", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using W = eve::wide<T>;
  constexpr auto N = W::size();

  if constexpr (std::integral<T>)
  {
    enum class E: T { };
    eve::logical<eve::wide<E>> wt = [](auto i, auto) { return eve::logical<E>(i % 2 == 0); };

    std::array<eve::logical<E>, N> tdata{};
    eve::store(wt, tdata.data());

    for(std::size_t i = 0; i < N; ++i) {
      TTS_EQUAL(bool(tdata[i]), (i % 2 == 0));
    }

    std::array<eve::logical<T>, N> data{};
    eve::store(wt, data.data());

    for(std::size_t i = 0; i < N; ++i) {
      TTS_EQUAL(bool(data[i]), (i % 2 == 0));
    }
  }

  using trans_t = BaseStruct<T>;
  eve::logical<eve::wide<trans_t>> wt = [](auto i, auto) { return eve::logical<trans_t>(i % 2 == 0); };

  std::array<eve::logical<trans_t>, N> tdata{};
  eve::store(wt, tdata.data());

  for(std::size_t i = 0; i < N; ++i) {
    TTS_EQUAL(bool(tdata[i]), (i % 2 == 0));
  }

  std::array<eve::logical<T>, N> data{};
  eve::store(wt, data.data());

  for(std::size_t i = 0; i < N; ++i) {
    TTS_EQUAL(bool(data[i]), (i % 2 == 0));
  }
};

