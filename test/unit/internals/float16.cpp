//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#if defined(SPY_SUPPORTS_FP16_TYPE) && !defined(_MSC_VER)
  // if the compiler provides fp16 softfloat support, use it to check the fp16 to fp32 routine
  TTS_CASE("emulated float16 conversion - f16 to f32")
  {
    for (uint16_t f16_bits = 0u; f16_bits < eve::valmax(eve::as<uint16_t>{}); ++f16_bits)
    {
      float f32 = eve::_::emulated_fp16_to_fp32(f16_bits);

      if (std::isnan(f32))
      {
        TTS_EXPECT(std::isnan(static_cast<float>(std::bit_cast<_Float16>(f16_bits))));
      }
      else
      {
        TTS_EQUAL(f32, static_cast<float>(std::bit_cast<_Float16>(f16_bits)));
      }
    }
  };
#endif

#if defined(EVE_SPECIAL_TESTS)
  #ifndef SPY_SUPPORTS_FP16_TYPE
    #error "Special fp16 test requires compiler support for _Float16 type"
  #endif

  TTS_CASE("emulated float16 conversion - f32 to f16")
  {
    auto is_nan = [](uint16_t bits) {
      return ((bits & 0x7C00u) == 0x7C00u) && ((bits & 0x03FFu) != 0);
    };

    for (uint32_t f32_bits = 0u; f32_bits < eve::valmax(eve::as<uint32_t>{}); ++f32_bits)
    {
      float f32 = std::bit_cast<float>(f32_bits);

      uint16_t mf16 = eve::_::emulated_fp32_to_fp16(f32);
      uint16_t cf16 = std::bit_cast<uint16_t>(static_cast<_Float16>(f32));

      if (eve::is_nan(f32)) TTS_EXPECT(is_nan(mf16) && is_nan(cf16));
      else                  TTS_EQUAL(mf16, cf16);
    }
  };

  TTS_CASE("emulated float16 conversion - f32 to f16 simd")
  {
    auto is_nan = [](auto bits) {
      return ((bits & uint16_t(0x7C00)) == 0x7C00u) && ((bits & uint16_t(0x03FF)) != 0u);
    };

    auto run_for = [&]<std::ptrdiff_t N>(std::integral_constant<std::ptrdiff_t, N>) {
      TTS_WHEN("cardinal = " << N)
      {
        using wf16_t = eve::wide<eve::float16_t, eve::fixed<N>>;
        using wf32_t = eve::wide<float, eve::fixed<N>>;
        using wu16_t = eve::wide<uint16_t, eve::fixed<N>>;

        for (uint64_t base = 0u; base < eve::valmax(eve::as<uint32_t>{}); base += N)
        {
          wf32_t f32 = [&](auto i) { return std::bit_cast<float>(static_cast<uint32_t>(base + i)); };
          wf16_t mf16 = eve::_::emulated_simd_fp32_to_fp16(f32);

          wu16_t expected = [&](auto i) {
            float scalar_f32 = std::bit_cast<float>(static_cast<uint32_t>(base + i));
            return std::bit_cast<uint16_t>(static_cast<_Float16>(scalar_f32));
          };

          wu16_t actual = eve::bit_cast(mf16, eve::as<wu16_t>{});

          TTS_EXPECT(eve::all((actual == expected) || (is_nan(actual) && is_nan(expected))));
        }
      }
    };

    constexpr uint32_t max_c = eve::expected_cardinal_v<float> * 2;
    constexpr std::size_t seq_size = std::countr_zero(max_c) + 1;

    [&]<std::size_t... I>(std::index_sequence<I...>) {
      (run_for(std::integral_constant<std::ptrdiff_t, 1LL << I>{}), ...);
    }(std::make_index_sequence<seq_size>{});
  };
#endif

TTS_CASE("emulated float16 conversion - f32 roundtrip")
{
  auto is_nan = [](uint16_t bits) {
    return ((bits & 0x7C00u) == 0x7C00u) && ((bits & 0x03FFu) != 0);
  };

  for (uint16_t f16_bits = 0u; f16_bits < eve::valmax(eve::as<uint16_t>{}); ++f16_bits)
  {
    float f32 = eve::_::emulated_fp16_to_fp32(f16_bits);
    uint16_t roundtrip = eve::_::emulated_fp32_to_fp16(f32);

    // special case for NaN: payload is not conserved
    if (is_nan(f16_bits)) TTS_EXPECT(is_nan(roundtrip));
    else                  TTS_EQUAL(roundtrip, f16_bits);
  }
};

