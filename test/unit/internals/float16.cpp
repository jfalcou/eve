//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#ifdef SPY_SUPPORTS_FP16_TYPE
// if the compiler provides fp16 softfloat support, use it to check the fp16 to fp32 routine
TTS_CASE("emulated float16 conversion - float16 to float32")
{
  for (uint16_t f16_bits = 0u; f16_bits < eve::valmax(eve::as<uint16_t>{}); ++f16_bits)
  {
    float f32 = eve::detail::emulated_fp16_to_fp32(f16_bits);

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

TTS_CASE("emulated float16 conversion - f32 roundtrip")
{
  // TODO: use eve::is_nan when fp16 elementwise_callable support is merged
  auto is_nan = [](uint16_t bits) {
    return ((bits & 0x7C00u) == 0x7C00u) && ((bits & 0x03FFu) != 0);
  };

  for (uint16_t f16_bits = 0u; f16_bits < eve::valmax(eve::as<uint16_t>{}); ++f16_bits)
  {
    float f32 = eve::detail::emulated_fp16_to_fp32(f16_bits);
    uint16_t roundtrip = eve::detail::emulated_fp_to_fp16(f32);

    // special case for NaN: payload is not conserved
    if (is_nan(f16_bits)) TTS_EXPECT(is_nan(roundtrip));
    else                  TTS_EQUAL(roundtrip, f16_bits);
  }
};

TTS_CASE("emulated float16 conversion - f16 roundtrip")
{
  auto cases = tts::limits(tts::type<float>{});

  TTS_EXPECT(eve::is_nan(eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(cases.nan))));

  TTS_EXPECT(eve::is_infinite(eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(cases.inf))));
  TTS_EXPECT(eve::is_positive(eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(cases.inf))));

  TTS_EXPECT(eve::is_infinite(eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(cases.minf))));
  TTS_EXPECT(eve::is_negative(eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(cases.minf))));

  TTS_EQUAL(eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(cases.mzero)), -0.0f);
  TTS_EXPECT(eve::is_negative(eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(cases.mzero))));

  TTS_EQUAL(eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(cases.zero)), 0.0f);
  TTS_EXPECT(eve::is_positive(eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(cases.zero))));

  // Smallest positive denormal in FP16: 2^-24 ≈ 5.960464477539063e-08
  float smallest_denormal = 5.960464477539063e-08f;
  std::uint16_t fp16_bits = eve::detail::emulated_fp_to_fp16(smallest_denormal);
  float converted_back = eve::detail::emulated_fp16_to_fp32(fp16_bits);
  TTS_EXPECT(converted_back > 0.0f);
  TTS_EXPECT(converted_back < 6.103515625e-05f);

  // Test a few denormal values
  float denormal1 = 1.0e-07f;  // Should become denormal
  std::uint16_t bits1 = eve::detail::emulated_fp_to_fp16(denormal1);
  float back1 = eve::detail::emulated_fp16_to_fp32(bits1);
  TTS_EXPECT(back1 > 0.0f);
  TTS_EXPECT(back1 < 6.103515625e-05f);

  float denormal2 = 3.0e-06f;  // Should become denormal
  std::uint16_t bits2 = eve::detail::emulated_fp_to_fp16(denormal2);
  float back2 = eve::detail::emulated_fp16_to_fp32(bits2);
  TTS_EXPECT(back2 > 0.0f);
  TTS_EXPECT(back2 < 6.103515625e-05f);

  // Test negative denormals
  float neg_denormal = -1.0e-07f;
  std::uint16_t neg_bits = eve::detail::emulated_fp_to_fp16(neg_denormal);
  float neg_back = eve::detail::emulated_fp16_to_fp32(neg_bits);
  TTS_EXPECT(neg_back < 0.0f);
  TTS_EXPECT(neg_back > -6.103515625e-05f);

  // Test positive values too small to represent (should round to zero)
  float too_small = 1.0e-10f;
  std::uint16_t zero_bits = eve::detail::emulated_fp_to_fp16(too_small);
  float zero_back = eve::detail::emulated_fp16_to_fp32(zero_bits);
  TTS_EQUAL(zero_back, 0.0f);
  TTS_EXPECT(eve::is_positive(zero_back));

  // Test negative values too small to represent (should round to zero)
  float neg_too_small = -1.0e-10f;
  std::uint16_t neg_zero_bits = eve::detail::emulated_fp_to_fp16(neg_too_small);
  float neg_zero_back = eve::detail::emulated_fp16_to_fp32(neg_zero_bits);
  TTS_EQUAL(neg_zero_back, -0.0f);
  TTS_EXPECT(eve::is_negative(neg_zero_back));

  // overflow to +infinity
  float overflow_pos = eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(65520.0f));
  TTS_EXPECT(eve::is_infinite(overflow_pos));
  TTS_EXPECT(eve::is_positive(overflow_pos));

  // overflow to +infinity - valmax rounding edge case
  float overflow_pos_r = eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(65519.0f));
  TTS_EXPECT(!eve::is_infinite(overflow_pos_r));
  TTS_EXPECT(eve::is_positive(overflow_pos_r));

  // underflow to -infinity
  float overflow_neg = eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(-65520.0f));
  TTS_EXPECT(eve::is_infinite(overflow_neg));
  TTS_EXPECT(eve::is_negative(overflow_neg));

  // underflow to -infinity - valmax rounding edge case
  float overflow_neg_r = eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(-65519.0f));
  TTS_EXPECT(!eve::is_infinite(overflow_neg_r));
  TTS_EXPECT(eve::is_negative(overflow_neg_r));
};

TTS_CASE("test emulated float16 comparison")
{
  auto cmp = [](uint16_t a, uint16_t b) { return eve::detail::emulated_fp16_compare(a, b); };

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

  uint16_t zero = eve::detail::float16_to_bits(eve::float16{0.0f});
  uint16_t one = eve::detail::float16_to_bits(eve::float16{1.0f});
  uint16_t mone = eve::detail::float16_to_bits(eve::float16{-1.0f});
  uint16_t mzero = eve::detail::float16_to_bits(eve::float16{-0.0f});
  uint16_t inf = eve::detail::float16_to_bits(eve::inf(eve::as<eve::float16>{}));
  uint16_t minf = eve::detail::float16_to_bits(eve::minf(eve::as<eve::float16>{}));
  uint16_t nan = eve::detail::float16_to_bits(eve::nan(eve::as<eve::float16>{}));
  uint16_t subnorm = eve::detail::float16_to_bits(eve::float16{3e-6f});
  uint16_t msubnorm = eve::detail::float16_to_bits(eve::float16{-1e-7f});
  uint16_t smaller_subnorm = eve::detail::float16_to_bits(eve::float16{1e-7f});

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
