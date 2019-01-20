//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_BITWISE_OR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_BITWISE_OR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve { namespace detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T,N,sse_> bitwise_or_ ( EVE_SUPPORTS(sse2_)
                                              , wide<T,N,sse_> const& v0
                                              , wide<T,N,sse_> const& v1
                                              ) noexcept
  {
    if constexpr( std::is_same_v<T,float>   ) return _mm_or_ps(v0,v1);
    if constexpr( std::is_same_v<T,double>  ) return _mm_or_pd(v0,v1);
    if constexpr( std::is_integral_v<T>     ) return _mm_or_si128(v0,v1);
  }
} }

#endif
