//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_DIV_HPP_INCLUDED

#include <eve/wide.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename T, typename N>
  EVE_FORCEINLINE wide<double, N, sse_> div_(EVE_SUPPORTS(sse2_),
                                             wide<double, N, sse_> const &v0,
                                             wide<double, N, sse_> const &v1) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, double>) return _mm_div_pd(v0, v1);
      if constexpr(std::is_same_v<T, float>)  return _mm_div_ps(v0, v1);
    }
    else
    {
      return map( eve::div, v0, v1);    
    }
    
  }

}

#endif
