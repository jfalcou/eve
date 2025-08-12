//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

TTS_CASE_TPL("test float16 conversions - floats", tts::types<float, double>)
<typename F>(tts::type<F>)
{
  auto cases = tts::limits(tts::type<float>{});

  TTS_EXPECT(eve::is_nan(static_cast<float>(eve::float16{ cases.nan })));

  TTS_EXPECT(eve::is_infinite(static_cast<float>(eve::float16{ cases.inf })));
  TTS_EXPECT(eve::is_positive(static_cast<float>(eve::float16{ cases.inf })));

  TTS_EXPECT(eve::is_infinite(static_cast<float>(eve::float16{ cases.minf })));
  TTS_EXPECT(eve::is_negative(static_cast<float>(eve::float16{ cases.minf })));

  TTS_EQUAL(static_cast<float>(eve::float16{ cases.mzero }), -0.0f);
  TTS_EXPECT(eve::is_negative(static_cast<float>(eve::float16{ cases.mzero })));

  TTS_EQUAL(static_cast<float>(eve::float16{ cases.zero }), 0.0f);
  TTS_EXPECT(eve::is_positive(static_cast<float>(eve::float16{ cases.zero })));
};

TTS_CASE_TPL("test float16 conversions - integrals", eve::test::scalar::integers)
<typename I>(tts::type<I>)
{
  TTS_EQUAL(static_cast<I>(eve::float16{I{0}}), I{0});
  TTS_EQUAL(static_cast<I>(eve::float16{I{30}}), I{30});
  if constexpr (std::is_signed_v<I>) {
    TTS_EQUAL(static_cast<I>(eve::float16{I{-11}}), I{-11});
  }

  I max_val = std::numeric_limits<I>::max();
  if (static_cast<long>(eve::maxflint(eve::as<eve::float16>{})) <= static_cast<long>(max_val))
  {
    I max_flint = static_cast<I>(eve::maxflint(eve::as<eve::float16>{}));
    TTS_EQUAL(static_cast<I>(eve::float16{max_flint}), max_flint);
  }
};

TTS_CASE_TPL("test emulated float16", tts::types<float, double>)
<typename F>(tts::type<F>)
{
  auto cases = tts::limits(tts::type<F>{});

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
  F smallest_denormal = 5.960464477539063e-08f;
  std::uint16_t fp16_bits = eve::detail::emulated_fp_to_fp16(smallest_denormal);
  F converted_back = eve::detail::emulated_fp16_to_fp32(fp16_bits);
  TTS_EXPECT(converted_back > 0.0f);
  TTS_EXPECT(converted_back < 6.103515625e-05f);

  // Test a few denormal values
  F denormal1 = 1.0e-07f;  // Should become denormal
  std::uint16_t bits1 = eve::detail::emulated_fp_to_fp16(denormal1);
  F back1 = eve::detail::emulated_fp16_to_fp32(bits1);
  TTS_EXPECT(back1 > 0.0f);
  TTS_EXPECT(back1 < 6.103515625e-05f);

  F denormal2 = 3.0e-06f;  // Should become denormal
  std::uint16_t bits2 = eve::detail::emulated_fp_to_fp16(denormal2);
  F back2 = eve::detail::emulated_fp16_to_fp32(bits2);
  TTS_EXPECT(back2 > 0.0f);
  TTS_EXPECT(back2 < 6.103515625e-05f);

  // Test negative denormals
  F neg_denormal = -1.0e-07f;
  std::uint16_t neg_bits = eve::detail::emulated_fp_to_fp16(neg_denormal);
  F neg_back = eve::detail::emulated_fp16_to_fp32(neg_bits);
  TTS_EXPECT(neg_back < 0.0f);
  TTS_EXPECT(neg_back > -6.103515625e-05f);

  // Test positive values too small to represent (should round to zero)
  F too_small = 1.0e-10f;
  std::uint16_t zero_bits = eve::detail::emulated_fp_to_fp16(too_small);
  F zero_back = eve::detail::emulated_fp16_to_fp32(zero_bits);
  TTS_EQUAL(zero_back, 0.0f);
  TTS_EXPECT(eve::is_positive(zero_back));

  // Test negative values too small to represent (should round to zero)
  F neg_too_small = -1.0e-10f;
  std::uint16_t neg_zero_bits = eve::detail::emulated_fp_to_fp16(neg_too_small);
  F neg_zero_back = eve::detail::emulated_fp16_to_fp32(neg_zero_bits);
  TTS_EQUAL(neg_zero_back, -0.0f);
  TTS_EXPECT(eve::is_negative(neg_zero_back));

  // overflow to +infinity
  F overflow_pos = eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(65505.0f));
  TTS_EXPECT(eve::is_infinite(overflow_pos));
  TTS_EXPECT(eve::is_positive(overflow_pos));

  // underflow to -infinity
  F overflow_neg = eve::detail::emulated_fp16_to_fp32(eve::detail::emulated_fp_to_fp16(-65505.0f));
  TTS_EXPECT(eve::is_infinite(overflow_neg));
  TTS_EXPECT(eve::is_negative(overflow_neg));
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

  uint16_t zero = eve::float16{0.0f}.bits();
  uint16_t one = eve::float16{1.0f}.bits();
  uint16_t mone = eve::float16{-1.0f}.bits();
  uint16_t mzero = eve::float16{-0.0f}.bits();
  uint16_t inf = eve::inf(eve::as<eve::float16>{}).bits();
  uint16_t minf = eve::minf(eve::as<eve::float16>{}).bits();
  uint16_t nan = eve::nan(eve::as<eve::float16>{}).bits();
  uint16_t subnorm = eve::float16{3e-6f}.bits();
  uint16_t msubnorm = eve::float16{-1e-7f}.bits();
  uint16_t smaller_subnorm = eve::float16{1e-7f}.bits();

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
