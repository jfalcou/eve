//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> div_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1) noexcept
  {
#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>)
      return vdiv_f64(v0, v1);
    else if constexpr(std::is_same_v<T, float>)
      return vdiv_f32(v0, v1);
    else
      return map(div, v0, v1);
#else
    return div_(EVE_RETARGET(cpu_), v0, v1);
#endif
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> div_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1) noexcept
  {
#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>)
      return vdivq_f64(v0, v1);
    else if constexpr(std::is_same_v<T, float>)
      return vdivq_f32(v0, v1);
    else
      return map(div, v0, v1);
#else
    return div_(EVE_RETARGET(cpu_), v0, v1);
#endif
  }
}

#endif
