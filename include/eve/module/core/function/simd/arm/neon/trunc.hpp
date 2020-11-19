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
  EVE_FORCEINLINE wide<T, N, ABI> trunc_(EVE_SUPPORTS(neon128_)
                                       , wide<T, N, ABI> const& v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

         if constexpr( cat == category::float32x2) return vrnd_f32(v);
    else if constexpr( cat == category::float32x4) return vrndq_f32(v);
#  if defined(__aarch64__) && __ARM_ARCH >= 8
    else if constexpr( cat == category::float64x1) return vrnd_f64(v);
    else if constexpr( cat == category::float64x2) return vrndq_f64(v);
#  endif
    else                                           return map(trunc, v);
  }
}

// #include <eve/detail/overload.hpp>
// #include <eve/detail/abi.hpp>
// #include <eve/forward.hpp>
// #include <eve/function/raw.hpp>
// #include <eve/concept/value.hpp>

// namespace eve::detail
// {
//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_> trunc_(EVE_SUPPORTS(neon128_),
//                                              wide<T, N, arm_64_> const &v0) noexcept
//   {
//     if constexpr(integral_value<T>) return v0;
// #if __ARM_ARCH >= 8
//     else if constexpr(std::same_as<T, double>)
// #  if defined(__aarch64__)
//       return vrnd_f64(v0);
// #  else
//       return map(trunc, v0);
// #  endif
//     else if constexpr(std::same_as<T, float>) return vrnd_f32(v0);
// #else
//     else if constexpr(floating_value<T>) return map(trunc, v0);
// #endif
// }

//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_> trunc_(EVE_SUPPORTS(neon128_),
//                                              raw_type const &,
//                                              wide<T, N, arm_64_> const &v0) noexcept
//   {
//     return trunc(v0);
//   }

//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_> trunc_(EVE_SUPPORTS(neon128_),
//                                               wide<T, N, arm_128_> const &v0) noexcept
//   {
//     if constexpr(integral_value<T>) return v0;
// #if __ARM_ARCH >= 8
//     else if constexpr(std::same_as<T, double>)
// #  if defined(__aarch64__)
//       return vrndq_f64(v0);
// #  else
//       return map(trunc, v0);
// #  endif
//    else if constexpr(std::same_as<T, float>) return vrndq_f32(v0);
// #else
//    else if constexpr(floating_value<T>) return map(trunc, v0);
// #endif
//   }

//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_> trunc_(EVE_SUPPORTS(neon128_),
//                                              raw_type const &,
//                                              wide<T, N, arm_128_> const &v0) noexcept
//   {
//     return trunc(v0);
//   }

// }
