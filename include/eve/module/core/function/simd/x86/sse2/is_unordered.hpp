//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SSE2_IS_UNORDERED_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SSE2_IS_UNORDERED_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // sse2
  template < typename T,  typename N>
  EVE_FORCEINLINE auto is_unordered_(EVE_SUPPORTS(sse2_),
                                     wide<T, N, sse_> const &v0,
                                     wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>)  return l_t(_mm_cmpunord_ps(v0, v1));
    if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmpunord_pd(v0, v1));
    if constexpr(std::is_integral_v<T> || eve::is_logical_v<T>) return False<l_t>(); 
  }
}

#endif
