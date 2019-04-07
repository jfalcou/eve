//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_2_IS_LESS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_2_IS_LESS_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/logical_not.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // sse2
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_greater_equal_(EVE_SUPPORTS(sse4_2_), wide<T, N, sse_> const &v0, wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>) return as_logical_t<t_t>(_mm_cmple_ps(v0, v1));
      if constexpr(std::is_same_v<T, double>) return as_logical_t<t_t>(_mm_cmple_pd(v0, v1));
    }
    else
    {
      if constexpr( sizeof(T) == 8)
      {
        t_t that = _mm_cmpgt_epi64(v0, v1);
        return logical_not(that);
      }
      else
        return logical_not(is_less(v0, v1)); 
    }     
  }
}

#endif
