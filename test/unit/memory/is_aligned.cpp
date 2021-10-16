//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/memory/is_aligned.hpp>

TTS_CASE("is_aligned for integers")
{
  TTS_EXPECT(eve::is_aligned<1>(0));
  TTS_EXPECT(eve::is_aligned<1>(1));
  TTS_EXPECT(eve::is_aligned<1>(2));

  TTS_EXPECT(eve::is_aligned<2>(0));
  TTS_EXPECT_NOT(eve::is_aligned<2>(1));
  TTS_EXPECT(eve::is_aligned<2>(2));
  TTS_EXPECT(eve::is_aligned<2>(4));

  TTS_EXPECT(eve::is_aligned<4>(0));
  TTS_EXPECT_NOT(eve::is_aligned<4>(1));
  TTS_EXPECT_NOT(eve::is_aligned<4>(2));
  TTS_EXPECT(eve::is_aligned<4>(4));
  TTS_EXPECT(eve::is_aligned<4>(8));

  TTS_EXPECT(eve::is_aligned<8>(0));
  TTS_EXPECT_NOT(eve::is_aligned<8>(1));
  TTS_EXPECT_NOT(eve::is_aligned<8>(2));
  TTS_EXPECT_NOT(eve::is_aligned<8>(4));
  TTS_EXPECT(eve::is_aligned<8>(8));
  TTS_EXPECT(eve::is_aligned<8>(16));
};

TTS_CASE("is_aligned for pointers")
{
  std::uint8_t            v8;
  std::uint16_t           v16;
  std::uint32_t           v32;
  std::uint64_t           v64;
  alignas(8) std::uint8_t v128;

  TTS_EXPECT(eve::is_aligned<1>(&v8));
  TTS_EXPECT(eve::is_aligned<2>(&v16));
  TTS_EXPECT(eve::is_aligned<4>(&v32));
  TTS_EXPECT(eve::is_aligned<8>(&v64));
  TTS_EXPECT(eve::is_aligned<8>(&v128));
};

EVE_TEST_TYPES("is_aligned for pointers with respect to SIMD lanes", eve::test::simd::cardinals)
<typename Lanes>(eve::as<Lanes>)
{
  alignas(sizeof(std::uint8_t)  * Lanes::value) std::uint8_t  v8;
  alignas(sizeof(std::uint16_t) * Lanes::value) std::uint16_t v16;
  alignas(sizeof(std::uint32_t) * Lanes::value) std::uint32_t v32;
  alignas(sizeof(std::uint64_t) * Lanes::value) std::uint64_t v64;

  TTS_EXPECT(eve::is_aligned(&v8  , Lanes{}));
  TTS_EXPECT(eve::is_aligned(&v16 , Lanes{}));
  TTS_EXPECT(eve::is_aligned(&v32 , Lanes{}));
  TTS_EXPECT(eve::is_aligned(&v64 , Lanes{}));
};
