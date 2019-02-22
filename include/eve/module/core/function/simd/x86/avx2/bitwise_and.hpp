//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_BITWISE_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_BITWISE_AND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_>
                  bitwise_and_(EVE_SUPPORTS(avx2_), wide<T, N, avx_> const &v0, wide<T, N, avx_> const &v1) noexcept
  {
    if constexpr(std::is_same_v<T, float>) return _mm256_and_ps(v0, v1);
    if constexpr(std::is_same_v<T, double>) return _mm256_and_pd(v0, v1);
    if constexpr(std::is_integral_v<T>) return _mm256_and_si256(v0, v1);
  }
}

#endif
