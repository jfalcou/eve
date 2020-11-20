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
  EVE_FORCEINLINE wide<T, N, ABI> floor_(EVE_SUPPORTS(neon128_)
                                       , wide<T, N, ABI> const& v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

         if constexpr( cat == category::float32x2) return vrndm_f32(v);
    else if constexpr( cat == category::float32x4) return vrndmq_f32(v);
#  if defined(__aarch64__) && __ARM_ARCH >= 8
         if constexpr( cat == category::float64x1) return vrndm_f64(v);
    else if constexpr( cat == category::float64x2) return vrndmq_f64(v);
#  endif
    else                                           return map(floor, v);
  }
}
