//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/convert.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>
                  div_(EVE_SUPPORTS(sse2_), wide<T, N, sse_> const &v0, wide<T, N, sse_> const &v1) noexcept
  {
    if constexpr(std::is_same_v<T, double>)
      return _mm_div_pd(v0, v1);
    else if constexpr(std::is_same_v<T, float>)
      return _mm_div_ps(v0, v1);
    else if constexpr(std::is_integral_v<T>)
    {
      if constexpr(sizeof(T) < 4)
      {
        return convert(div(convert(v0, as<float>()), convert(v1, as<float>())), as<T>());
      }
      else if constexpr(sizeof(T) ==  4)
      {
        return convert(div(convert(v0, as<double>()), convert(v1, as<double>())), as<T>());
      }
       else
        return map(div, v0, v1);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_>
                  div_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &v0, wide<T, N, avx_> const &v1) noexcept
  {
    if constexpr(std::is_same_v<T, float>)
      return _mm256_div_ps(v0, v1);
    else if constexpr(std::is_same_v<T, double>)
      return _mm256_div_pd(v0, v1);
    else if constexpr(std::is_integral_v<T>)
      return aggregate(eve::div, v0, v1);
  }
}

#endif
