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
#include <eve/function/raw.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> trunc_(EVE_SUPPORTS(neon128_),
                                             wide<T, N, neon64_> const &v0) noexcept
  {
    if constexpr(integral_value<T>) return v0;
#if __ARM_ARCH >= 8
    else if constexpr(std::same_as<T, double>)
#  if defined(__aarch64__)
      return vrnd_f64(v0);
#  else
      return map(trunc, v0);
#  endif
    else if constexpr(std::same_as<T, float>) return vrnd_f32(v0);
#else
    else if constexpr(floating_value<T>) return map(trunc, v0);
#endif
}

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> trunc_(EVE_SUPPORTS(neon128_),
                                             raw_type const &,
                                             wide<T, N, neon64_> const &v0) noexcept
  {
    return trunc(v0);
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> trunc_(EVE_SUPPORTS(neon128_),
                                              wide<T, N, neon128_> const &v0) noexcept
  {
    if constexpr(integral_value<T>) return v0;
#if __ARM_ARCH >= 8
    else if constexpr(std::same_as<T, double>)
#  if defined(__aarch64__)
      return vrndq_f64(v0);
#  else
      return map(trunc, v0);
#  endif
   else if constexpr(std::same_as<T, float>) return vrndq_f32(v0);
#else
   else if constexpr(floating_value<T>) return map(trunc, v0);
#endif
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> trunc_(EVE_SUPPORTS(neon128_),
                                             raw_type const &,
                                             wide<T, N, neon128_> const &v0) noexcept
  {
    return trunc(v0);
  }

}

#endif
