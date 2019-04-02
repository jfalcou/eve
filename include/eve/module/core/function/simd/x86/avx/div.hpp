//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename T, typename N>
  EVE_FORCEINLINE wide<double, N, avx_> div_(EVE_SUPPORTS(avx_),
                                             wide<double, N, avx_> const &v0,
                                             wide<double, N, avx_> const &v1) noexcept
  {
    return _mm_div_pd(v0, v1);
  }
  
  // -----------------------------------------------------------------------------------------------
  // single
  template<typename T, typename N>
  EVE_FORCEINLINE wide<float, N, avx_> div_(EVE_SUPPORTS(avx_),
                                             wide<float, N, avx_> const &v0,
                                             wide<float, N, avx_> const &v1) noexcept
  {
    return _mm_div_ps(v0, v1);
  }

}

#endif