TTS_CASE("emulated float16 conversion - f32 roundtrip (simd)")
{
  auto run_for = [&]<std::ptrdiff_t N>(std::integral_constant<std::ptrdiff_t, N>) {
    TTS_WHEN("cardinal = " << N)
    {
      using wf16_t = eve::wide<eve::float16_t, eve::fixed<N>>;
      using wf32_t = eve::wide<float, eve::fixed<N>>;

      for (uint32_t base = 0u; base < eve::valmax(eve::as<uint16_t>{}); base += N)
      {
        wf16_t input = [&](auto i) {
          return eve::bit_cast(static_cast<uint16_t>(base + i), eve::as<eve::float16_t>{});
        };

        wf32_t f32       = eve::_::emulated_simd_fp16_to_fp32(input);
        wf16_t roundtrip = eve::_::emulated_simd_fp32_to_fp16(f32);

        TTS_IEEE_EQUAL(input, roundtrip);
      }
    }
  };

  constexpr uint32_t max_c = eve::expected_cardinal_v<eve::float16_t> * 2;
  constexpr std::size_t seq_size = std::countr_zero(max_c) + 1;

  [&]<std::size_t... I>(std::index_sequence<I...>) {
    (run_for(std::integral_constant<std::ptrdiff_t, 1LL << I>{}), ...);
  }(std::make_index_sequence<seq_size>{});
};

TTS_CASE("emulated float16 conversion - f16 special")
{
  auto cases = tts::limits(tts::type<float>{});

  TTS_EXPECT(eve::is_nan(eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(cases.nan))));

  TTS_EXPECT(eve::is_infinite(eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(cases.inf))));
  TTS_EXPECT(eve::is_positive(eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(cases.inf))));

  TTS_EXPECT(eve::is_infinite(eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(cases.minf))));
  TTS_EXPECT(eve::is_negative(eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(cases.minf))));

  TTS_EQUAL(eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(cases.mzero)), -0.0f);
  TTS_EXPECT(eve::is_negative(eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(cases.mzero))));

  TTS_EQUAL(eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(cases.zero)), 0.0f);
  TTS_EXPECT(eve::is_positive(eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(cases.zero))));

  // Smallest positive denormal in FP16: 2^-24 ≈ 5.960464477539063e-08
  float smallest_denormal = 5.960464477539063e-08f;
  std::uint16_t fp16_bits = eve::_::emulated_fp32_to_fp16(smallest_denormal);
  float converted_back = eve::_::emulated_fp16_to_fp32(fp16_bits);
  TTS_EXPECT(converted_back > 0.0f);
  TTS_EXPECT(converted_back < 6.103515625e-05f);

  // Test a few denormal values
  float denormal1 = 1.0e-07f;  // Should become denormal
  std::uint16_t bits1 = eve::_::emulated_fp32_to_fp16(denormal1);
  float back1 = eve::_::emulated_fp16_to_fp32(bits1);
  TTS_EXPECT(back1 > 0.0f);
  TTS_EXPECT(back1 < 6.103515625e-05f);

  float denormal2 = 3.0e-06f;  // Should become denormal
  std::uint16_t bits2 = eve::_::emulated_fp32_to_fp16(denormal2);
  float back2 = eve::_::emulated_fp16_to_fp32(bits2);
  TTS_EXPECT(back2 > 0.0f);
  TTS_EXPECT(back2 < 6.103515625e-05f);

  // Test negative denormals
  float neg_denormal = -1.0e-07f;
  std::uint16_t neg_bits = eve::_::emulated_fp32_to_fp16(neg_denormal);
  float neg_back = eve::_::emulated_fp16_to_fp32(neg_bits);
  TTS_EXPECT(neg_back < 0.0f);
  TTS_EXPECT(neg_back > -6.103515625e-05f);

  // Test positive values too small to represent (should round to zero)
  float too_small = 1.0e-10f;
  std::uint16_t zero_bits = eve::_::emulated_fp32_to_fp16(too_small);
  float zero_back = eve::_::emulated_fp16_to_fp32(zero_bits);
  TTS_EQUAL(zero_back, 0.0f);
  TTS_EXPECT(eve::is_positive(zero_back));

  // Test negative values too small to represent (should round to zero)
  float neg_too_small = -1.0e-10f;
  std::uint16_t neg_zero_bits = eve::_::emulated_fp32_to_fp16(neg_too_small);
  float neg_zero_back = eve::_::emulated_fp16_to_fp32(neg_zero_bits);
  TTS_EQUAL(neg_zero_back, -0.0f);
  TTS_EXPECT(eve::is_negative(neg_zero_back));

  // overflow to +infinity
  float overflow_pos = eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(65520.0f));
  TTS_EXPECT(eve::is_infinite(overflow_pos));
  TTS_EXPECT(eve::is_positive(overflow_pos));

  // overflow to +infinity - valmax rounding edge case
  float overflow_pos_r = eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(65519.0f));
  TTS_EXPECT(!eve::is_infinite(overflow_pos_r));
  TTS_EXPECT(eve::is_positive(overflow_pos_r));

  // underflow to -infinity
  float overflow_neg = eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(-65520.0f));
  TTS_EXPECT(eve::is_infinite(overflow_neg));
  TTS_EXPECT(eve::is_negative(overflow_neg));

  // underflow to -infinity - valmax rounding edge case
  float overflow_neg_r = eve::_::emulated_fp16_to_fp32(eve::_::emulated_fp32_to_fp16(-65519.0f));
  TTS_EXPECT(!eve::is_infinite(overflow_neg_r));
  TTS_EXPECT(eve::is_negative(overflow_neg_r));
};

