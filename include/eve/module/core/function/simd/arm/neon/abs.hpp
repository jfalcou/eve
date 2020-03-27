//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<scalar_real_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> abs_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0) noexcept
  {
    if constexpr(unsigned_scalar_value<T>) return v0;
#if defined(__aarch64__)
    else if constexpr(std::same_as<T, double>) return vabs_f64(v0);
#endif
    else if constexpr(std::same_as<T, float>) return vabs_f32(v0);
    else if constexpr(signed_integral_scalar_value<T>)
    {
           if constexpr(sizeof(T) == 8) return map(eve::abs, v0);
      else if constexpr(sizeof(T) == 4) return vabs_s32(v0);
      else if constexpr(sizeof(T) == 2) return vabs_s16(v0);
      else if constexpr(sizeof(T) == 1) return vabs_s8(v0);
    }
  }
  
  template<scalar_real_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> abs_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0) noexcept
  {
         if constexpr(unsigned_scalar_value<T>) return v0;
#if defined(__aarch64__)
    else if constexpr(std::same_as<T, double>) return vabsq_f64(v0);
#endif
    else if constexpr(std::same_as<T, float>) return vabsq_f32(v0);
    else if constexpr(signed_integral_scalar_value<T>)
    {
            if constexpr(sizeof(T) == 8) return map(eve::abs, v0);
       else if constexpr(sizeof(T) == 4) return vabsq_s32(v0);
       else if constexpr(sizeof(T) == 2) return vabsq_s16(v0);
       else if constexpr(sizeof(T) == 1) return vabsq_s8(v0);
    }
  }
}

#endif
