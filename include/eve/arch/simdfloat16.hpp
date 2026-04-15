//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/float16.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/countl_zero.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::_
{
  template<typename N>
  EVE_NOINLINE auto emulated_simd_fp16_to_fp32(wide<eve::float16_t, N> v) noexcept
  {
    auto u16      = bit_cast(v, as<wide<uint16_t, N>>{});
    auto u32      = convert(u16, as<uint32_t>{});
    auto sign     = (u32 & 0x8000u) << 16;
    auto exponent = (u32 & 0x7C00u) >> 10;
    auto mantissa = (u32 & 0x03FFu);

    // Normal
    auto normal_res = sign | ((exponent + 112) << 23) | (mantissa << 13);

    // Denormal / Zero
    auto shift = convert(countl_zero(mantissa), as<uint32_t>{}) - 21;
    auto denorm_mantissa = (mantissa << shift) & 0x03FFu;
    auto denorm_exp = 113 - shift;
    auto denorm_res = sign | (denorm_exp << 23) | (denorm_mantissa << 13);
    denorm_res = if_else(mantissa == 0, sign, denorm_res);

    // Inf / NaN
    auto inf_nan_res = sign | 0x7F800000u | (mantissa << 13);
    inf_nan_res = if_else(mantissa != 0, inf_nan_res | 0x400000u, inf_nan_res);

    auto result = if_else(exponent == 31, inf_nan_res,
                  if_else(exponent == 0, denorm_res, normal_res));

    return bit_cast(result, as<wide<float, N>>{});
  }

  template<typename N>
  EVE_NOINLINE auto emulated_simd_fp32_to_fp16(wide<float, N> v) noexcept
  {
    auto bits     = bit_cast(v, as<wide<uint32_t, N>>{});
    auto sign     = (bits & 0x80000000u) >> 16;
    auto mantissa = bits & 0x7FFFFFu;
    auto exponent = bit_cast((bits >> 23) & 0xFF, as<wide<int32_t, N>>{}) - 127;

    auto is_inf_nan = (bits & 0x7F800000u) == 0x7F800000u;
    auto is_nan     = is_inf_nan && (mantissa != 0);

    auto nan_payload = mantissa >> 13;
    nan_payload = if_else(nan_payload != 0, nan_payload, 1u);
    auto nan_res = sign | 0x7C00u | nan_payload;
    auto inf_res = sign | 0x7C00u;
    auto inf_nan_res = if_else(is_nan, nan_res, inf_res);

    auto is_overflow = exponent > 15;
    auto res_overflow = sign | 0x7C00u;

    auto is_tiny = exponent < -25;

    // Denormal handling
    auto mant_hidden = mantissa | 0x800000u;
    auto raw_shift   = -exponent - 1;
    auto safe_shift  = if_else(exponent <= -15, min(raw_shift, 24), 24);

    auto rounded_denorm    = mant_hidden >> safe_shift;
    auto one_v = one(as<wide<uint32_t, N>>{});
    auto remainder_denorm  = mant_hidden & ((one_v << safe_shift) - one_v);

    auto threshold_denorm  = one_v << (safe_shift - 1);
    auto should_inc_denorm = (remainder_denorm > threshold_denorm) ||
                             ((remainder_denorm == threshold_denorm) && ((rounded_denorm & 1u) != 0));

    rounded_denorm += if_else(should_inc_denorm, 1u, 0u);
    auto res_denorm = sign | rounded_denorm;

    // Normal handling
    auto fp16_exp_norm = convert(exponent + 15, as<uint32_t>{}) << 10;
    auto mant_norm     = mantissa >> 13;
    auto round_bits    = mantissa & 0x1FFFu;

    auto should_inc_norm = (round_bits > 0x1000u) || ((round_bits == 0x1000u) && ((mant_norm & 1u) != 0));
    mant_norm += if_else(should_inc_norm, 1u, 0u);

    auto norm_overflow = mant_norm == 0x0400u;
    mant_norm = if_else(norm_overflow, 0u, mant_norm);
    fp16_exp_norm += if_else(norm_overflow, 0x0400u, 0u);

    auto is_inf_post_round = (fp16_exp_norm >> 10) >= 31u;
    auto result_norm = if_else(is_inf_post_round, sign | 0x7C00u, sign | fp16_exp_norm | (mant_norm & 0x3FFu));

    auto res = if_else(exponent <= -15,
                       if_else(is_tiny, sign, res_denorm),
                       result_norm);

    res = if_else(is_overflow, res_overflow, res);
    res = if_else(is_inf_nan, inf_nan_res, res);

    return bit_cast(convert(res, as<uint16_t>{}), as<wide<eve::float16_t, N>>{});
  }
}
