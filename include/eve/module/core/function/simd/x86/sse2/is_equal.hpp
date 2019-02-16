//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SSE2_IS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SSE2_IS_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // float
  template < typename N > 
  EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(sse2_),
                                 wide<float, N, sse_> const &v0,
                                 wide<float, N, sse_> const &v1) noexcept
  {
    using t_t = wide<float, N, sse_>; 
    return as_logical_t<t_t>(_mm_cmpeq_ps(v0,v1));
  }
 
  // -----------------------------------------------------------------------------------------------
  // double
  template < typename N > 
  EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(sse2_),
                                 wide<double, N, sse_> const &v0,
                                 wide<double, N, sse_> const &v1) noexcept
  {
    using t_t = wide<double, N , sse_>; 
    return as_logical_t<t_t>(_mm_cmpeq_pd(v0,v1));
  }

    
  // -----------------------------------------------------------------------------------------------
  // integers
  template < typename T,  typename N> 
  EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(sse2_),
                                 wide<T, N, sse_> const &v0,
                                 wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N ,sse_>; 
    if constexpr(sizeof(T) == 1)
      return as_logical_t<t_t>(_mm_cmpeq_epi8(v0,v1));
    else if  constexpr(sizeof(T) == 2)
      return as_logical_t<t_t>(_mm_cmpeq_epi16(v0,v1));
    else if  constexpr(sizeof(T) == 4)
      return as_logical_t<t_t>(_mm_cmpeq_epi32(v0,v1));
    else if  constexpr(sizeof(T) == 8)
      return map(eve::is_equal, v0, v1); 
  }
 
}

#endif
