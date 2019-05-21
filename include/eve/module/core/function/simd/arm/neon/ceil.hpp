//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_CEIL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_CEIL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/sub.hpp>
#include <eve/forward.hpp>

// #if __ARM_ARCH >= 8 to put somewhere

namespace eve::detail
{
  template<typename N>
  EVE_FORCEINLINE wide<float, N, neon64_> ceil_(EVE_SUPPORTS(neon128_),
                                                   wide<float, N, neon64_> const &v0) noexcept
  {
    return vrndp_f32(v0);
  }

  template< typename N>
  EVE_FORCEINLINE wide<float, N, neon128_> ceil_(EVE_SUPPORTS(neon128_),
                                                    wide<float, N, neon128_> const &v0) noexcept
  {
    return vrndpq_f32(v0);
  }

#if defined(__aarch64__)
  template<typename N>
  EVE_FORCEINLINE wide<double, N, neon64_> ceil_(EVE_SUPPORTS(neon128_),
                                                   wide<double, N, neon64_> const &v0) noexcept
  {
    return vrndp_f64(v0);
  }

  template< typename N>
  EVE_FORCEINLINE wide<double, N, neon128_> ceil_(EVE_SUPPORTS(neon128_),
                                                    wide<double, N, neon128_> const &v0) noexcept
  {
    return vrndpq_f64(v0);
  }
#endif
  
}

#endif
