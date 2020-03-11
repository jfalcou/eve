//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_TRUNC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_TRUNC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> trunc_(EVE_SUPPORTS(neon128_),
                                             wide<T, N, neon64_> const &v0) noexcept
  {
    if constexpr(std::is_integral_v<T>) return v0;
#if __ARM_ARCH >= 8
    if constexpr(std::is_same_v<T, double>)
#  if defined(__aarch64__)
      return vrnd_f64(v0);
#  else
      return map(trunc, v0);
#  endif
    if constexpr(std::is_same_v<T, float>) return vrnd_f32(v0);
#else
    if constexpr(std::is_floating_point_v<T>) return map(trunc, v0);
#endif
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> trunc_(EVE_SUPPORTS(neon128_),
                                              wide<T, N, neon128_> const &v0) noexcept
  {
    if constexpr(std::is_integral_v<T>) return v0;

#if __ARM_ARCH >= 8
    if constexpr(std::is_same_v<T, double>)
#  if defined(__aarch64__)
      return vrndq_f64(v0);
#  else
      return map(ceil, v0);
#  endif
    if constexpr(std::is_same_v<T, float>) return vrndq_f32(v0);
#else
    if constexpr(std::is_floating_point_v<T>) return map(trunc, v0);
#endif
  }
}

#endif
