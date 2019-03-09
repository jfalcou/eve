//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SSE2_IFNOT_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SSE2_IFNOT_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/logical.hpp>
#include <eve/as_arithmetic.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // sse2 only
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE wide<logical<U>, N> ifnot_else_(EVE_SUPPORTS(sse2_)
                                           , wide<T, N, sse_> const &v0
                                           , wide<logical<U>, N, sse_> const &v1
                                           , wide<logical<U>, N, sse_> const &v2) noexcept
  {
    using u_t = wide<logical<U>, N>;
    using a_t = wide<eve::as_arithmetic_t<T>,N>;
    return bitwise_cast<u_t>(ifnot_else(bitwise_cast<a_t>(bitwise_mask(v0)), bitwise_cast<a_t>(v1), bitwise_cast<a_t>(v2)));    
  }
}

#endif
