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
  EVE_FORCEINLINE wide<T, N, ABI> ceil_(EVE_SUPPORTS(neon128_)
                                       , wide<T, N, ABI> const& v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();


         if constexpr( cat == category::float32x2) return vrndp_f32(v);
    else if constexpr( cat == category::float32x4) return vrndpq_f32(v);
#  if defined(__aarch64__) && __ARM_ARCH >= 8
         if constexpr( cat == category::float64x1) return vrndp_f64(v);
    else if constexpr( cat == category::float64x2) return vrndpq_f64(v);
#  endif
    else                                           return map(ceil, v);
  }
}

// #include <eve/detail/overload.hpp>
// #include <eve/detail/abi.hpp>
// #include <eve/forward.hpp>
// #include <type_traits>
// #include <eve/concept/value.hpp>

// namespace eve::detail
// {
//   template<floating_real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_> ceil_(EVE_SUPPORTS(neon128_),
//                                             wide<T, N, arm_64_> const &v0) noexcept
//   {
// #if __ARM_ARCH >= 8
//     if constexpr(std::is_same_v<T, double>)
// #  if defined(__aarch64__)
//       return vrndp_f64(v0);
// #  else
//       return map(ceil, v0);
// #  endif
//     if constexpr(std::is_same_v<T, float>) return vrndp_f32(v0);
// #else
//     if constexpr(std::is_floating_point_v<T>) return map(ceil, v0);
// #endif
//   }

//   template<floating_real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_> ceil_(EVE_SUPPORTS(neon128_),
//                                              wide<T, N, arm_128_> const &v0) noexcept
//   {
// #if __ARM_ARCH >= 8
//     if constexpr(std::is_same_v<T, double>)
// #  if defined(__aarch64__)
//       return vrndpq_f64(v0);
// #  else
//       return map(ceil, v0);
// #  endif
//     if constexpr(std::is_same_v<T, float>) return vrndpq_f32(v0);
// #else
//     if constexpr(std::is_floating_point_v<T>) return map(ceil, v0);
// #endif
//   }
// }
