//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_AVX2_IF_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_AVX2_IF_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/logical.hpp>
#include <eve/is_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // avx2
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE wide<U, N, avx_> if_else_(EVE_SUPPORTS(avx2_)
                                           , wide<T, N, avx_> const &v0
                                           , wide<U, N, avx_> const &v1
                                           , wide<U, N, avx_> const &v2) noexcept
  {
    using u_t = wide<U, N, avx_>;
    using a_t = wide<as_integer_t<T>,N>;

    if constexpr(std::is_same_v<U, float>)   return _mm256_blendv_ps(v2, v1, bitwise_cast<u_t>(bitwise_mask(v0)));
    if constexpr(std::is_same_v<U, double>)  return _mm256_blendv_pd(v2, v1, bitwise_cast<u_t>(bitwise_mask(v0)));   
    if constexpr(std::is_integral_v<U>)      return _mm256_blendv_epi8(v2, v1, bitwise_cast<u_t>(bitwise_mask(v0)));
    if constexpr(is_logical_v<U>) return bitwise_cast<u_t>(if_else(v0, bitwise_cast<a_t>(v1), bitwise_cast<a_t>(v2))); 
  }

}

#endif
