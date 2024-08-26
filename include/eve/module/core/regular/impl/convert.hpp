//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/impl/convert_helpers.hpp>

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
    using out_t = std::conditional_t<scalar_value<T>, U, as_wide_t<U, cardinal_t<T>>>;
    out_t res;

    auto outs = kumi::flatten_all(res, [](auto& m) { return &m; });
    auto ins  = kumi::flatten_all(v0);

    kumi::for_each(convert_lambda<O> {opts}, ins, outs);

    return res;
  }
}

template<callable_options O, value In, scalar_value Out>
requires (!product_type<In>)
EVE_FORCEINLINE auto convert_(EVE_REQUIRES(cpu_), O const&, In v0, [[maybe_unused]] as<Out> tgt) noexcept
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
        if constexpr (sizeof(out_ae_t) == sizeof(in_ea_t)) 
        {
          return bit_cast(v0, as<out_t> {});
        }
        else if constexpr (std::is_unsigned_v<in_ea_t> || std::is_floating_point_v<in_ea_t>)
        {
          using i_t = as<logical<wide<as_integer_t<in_ea_t, signed>, cardinal_t<In>>>>;
          return convert(bit_cast(v0, i_t {}), tgt);
        }
        else if constexpr (std::is_unsigned_v<out_ae_t> || std::is_floating_point_v<out_ae_t>)
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
      else if constexpr (O::contains(saturated2))
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
