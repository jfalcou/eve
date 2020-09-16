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
#include <eve/constant/zero.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename N>
  EVE_FORCEINLINE wide<float, N, neon64_> refine_rec_(EVE_SUPPORTS(neon128_),
                                                      wide<float, N, neon64_> const &a0,
                                                      wide<float, N, neon64_> const &a1) noexcept
  {
    return vmul_f32(vrecps_f32(a0, a1), a1);
  }

  template<typename N>
  EVE_FORCEINLINE wide<float, N, neon128_> refine_rec_(EVE_SUPPORTS(neon128_),
                                                       wide<float, N, neon128_> const &a0,
                                                       wide<float, N, neon128_> const &a1) noexcept
  {
    return vmulq_f32(vrecpsq_f32(a0, a1), a1);
  }

#if defined(__aarch64__)
  template<typename N>
  EVE_FORCEINLINE wide<double, N, neon64_> refine_rec_(EVE_SUPPORTS(neon128_),
                                                       wide<double, N, neon64_> const &a0,
                                                       wide<double, N, neon64_> const &a1) noexcept
  {
    auto x = vmul_f64(vrecps_f64(a0, a1), a1);
    return vmul_f64(vrecps_f64(a0, x), x);
  }

  template<typename N>
  EVE_FORCEINLINE wide<double, N, neon128_>
                  refine_rec_(EVE_SUPPORTS(neon128_),
                              wide<double, N, neon128_> const &a0,
                              wide<double, N, neon128_> const &a1) noexcept
  {
    auto x = vmulq_f64(vrecpsq_f64(a0, a1), a1);
    return vmulq_f64(vrecpsq_f64(a0, x), x);
  }
#endif
}

