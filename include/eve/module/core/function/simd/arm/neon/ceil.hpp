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

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, arm_64_> ceil_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, arm_64_> const &v0) noexcept
  {
#if __ARM_ARCH >= 8
    if constexpr(std::is_same_v<T, double>)
#  if defined(__aarch64__)
      return vrndp_f64(v0);
#  else
      return map(ceil, v0);
#  endif
    if constexpr(std::is_same_v<T, float>) return vrndp_f32(v0);
#else
    if constexpr(std::is_floating_point_v<T>) return map(ceil, v0);
#endif
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, arm_128_> ceil_(EVE_SUPPORTS(neon128_),
                                             wide<T, N, arm_128_> const &v0) noexcept
  {
#if __ARM_ARCH >= 8
    if constexpr(std::is_same_v<T, double>)
#  if defined(__aarch64__)
      return vrndpq_f64(v0);
#  else
      return map(ceil, v0);
#  endif
    if constexpr(std::is_same_v<T, float>) return vrndpq_f32(v0);
#else
    if constexpr(std::is_floating_point_v<T>) return map(ceil, v0);
#endif
  }
}

