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
#include <eve/constant/zero.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>
                  mul_(EVE_SUPPORTS(sse2_), wide<T, N, sse_> v0, wide<T, N, sse_> const &v1) noexcept
  {
    return v0 *= v1;
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>
                  mul_(EVE_SUPPORTS(avx_), saturated_type const &, wide<T, N, sse_> v0, wide<T, N, sse_> const &v1) noexcept
  {
    if constexpr(supports_xop)
    {
           if constexpr(std::is_same_v<T, std::int32_t>) return  _mm_maccs_epi32(v0,v1,Zero(eve::as(v0)));
      else if constexpr(std::is_same_v<T, std::int16_t>) return  _mm_maccs_epi16(v0,v1,Zero(eve::as(v0)));
      else return mul_(EVE_RETARGET(cpu_), saturated_type(), v0, v1);
    }
    else return mul_(EVE_RETARGET(cpu_), saturated_type(), v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_>
                  mul_(EVE_SUPPORTS(avx_), wide<T, N, avx_> v0, wide<T, N, avx_> const &v1) noexcept
  {
    return v0 *= v1;
  }


}
