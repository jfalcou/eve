//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/raw.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Raw version
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, arm_64_>
                  sqrt_(EVE_SUPPORTS(neon128_), raw_type const &, wide<T, N, arm_64_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<T, double> && supports_aarch64) { return vsqrt_f64(v0); }
    else if constexpr(std::is_same_v<T, float>)
    {
      if constexpr(supports_aarch64) { return vsqrt_f32(v0); }
      else
      {
        return if_else(v0, v0 * raw(rsqrt)(v0), v0);
      }
    }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, arm_128_>
                  sqrt_(EVE_SUPPORTS(neon128_), raw_type const &, wide<T, N, arm_128_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<T, double> && supports_aarch64) { return vsqrtq_f64(v0); }
    else if constexpr(std::is_same_v<T, float>)
    {
      if constexpr(supports_aarch64) { return vsqrtq_f32(v0); }
      else
      {
        return if_else(v0, v0 * raw(rsqrt)(v0), v0);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  // Basic version
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, arm_64_> sqrt_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, arm_64_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<T, double> && supports_aarch64) { return vsqrt_f64(v0); }
    else if constexpr(std::is_same_v<T, float>)
    {
      if constexpr(supports_aarch64) { return vsqrt_f32(v0); }
      else
      {
        auto that = if_else(v0, v0 * rsqrt(v0), v0);
        if constexpr(platform::supports_invalids) { return if_else(is_not_finite(v0), v0, that); }
        else
        {
          return that;
        }
      }
    }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, arm_128_> sqrt_(EVE_SUPPORTS(neon128_),
                                             wide<T, N, arm_128_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<T, double> && supports_aarch64) { return vsqrtq_f64(v0); }
    else if constexpr(std::is_same_v<T, float>)
    {
      if constexpr(supports_aarch64) { return vsqrtq_f32(v0); }
      else
      {
        auto that = if_else(v0, v0 * rsqrt(v0), v0);
        if constexpr(platform::supports_invalids) { return if_else(is_not_finite(v0), v0, that); }
        else
        {
          return that;
        }
      }
    }
  }
}
