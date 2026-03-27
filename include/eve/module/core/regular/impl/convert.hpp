//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/impl/convert_helpers.hpp>
#include <eve/module/core/regular/is_finite.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/countl_zero.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/detail/category.hpp>

namespace eve::detail
{
  template<callable_options O, product_type T, product_type U>
  EVE_FORCEINLINE auto convert_(EVE_REQUIRES(cpu_), O const& opts, T const& v0, eve::as<U>)
  {
    if constexpr( std::same_as<element_type_t<T>, U> )
    {
      return v0;
    }
    else
    {
      using out_t = detail::conditional_t<scalar_value<T>, U, as_wide_t<U, cardinal_t<T>>>;
      out_t res;

      auto outs = kumi::flatten_all(res, [](auto& m) { return &m; });
      auto ins  = kumi::flatten_all(v0);

      kumi::for_each(convert_lambda<O> {opts}, ins, outs);

      return res;
    }
  }

  template<callable_options O, typename N>
  EVE_NOINLINE auto convert_(EVE_REQUIRES(cpu_), O const&, wide<eve::float16_t, N> v, as<float>) noexcept
    requires (!detail::supports_fp16_vector_ops)
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

  template<callable_options O, typename N, typename U>
  EVE_FORCEINLINE auto convert_(EVE_REQUIRES(cpu_), O const&, wide<eve::float16_t, N> v, as<U> tgt) noexcept
    requires (!std::same_as<U, float> && !std::same_as<U, eve::float16_t> && !detail::supports_fp16_vector_ops)
  {
    return convert(convert(v, as<float>{}), tgt);
  }

  template<callable_options O, typename N>
  EVE_NOINLINE auto convert_(EVE_REQUIRES(cpu_), O const&, wide<float, N> v, as<eve::float16_t>) noexcept
    requires (!detail::supports_fp16_vector_ops)
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

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE auto convert_(EVE_REQUIRES(cpu_), O const&, wide<T, N> v, as<eve::float16_t>) noexcept
    requires (!std::same_as<T, float> && !std::same_as<T, eve::float16_t> && !detail::supports_fp16_vector_ops)
  {
    return convert(convert(v, as<float>{}), as<eve::float16_t>{});
  }

  template<callable_options O, value In, scalar_value Out>
  EVE_FORCEINLINE auto convert_(EVE_REQUIRES(cpu_), O const&, In v0, [[maybe_unused]] as<Out> tgt) noexcept
    requires (!product_type<In>)
  {
    constexpr maybe_saturated<O, Out> maybe_saturate;

    using in_e_t = element_type_t<In>;

    if constexpr (std::same_as<in_e_t, Out>)
    {
      return v0;
    }
    else if constexpr (logical_scalar_value<In>)
    {
      return Out(v0.value());
    }
    else if constexpr (plain_scalar_value<In>)
    {
      if constexpr (floating_scalar_value<In> && integral_scalar_value<Out>)
      {
        EVE_ASSERT(is_finite(v0), "[EVE] - Convert to integral from floating point called on non finite value");
      }

      return static_cast<Out>(maybe_saturate(v0));
    }
    else // simd_value
    {
      if constexpr (logical_simd_value<In>)
      {
        using in_ea_t = as_arithmetic_t<in_e_t>;
        using out_ae_t = as_arithmetic_t<Out>;
        using out_t = as_wide_as_t<Out, In>;

        if constexpr (has_aggregated_abi_v<In> || has_aggregated_abi_v<out_t>)
        {
          // If input or output are aggregated, we slice and combine without lose of performance
          return out_t {eve::convert(v0.slice(lower_), tgt), eve::convert(v0.slice(upper_), tgt)};
        }
        else
        {
          if constexpr (has_emulated_abi_v<In> || has_emulated_abi_v<out_t>)
          {
            return map([&](auto m) { return convert(m, tgt); }, v0);
          }
          else if constexpr (sizeof(out_ae_t) == sizeof(in_ea_t))
          {
            return bit_cast(v0, as<out_t> {});
          }
          else if constexpr (std::is_unsigned_v<in_ea_t> || floating_scalar_value<in_ea_t>)
          {
            using i_t = as<logical<wide<as_integer_t<in_ea_t, signed>, cardinal_t<In>>>>;
            return convert(bit_cast(v0, i_t {}), tgt);
          }
          else if constexpr (std::is_unsigned_v<out_ae_t> || floating_scalar_value<out_ae_t>)
          {
            using i_t = as<logical<as_integer_t<out_ae_t, signed>>>;
            return bit_cast(convert(v0, i_t {}), as<out_t> {});
          }
          else
          {
            return convert_impl(EVE_TARGETS(current_api_type), v0, tgt);
          }
        }
      }
      else // wide
      {
        using N = cardinal_t<In>;

        constexpr auto c_i = categorize<In>();
        constexpr auto c_o = categorize<wide<Out, N>>();

        // helps with some ptrdiff_t conversions on macOS x86_64
        if constexpr (has_native_abi_v<In> && (c_i == c_o))
        {
          return bit_cast(v0, as<wide<Out, N>>{});
        }
        // Converting between integral of different signs is just a bit_cast away
        if constexpr (std::signed_integral<in_e_t> && std::unsigned_integral<Out>)
        {
          auto s_res = convert(maybe_saturate(v0), eve::as<std::make_signed_t<Out>> {});
          return bit_cast(s_res, eve::as<wide<Out, N>> {});
        }
        else if constexpr (std::unsigned_integral<in_e_t> && std::signed_integral<Out>)
        {
          auto u_res = convert(maybe_saturate(v0), eve::as<std::make_unsigned_t<Out>> {});
          return bit_cast(u_res, eve::as<wide<Out, N>> {});
        }
        else if constexpr (O::contains(saturated))
        {
          return convert_saturated(EVE_TARGETS(current_api_type), v0, tgt);
        }
        else
        {
          // Fallbacks to architecture-specific cases
          return convert_impl(EVE_TARGETS(current_api_type), v0, tgt);
        }
      }
    }
  }
}
