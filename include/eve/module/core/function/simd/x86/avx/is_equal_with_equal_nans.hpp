//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_AVX_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_AVX_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED

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
  // avx_
  template < typename T, typename N >
  EVE_FORCEINLINE auto is_equal_with_equal_nans_(EVE_SUPPORTS(avx_),
                                 wide<T, N, avx_> const &v0,
                                 wide<T, N, avx_> const &v1) noexcept
  {
    using t_t = wide<T, N, avx_>;
    using l_t = as_logical_t<t_t>;
    using a_t = wide<as_integer_t<T>,N>;
    std::cout << "avx avx" << std::endl; 
    if constexpr(std::is_same_v<T, float> ) return l_t(_mm256_cmp_ps(v0, v1, _CMP_EQ_UQ));
    if constexpr(std::is_same_v<T, double>) return l_t(_mm256_cmp_pd(v0, v1, _CMP_EQ_UQ));
    if constexpr(std::is_integral_v<T>)     return aggregate(eve::is_equal_with_equal_nans, v0, v1);
    if constexpr(is_logical_v<T>)
      return bitwise_cast<l_t>(is_equal_with_equal_nans(bitwise_cast<a_t>(v0), bitwise_cast<a_t>(v1)));
  }

  // -----------------------------------------------------------------------------------------------
  // sse_
  template < typename T,  typename N >
  EVE_FORCEINLINE auto is_equal_with_equal_nans_(EVE_SUPPORTS(avx_),
                                 wide<T, N, sse_> const &v0,
                                 wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    using l_t = as_logical_t<t_t>;
    using a_t = wide<as_integer_t<T>,N>;
    std::cout << "avx sse" << std::endl; 

    if constexpr(std::is_same_v<T, float> ) return l_t(_mm_cmp_ps(v0, v1, _CMP_EQ_UQ));
    if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmp_pd(v0, v1, _CMP_EQ_UQ));
    if constexpr( std::is_integral_v<T>   ) return is_equal_with_equal_nans_(EVE_RETARGET(sse4_1_),v0,v1);
    if constexpr(is_logical_v<T>)
      return bitwise_cast<l_t>(is_equal_with_equal_nans(bitwise_cast<a_t>(v0), bitwise_cast<a_t>(v1)));
  }
}

#endif
