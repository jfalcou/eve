//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_RSHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_RSHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/function/abs.hpp>

namespace eve::detail
{
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE auto
  rshr_(EVE_SUPPORTS(avx_),
        wide<T, N, sse_> const &a0,
        wide<I, N, sse_> const &a1) noexcept requires(wide<T, N, sse_>, integral<T>, integral<I>)
  {
    if constexpr(supports_xop)
    {
      using si_t = wide<as_integer_t<I, signed>, N, sse_>;
      auto sa1   = -bit_cast(a1, as_<si_t>{});
      if(std::is_signed_v<I>)
      {
        if constexpr(sizeof(T) == 1)
        {
          return _mm_sha_epi8(a0, sa1);
        }
        else if constexpr(sizeof(T) == 2)
        {
          return _mm_sha_epi16(a0, sa1);
        }
        else if constexpr(sizeof(T) == 4)
        {
          return _mm_sha_epi32(a0, sa1);
        }
        else if constexpr(sizeof(T) == 8)
        {
          return _mm_sha_epi64(a0, sa1);
        }
      }
      else
      {
        auto sa1 = -a1;
        if constexpr(sizeof(T) == 1)
        {
          return _mm_shl_epi8(a0, sa1);
        }
        else if constexpr(sizeof(T) == 2)
        {
          return _mm_shl_epi16(a0, sa1);
        }
        else if constexpr(sizeof(T) == 4)
        {
          return _mm_shl_epi32(a0, sa1);
        }
        else if constexpr(sizeof(T) == 8)
        {
          return _mm_shl_epi64(a0, sa1);
        }
      }
    }
    else
    {
      return map(eve::rshr, a0, a1);
    }
  }
}

#endif
