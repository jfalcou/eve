//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SSE2_IS_NOT_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SSE2_IS_NOT_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // float
  template < typename N >
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(sse2_),
                                 wide<float, N, sse_> const &v0,
                                 wide<float, N, sse_> const &v1) noexcept
  {
    using t_t = wide<float, N, sse_>;
    return as_logical_t<t_t>(_mm_cmpneq_ps(v0,v1));
  }

  // -----------------------------------------------------------------------------------------------
  // double
  template < typename N >
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(sse2_),
                                 wide<double, N, sse_> const &v0,
                                 wide<double, N, sse_> const &v1) noexcept
  {
    using t_t = wide<double, N , sse_>;
    return as_logical_t<t_t>(_mm_cmpneq_pd(v0,v1));
  }
}

#endif
