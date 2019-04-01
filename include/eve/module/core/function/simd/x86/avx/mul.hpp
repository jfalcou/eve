//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename T, typename N>
  EVE_FORCEINLINE wide<double, N, avx_> mul_(EVE_SUPPORTS(avx_),
                                             wide<double, N, avx_> const &v0,
                                             wide<double, N, avx_> const &v1) noexcept
  {
    return _mm_mul_pd(v0, v1);
  }
  
  template<typename T, typename N>
  EVE_FORCEINLINE wide<float, N, avx_> mul_(EVE_SUPPORTS(avx_),
                                             wide<float, N, avx_> const &v0,
                                             wide<float, N, avx_> const &v1) noexcept
  {
    return _mm_mul_ps(v0, v1);
  }

}

#endif
