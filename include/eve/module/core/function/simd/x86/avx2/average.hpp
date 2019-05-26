//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_AVERAGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_AVERAGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  EVE_FORCEINLINE wide<T, N, avx_>
                  average_(EVE_SUPPORTS(avx2_)
                          , wide<uint16_t, N, avx_> const &v0
                          , wide<uint16_t, N, avx_> const &v1) noexcept
  {
    return _mm256_avg_epu16(a0, a1);
  }
  
  template<typename N>
  EVE_FORCEINLINE wide<T, N, avx_>
                  average_(EVE_SUPPORTS(avx2_)
                          , wide<uint8_t, N, avx_> const &v0
                          , wide<uint8_t, N, avx_> const &v1) noexcept
  {
   return _mm256_avg_epu8(a0, a1);
  }
}

#endif
