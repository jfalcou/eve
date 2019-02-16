//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SSE4_1_IS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SSE4_1_IS_EQUAL_HPP_INCLUDED

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
  // integers 64 bits
  template < typename N> 
  EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(sse2_),
                                 wide<std::int64_t, N, sse_> const &v0,
                                 wide<std::int64_t, N, sse_> const &v1) noexcept
  {
    using t_t = wide<std::int64_t, N ,sse_>; 
    return as_logical_t<t_t>(_mm_cmpeq_epi64(v0,v1));
  }
  
  template < typename N> 
  EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(sse2_),
                                 wide<std::uint64_t, N, sse_> const &v0,
                                 wide<std::uint64_t, N, sse_> const &v1) noexcept
  {
    using t_t = wide<std::uint64_t, N ,sse_>; 
    return as_logical_t<t_t>(_mm_cmpeq_epi64(v0,v1));
  }
 
}

#endif
