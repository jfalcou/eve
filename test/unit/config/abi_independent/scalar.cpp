//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "interface.hpp"

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>

TTS_CASE("ABI independent types: both translation units use their own ABI namespace")
{
  TTS_EXPECT_NOT(eve::platform::supports_simd);
  if( abi_test::native_supports_simd() )
    TTS_NOT_EQUAL(abi_test::native_abi_namespace(), eve::current_abi_namespace);
};

TTS_CASE("ABI independent types: aligned_ptr crosses the ABI boundary")
{
  alignas(sizeof(float) * abi_test::lanes) std::array<float, 37> data;
  std::iota(data.begin(), data.end(), 1.0f);

  auto expected = data;
  std::transform(expected.begin(), expected.end(), expected.begin(), [](float x) { return x * x; });

  abi_test::square(eve::aligned_ptr<float, abi_test::lanes>{data.data()}, data.size());
  TTS_EXPECT(data == expected);
};

TTS_CASE("ABI independent types: soa_ptr crosses the ABI boundary")
{
  std::array<int, 37> a, b, out = {};
  std::iota(a.begin(), a.end(), 1);
  std::iota(b.begin(), b.end(), -10);

  std::array<int, 37> expected;
  std::transform(a.begin(), a.end(), b.begin(), expected.begin(), std::multiplies<>{});

  abi_test::multiply(eve::soa_ptr<int const*, int const*, int*>{a.data(), b.data(), out.data()}, a.size());
  TTS_EXPECT(out == expected);
};
