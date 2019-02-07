//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_XOP_BITWISE_SELECT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_XOP_BITWISE_SELECT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/scalar/bitwise_cast.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> bitwise_select_(EVE_SUPPORTS(xop_),
                                                   wide<T, N, sse_> const &v0,
                                                   wide<T, N, sse_> const &v1,
                                                   wide<T, N, sse_> const &v2) noexcept
  {
    if constexpr(!std::is_integral_v<T>)
    {
      using itype = as_integer_t<wide<T, N, sse_>, unsigned>;
      itype tmp =
          _mm_cmov_si128(bitwise_cast<itype>(v1), bitwise_cast<itype>(v2), bitwise_cast<itype>(v0));
      return bitwise_cast<wide<T, N, sse_>>(tmp);
    }
    else
    {
      return _mm_cmov_si128(v1, v2, v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> bitwise_select_(EVE_SUPPORTS(xop_),
                                                   wide<T, N, avx_> const &v0,
                                                   wide<T, N, avx_> const &v1,
                                                   wide<T, N, avx_> const &v2) noexcept
  {
    if constexpr(!std::is_integral_v<T>)
    {
      using itype = as_integer_t<wide<T, N, avx_>, unsigned>;
      itype tmp   = _mm256_cmov_si256(
          bitwise_cast<itype>(v1), bitwise_cast<itype>(v2), bitwise_cast<itype>(v0));
      return bitwise_cast<wide<T, N, avx_>>(tmp);
    }
    else
    {
      return _mm256_cmov_si256(v1, v2, v0);
    }
  }

}

#endif
