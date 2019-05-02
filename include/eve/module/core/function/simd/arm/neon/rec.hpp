//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_REC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/refine_rec.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename N>
  EVE_FORCEINLINE wide<double, N, neon64_> rec_(EVE_SUPPORTS(neon128_),
                                                   wide<double, N, neon64_> const &v0) noexcept
  {
    // estimate 1/x with an extra NR step for full precision
    auto a = refine_rec(v0, rec[raw_](v0) );
    return refine_rec(v0, a );
  }


  template<typename N>
  EVE_FORCEINLINE wide<float, N, neon64_> rec_(EVE_SUPPORTS(neon128_),
                                                   wide<float, N, neon64_> const &v0) noexcept
  {
    return vrecpeq_f32(v0);
  }

#if defined(__aarch64__)

  template<typename N>
  EVE_FORCEINLINE wide<double, N, neon64_> rec_(EVE_SUPPORTS(neon128_),
                                                   wide<float, N, neon64_> const &v0) noexcept
  {
    return t_t(1.0/extract<0>(v0));
  }

  template<typename N>
  EVE_FORCEINLINE wide<double, N, neon128_> rec_(EVE_SUPPORTS(neon128_),
                                                    wide<double, N, neon128_> const &v0) noexcept
  {
      auto x = vmulq_f64(vrecpsq_f64(v0, a1), a1);
      return vmulq_f64(vrecpsq_f64(v0, x), x);
  }
  
  template<typename N>
  EVE_FORCEINLINE wide<double, N, neon64_> rec_(EVE_SUPPORTS(neon128_),
                                                   raw_type const &
                                                   wide<float, N, neon64_> const &v0) noexcept
  {
    return rec(v0));
  }

#endif
  
}

#endif
