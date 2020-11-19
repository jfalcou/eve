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

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> nearest_(EVE_SUPPORTS(neon128_)
                                          , wide<T, N, ABI> const& v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

#  if defined(__aarch64__) && __ARM_ARCH >= 8
    if constexpr( cat == category::float64x1) return vrndn_f64(v);
    else if constexpr( cat == category::float64x2) return vrndnq_f64(v);
    else                                           return map(nearest, v);
#  else
    return map(nearest, v);
#  endif
  }
}
// #include <eve/detail/implementation.hpp>
// #include <type_traits>

// namespace eve::detail
// {
//   template<floating_real_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_> nearest_(EVE_SUPPORTS(neon128_),
//                                                wide<T, N, arm_64_> const &v0) noexcept
//   {
// #if __ARM_ARCH >= 8
//     if constexpr(std::is_same_v<T, double>)
// #  if defined(__aarch64__)
//       return vrndn_f64(v0);
// #  else
//       return map(nearest, v0);
// #  endif
//     if constexpr(std::is_same_v<T, float>) return vrndn_f32(v0);
// #else
//     if constexpr(std::is_floating_point_v<T>) return map(nearest, v0);
// #endif
//   }

//   template<floating_real_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_> nearest_(EVE_SUPPORTS(neon128_),
//                                                 wide<T, N, arm_128_> const &v0) noexcept
//   {
// #if __ARM_ARCH >= 8
//     if constexpr(std::is_same_v<T, double>)
// #  if defined(__aarch64__)
//       return vrndnq_f64(v0);
// #  else
//       return map(ceil, v0);
// #  endif
//     if constexpr(std::is_same_v<T, float>) return vrndnq_f32(v0);
// #else
//     if constexpr(std::is_floating_point_v<T>) return map(nearest, v0);
// #endif
//   }
// }
