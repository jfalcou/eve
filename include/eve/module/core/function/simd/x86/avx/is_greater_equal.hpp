//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_AVX_IS_GREATER_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_AVX_IS_GREATER_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/function/is_less.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // avx
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_greater_equal_(EVE_SUPPORTS(avx_), wide<T, N, sse_> const &v0, wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>)
        return as_logical_t<t_t>(_mm_cmp_ps(v0, v1, _CMP_GE_OQ));
      if constexpr(std::is_same_v<T, double>)
        return as_logical_t<t_t>(_mm_cmp_pd(v0, v1, _CMP_GE_OQ));
    }
    else
    {
      return logical_not(is_less(v0, v1)); 
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_greater_equal_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &v0, wide<T, N, avx_> const &v1) noexcept
  {
    using t_t = wide<T, N, avx_>;
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>)
        return as_logical_t<t_t>(_mm256_cmp_ps(v0, v1, _CMP_GE_OQ));
      if constexpr(std::is_same_v<T, double>)
        return as_logical_t<t_t>(_mm256_cmp_pd(v0, v1, _CMP_GE_OQ));
    }
    else
    {
      return  logical_not(is_less(v0, v1)); 
    }
  }
}

#endif
