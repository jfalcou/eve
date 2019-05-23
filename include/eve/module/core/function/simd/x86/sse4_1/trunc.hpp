//==================================================================================================
/**
  EVE - Expressive Vector Engine 
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_1_TRUNC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_1_TRUNC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/function/add.hpp>
#include <eve/function/shr.hpp>
#include <type_traits>
 
namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N>
  EVE_FORCEINLINE auto trunc_(EVE_SUPPORTS(sse4_1_),
                            wide<T, N, sse_> const &a0) noexcept
  requires(wide<T, N, sse_>, Arithmetic<T>)
  {
    using t_t =  wide<T, N, sse_>; 
    if constexpr(std::is_integral_v<T>)
    {
       return a0; 
    }
    else
    {
      if constexpr(std::is_same_v<T, double>) return _mm_round_pd(a0,  _MM_FROUND_TO_ZERO);
      if constexpr(std::is_same_v<T, float>)  return _mm_round_ps(a0,  _MM_FROUND_TO_ZERO);
    }
  }
}

#endif
