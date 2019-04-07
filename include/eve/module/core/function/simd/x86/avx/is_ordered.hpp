//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_IS_ORDERED_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_IS_ORDERED_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/constant/true.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // avx
  template < typename T,  typename N>
  EVE_FORCEINLINE auto is_ordered_(EVE_SUPPORTS(avx_),
                                     wide<T, N, avx_> const &v0,
                                     wide<T, N, avx_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>)  return l_t(_mm256_cmp_ps(v0, v1, _CMP_ORD_Q));
    if constexpr(std::is_same_v<T, double>) return l_t(_mm256_cmp_pd(v0, v1, _CMP_ORD_Q));
    if constexpr(std::is_integral_v<T> || eve::is_logical_v<T>) return True<l_t>(); 
  }

  // -----------------------------------------------------------------------------------------------
  // sse_
  template < typename T,  typename N>
  EVE_FORCEINLINE auto is_ordered_(EVE_SUPPORTS(avx_),
                                     wide<T, N, sse_> const &v0,
                                     wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>)  return l_t(_mm_cmp_ps(v0, v1, _CMP_ORD_Q));
    if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmp_pd(v0, v1, _CMP_ORD_Q));
    if constexpr(std::is_integral_v<T> || eve::is_logical_v<T>) return True<l_t>(); 
  } 
}

#endif
