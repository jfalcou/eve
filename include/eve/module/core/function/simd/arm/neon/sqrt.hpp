//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_SQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_SQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/tags.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Raw version
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_>
                  sqrt_(EVE_SUPPORTS(neon128_), raw_type const &, wide<T, N, neon64_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<T, double> && supports_aarch64) { return vsqrt_f64(v0); }
    else if constexpr(std::is_same_v<T, float>)
    {
      if constexpr(supports_aarch64) { return vsqrt_f32(v0); }
      else
      {
        return if_else(v0, v0 * raw_(rsqrt)(v0), v0);
      }
    }
    else
    {
      return map(eve::sqrt, v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_>
                  sqrt_(EVE_SUPPORTS(neon128_), raw_type const &, wide<T, N, neon128_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<T, double> && supports_aarch64) { return vsqrtq_f64(v0); }
    else if constexpr(std::is_same_v<T, float>)
    {
      if constexpr(supports_aarch64) { return vsqrtq_f32(v0); }
      else
      {
        return if_else(v0, v0 * raw_(rsqrt)(v0), v0);
      }
    }
    else
    {
      return map(eve::sqrt, v0);
    }
  }

  //------------------------------------------------------------------------------------------------
  // Basic version
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> sqrt_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon64_> const &v0) noexcept
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
    else
    {
      return map(eve::sqrt, v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> sqrt_(EVE_SUPPORTS(neon128_),
                                             wide<T, N, neon128_> const &v0) noexcept
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
    else
    {
      return map(eve::sqrt, v0);
    }
  }
}

#endif
