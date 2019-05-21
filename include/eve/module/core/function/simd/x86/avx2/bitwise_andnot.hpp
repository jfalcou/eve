//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_BITWISE_ANDNOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_BITWISE_ANDNOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> bitwise_andnot_(EVE_SUPPORTS(avx2_),
                                                   wide<T, N, avx_> const &v0,
                                                   wide<T, N, avx_> const &v1) noexcept
  {
    if constexpr(std::is_same_v<T, float>) return _mm256_andnot_ps(v1, v0);
    if constexpr(std::is_same_v<T, double>) return _mm256_andnot_pd(v1, v0);
    if constexpr(std::is_integral_v<T>) return _mm256_andnot_si256(v1, v0);
  }
}
#endif
