//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/wide.hpp>
#include <eve/memory/aligned_ptr.hpp>

TTS_CASE("Check for expected width")
{
#ifdef EVE_AVX512_DEFAULT_64_BYTES
  TTS_EQUAL((eve::expected_width_v<double, eve::x86_512_>), (eve::max_native_width_v<double, eve::x86_512_>));
#else
  TTS_EQUAL((eve::expected_width_v<double, eve::x86_512_>), (eve::max_native_width_v<double, eve::x86_256_>));
  TTS_EQUAL((eve::expected_width_v<char, eve::x86_512_>), 32);
#endif
  TTS_EQUAL((eve::expected_width_v<double, eve::x86_256_>), (eve::max_native_width_v<double, eve::x86_256_>));
  TTS_EQUAL((eve::expected_width_v<double, eve::x86_128_>), (eve::max_native_width_v<double, eve::x86_128_>));
  TTS_EQUAL((eve::expected_width_v<double, eve::arm_128_>), (eve::max_native_width_v<double, eve::arm_128_>));
  TTS_EQUAL((eve::expected_width_v<double, eve::emulated_>), (eve::max_native_width_v<double, eve::emulated_>));
};

TTS_CASE("Check defaults use expected width")
{
  TTS_EQUAL(eve::wide<float>::size(), eve::expected_width_v<float>);
  TTS_EQUAL(eve::logical<eve::wide<std::int8_t>>::size(), eve::expected_width_v<std::int8_t>);
  TTS_EQUAL(decltype(eve::wide(1.0))::size(), eve::expected_width_v<double>);
  TTS_EQUAL(eve::aligned_ptr<short>::alignment(), eve::expected_width_v<short> * sizeof(short));
};

#include <eve/traits/product_type.hpp>

TTS_CASE("Check eve::expected_width works for tuples")
{
  using T = kumi::tuple<eve::logical<std::uint32_t>, double>;

  constexpr auto ecl = eve::expected_width_v<eve::logical<std::uint32_t>>;
  constexpr auto ecd = eve::expected_width_v<double>;

  TTS_EQUAL(eve::expected_width_v<T>, std::min(ecl, ecd));
  TTS_EQUAL(eve::wide<T>::size(), std::min(ecl, ecd));

  using U = kumi::tuple<std::int8_t, double>;
#ifdef EVE_AVX512_DEFAULT_64_BYTES
  TTS_EQUAL((eve::expected_width_v<U, eve::x86_512_>), 8);
#else
  TTS_EQUAL((eve::expected_width_v<U, eve::x86_512_>), 4);
#endif
  TTS_EQUAL((eve::expected_width_v<U, eve::x86_256_>), 4);
  TTS_EQUAL((eve::expected_width_v<U, eve::x86_128_>), 2);
};

TTS_CASE("Check max_native typedefs")
{
  TTS_EQUAL(eve::max_native_wide<float>::size(), eve::max_native_width_v<float>);
  TTS_EQUAL(eve::max_native_logical<float>::size(), eve::max_native_width_v<float>);
};
