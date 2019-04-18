//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_IS_LESS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_IS_LESS_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_less_equal_ ( EVE_SUPPORTS(sse2_),
                                        wide<T, N, sse_> const &v0, wide<T, N, sse_> const &v1
                                      ) noexcept
  {
    using t_t = wide<T, N, sse_>;
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float> ) return as_logical_t<t_t>(_mm_cmple_ps(v0, v1));
      if constexpr(std::is_same_v<T, double>) return as_logical_t<t_t>(_mm_cmple_pd(v0, v1));
    }
    else
    {
      return logical_not(is_greater(v0, v1));
    }
  }
}

#endif
