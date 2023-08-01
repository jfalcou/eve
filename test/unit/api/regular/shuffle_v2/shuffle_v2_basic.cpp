//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

// These tests just for common functionality, not shuffling specific patterns.
// Those are in other files.

TTS_CASE_TPL("Check shuffle_v2, all call apis", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  T x {[](int i, int) { return i; }};
  TTS_EQUAL(x, eve::shuffle_v2(x, eve::lane<T::size()>, eve::pattern<0>));
  TTS_EQUAL(x, eve::shuffle_v2(x, [](int i, int) { return i; }));
  TTS_EQUAL(x, eve::shuffle_l<0>(x, eve::lane<T::size()>, eve::pattern<0>));
  TTS_EQUAL(x, eve::shuffle_l<0>(x, [](int i, int) { return i; }));
};

TTS_CASE("Check shuffle_v2, basic aggregation")
{
  using T  = eve::wide<std::uint64_t>;
  using T2 = eve::wide<std::uint64_t, eve::fixed<eve::expected_cardinal_v<std::uint64_t> * 2>>;

  T  lo {[](int i, int) { return i; }};
  T  hi {[](int i, int size) { return i + size; }};
  T2 in {lo, hi};

  TTS_EQUAL(lo, eve::shuffle_v2(in, eve::lane<T::size()>, eve::pattern<0>));
  TTS_EQUAL(hi, eve::shuffle_v2(in, eve::lane<T::size()>, eve::pattern<1>));
  TTS_EQUAL((T2 {lo, lo}), eve::shuffle_v2(in, eve::lane<T::size()>, eve::pattern<0, 0>));
  TTS_EQUAL((T2 {hi, hi}), eve::shuffle_v2(in, eve::lane<T::size()>, eve::pattern<1, 1>));
  TTS_EQUAL((T2 {lo, hi}), eve::shuffle_v2(in, eve::lane<T::size()>, eve::pattern<0, 1>));
  TTS_EQUAL((T2 {hi, lo}), eve::shuffle_v2(in, eve::lane<T::size()>, eve::pattern<1, 0>));

  TTS_EQUAL((T2 {lo, lo}), eve::shuffle_l<0>(in, eve::lane<T::size()>, eve::pattern<0, 0>));
  TTS_EQUAL((T2 {hi, hi}), eve::shuffle_l<0>(in, eve::lane<T::size()>, eve::pattern<1, 1>));
  TTS_EQUAL((T2 {lo, hi}), eve::shuffle_l<0>(in, eve::lane<T::size()>, eve::pattern<0, 1>));
  TTS_EQUAL((T2 {hi, lo}), eve::shuffle_l<0>(in, eve::lane<T::size()>, eve::pattern<1, 0>));
};