TTS_CASE("test emulated float16 comparison")
{
  auto cmp = [](uint16_t a, uint16_t b) { return eve::_::emulated_fp16_compare(a, b); };

  auto expect_eq = [&](uint16_t a, uint16_t b) {
    TTS_EXPECT(cmp(a, b) == std::partial_ordering::equivalent);
    TTS_EXPECT(cmp(b, a) == std::partial_ordering::equivalent);
  };

  auto expect_unordered = [&](uint16_t a, uint16_t b) {
    TTS_EQUAL(cmp(a, b), std::partial_ordering::unordered);
    TTS_EQUAL(cmp(b, a), std::partial_ordering::unordered);
  };

  auto expect_greater = [&](uint16_t a, uint16_t b) {
    TTS_EXPECT(cmp(a, b) == std::partial_ordering::greater);
    TTS_EXPECT(cmp(b, a) == std::partial_ordering::less);
  };

  uint16_t zero = std::bit_cast<uint16_t>(static_cast<eve::float16_t>(0.0f));
  uint16_t one = std::bit_cast<uint16_t>(static_cast<eve::float16_t>(1.0f));
  uint16_t mone = std::bit_cast<uint16_t>(static_cast<eve::float16_t>(-1.0f));
  uint16_t mzero = std::bit_cast<uint16_t>(static_cast<eve::float16_t>(-0.0f));
  uint16_t inf = std::bit_cast<uint16_t>(eve::inf(eve::as<eve::float16_t>{}));
  uint16_t minf = std::bit_cast<uint16_t>(eve::minf(eve::as<eve::float16_t>{}));
  uint16_t nan = std::bit_cast<uint16_t>(eve::nan(eve::as<eve::float16_t>{}));
  uint16_t subnorm = std::bit_cast<uint16_t>(static_cast<eve::float16_t>(3e-6f));
  uint16_t msubnorm = std::bit_cast<uint16_t>(static_cast<eve::float16_t>(-1e-7f));
  uint16_t smaller_subnorm = std::bit_cast<uint16_t>(static_cast<eve::float16_t>(1e-7f));

  // normal values
  expect_eq(zero, mzero);

  expect_greater(one, zero);
  expect_greater(one, mzero);

  expect_greater(zero, mone);
  expect_greater(mzero, mone);

  expect_greater(one, mone);

  // infinity
  expect_greater(inf, minf);
  expect_greater(inf, zero);
  expect_greater(inf, mzero);
  expect_greater(inf, subnorm);
  expect_greater(inf, msubnorm);
  expect_greater(zero, minf);
  expect_greater(mzero, minf);

  // NaN
  expect_unordered(nan, nan);
  expect_unordered(nan, one);
  expect_unordered(nan, zero);
  expect_unordered(nan, mzero);
  expect_unordered(nan, inf);
  expect_unordered(nan, minf);
  expect_unordered(nan, subnorm);
  expect_unordered(nan, msubnorm);

  // Subnormals
  expect_greater(subnorm, smaller_subnorm);
  expect_greater(subnorm, msubnorm);
  expect_greater(smaller_subnorm, msubnorm);
};
