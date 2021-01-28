//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <eve/wide.hpp>


TTS_CASE_TPL("wide supports std::tuple_size",
             eve::fixed<1>,
             eve::fixed<2>,
             eve::fixed<4>,
             eve::fixed<8>,
             eve::fixed<16>,
             eve::fixed<32>,
             eve::fixed<64>,
             eve::fixed<128>)
{
  using wide_t = eve::wide<int, T>;

  TTS_EQUAL(std::tuple_size<wide_t>::value, T::value);
}

TTS_CASE_TPL("wide supports std::tuple_element",
             double,
             float,
             std::uint8_t,
             std::uint16_t,
             std::uint32_t,
             std::uint64_t,
             std::int8_t,
             std::int16_t,
             std::int32_t,
             std::int64_t)
{
  using wide_t = eve::wide<T>;

  TTS_TYPE_IS((typename std::tuple_element<0, wide_t>::type), T);
}

TTS_CASE("wide supports structured binding")
{
  eve::wide<float, eve::fixed<8>> w = {1.2f, 2.3f, 3.4f, 4.5f, 5.6f, 6.7f, 7.8f, 8.9f};

  auto [ a0, a1, a2, a3, a4, a5, a6, a7 ] = w;

  TTS_EQUAL(a0, w.get(0));
  TTS_EQUAL(a1, w.get(1));
  TTS_EQUAL(a2, w.get(2));
  TTS_EQUAL(a3, w.get(3));
  TTS_EQUAL(a4, w.get(4));
  TTS_EQUAL(a5, w.get(5));
  TTS_EQUAL(a6, w.get(6));
  TTS_EQUAL(a7, w.get(7));
}
