//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_XOP_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_XOP_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/architecture.hpp>
#include <eve/forward.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/detail/assert_utils.hpp>

#include <type_traits>
#include <cassert>

#if defined(EVE_SUPPORTS_XOP)
namespace eve ::detail
{
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE wide<T, N, sse_> shr_(EVE_SUPPORTS(xop_)
                                       , wide<T, N, sse_> const &a0
                                       , I const &a1) noexcept
  {
    using t_t = wide<T, N, sse_>; 
    assert(assert_good_shift<t_t>(a1) && "shl xop: a shift is out of range");
    if constexpr(std::is_floating_point_v<T>)
    {
      using i_t = wide<detail::as_integer_t<T>, N, sse_>;
      return bitwise_cast<t_t>(shr(bitwise_cast<i_t>(a0), a1));
    }
    if constexpr(std::is_integral_v<I>)
    {
      return map(eve::shr, a0, a1);
    }     
    else
    {
      if constexpr(std::is_unsigned_v<T>)
      {
        if constexpr(sizeof(T) == 1)
        {
          _mm_shl_epi8(a0,-a1);   
        }
        else if constexpr(sizeof(T) == 2)
        {
          _mm_shl_epi16(a0,-a1);   
        }
        else if constexpr(sizeof(T) == 4)
        {
          _mm_shl_epi32(a0,-a1);   
        }
        else if constexpr(sizeof(T) == 8)
        {
          _mm_shl_epi64(a0,-a1);   
        }
      }
      else
      {
        if constexpr(sizeof(T) == 1)
        {
          _mm_sha_epi8(a0,-a1);   
        }
        else if constexpr(sizeof(T) == 2)
        {
          _mm_sha_epi16(a0,-a1);   
        }
        else if constexpr(sizeof(T) == 4)
        {
          _mm_sha_epi32(a0,-a1);   
        }
        else if constexpr(sizeof(T) == 8)
        {
          _mm_sha_epi64(a0,-a1);   
        }
      }
    }
  }

}

#endif
#endif
