//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_AVERAGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_AVERAGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename N>
  EVE_FORCEINLINE wide<uint16_t, N, sse_>
                  average_(EVE_SUPPORTS(sse2_)
                          , wide<uint16_t, N, sse_> const &v0
                          , wide<uint16_t, N, sse_> const &v1) noexcept
  {
    return _mm_avg_epu16(v0, v1);
  }
  
  template<typename N>
  EVE_FORCEINLINE wide<uint8_t, N, sse_>
                  average_(EVE_SUPPORTS(sse2_)
                          , wide<uint8_t, N, sse_> const &v0
                          , wide<uint8_t, N, sse_> const &v1) noexcept
  {
    return _mm_avg_epu8(v0, v1);
  }  
}

#endif
