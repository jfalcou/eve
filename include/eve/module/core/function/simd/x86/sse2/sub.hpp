//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_SUB_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_SUB_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename N>
  EVE_FORCEINLINE wide<double,N,sse_> sub_( EVE_SUPPORTS(sse2_)
                                          , wide<double,N,sse_> const& v0
                                          , wide<double,N,sse_> const& v1
                                          ) noexcept
  {
    return _mm_sub_pd(v0,v1);
  }

  // -----------------------------------------------------------------------------------------------
  // float
  template<typename N>
  EVE_FORCEINLINE wide<float,N,sse_> sub_ ( EVE_SUPPORTS(sse2_)
                                          , wide<float,N,sse_> const& v0
                                          , wide<float,N,sse_> const& v1
                                          ) noexcept
  {
    return _mm_sub_ps(v0,v1);
  }

  template< typename T, typename N
          , typename = std::enable_if_t<std::is_integral_v<T>>
          >
  EVE_FORCEINLINE wide<T,N,sse_> sub_ ( EVE_SUPPORTS(sse2_)
                                      , wide<T,N,sse_> const& v0
                                      , wide<T,N,sse_> const& v1
                                      ) noexcept
  {
    if constexpr(sizeof(T) == 1)
      return _mm_sub_epi8(v0,v1);
    else if constexpr(sizeof(T) == 2)
      return _mm_sub_epi16(v0,v1);
    else if constexpr(sizeof(T) == 4)
      return _mm_sub_epi32(v0,v1);
    else
      return _mm_sub_epi64(v0,v1);
  }
}

#endif
