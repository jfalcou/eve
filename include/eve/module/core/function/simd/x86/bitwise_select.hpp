//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_BITWISE_SELECT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_BITWISE_SELECT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename U, typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> bitwise_select_(EVE_SUPPORTS(avx_),
                                                   wide<U, N, sse_> const &v0,
                                                   wide<T, N, sse_> const &v1,
                                                   wide<T, N, sse_> const &v2) noexcept
  {
    if constexpr(supports_xop)
    {
      if constexpr(std::is_floating_point_v<T>)
      {
        using itype = wide<as_integer_t<T, unsigned>, N, sse_>;
        using utype = wide<as_integer_t<U, unsigned>, N, sse_>;
        itype tmp =
          _mm_cmov_si128(bitwise_cast<itype>(v1), bitwise_cast<itype>(v2), bitwise_cast<utype>(v0));
        return bitwise_cast<wide<T, N, sse_>>(tmp);
      }
      else
      {
        return _mm_cmov_si128(v1, v2, v0);
      }
    }
    else return bitwise_select_(EVE_RETARGET(simd_), v0, v1, v2);
  }

#if defined(EVE_COMP_IS_MSVC)
  template<typename U, typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> bitwise_select_(EVE_SUPPORTS(avx_),
                                                   wide<U, N, avx_> const &v0,
                                                   wide<T, N, avx_> const &v1,
                                                   wide<T, N, avx_> const &v2) noexcept
  {
    if constexpr(supports_xop)
    {
      if constexpr(std::is_floating_point_v<T>)
      {
        using itype = wide<as_integer_t<T, unsigned>, N, avx_>;
        using utype = wide<as_integer_t<U, unsigned>, N, avx_>;
        itype tmp   = _mm256_cmov_si256(
          bitwise_cast<itype>(v1), bitwise_cast<itype>(v2), bitwise_cast<utype>(v0));
        return bitwise_cast<wide<T, N, avx_>>(tmp);
      }
      else
      {
        return _mm256_cmov_si256(v1, v2, v0);
      }
    }
    else return bitwise_select_(EVE_RETARGET(simd_), v0, v1, v2);
  }
#endif
}

#endif
