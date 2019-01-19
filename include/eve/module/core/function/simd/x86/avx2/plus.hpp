//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_PLUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_PLUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template< typename T, typename N
          , typename = std::enable_if_t<std::is_integral_v<T>>
          >
  EVE_FORCEINLINE wide<T,N,avx_> plus_( EVE_SUPPORTS(avx2_)
                                      , wide<T,N,avx_> const& v0
                                      , wide<T,N,avx_> const& v1
                                      ) noexcept
  {
    if constexpr(sizeof(T) == 1)
      return _mm256_add_epi8(v0,v1);
    else if constexpr(sizeof(T) == 2)
      return _mm256_add_epi16(v0,v1);
    else if constexpr(sizeof(T) == 4)
      return _mm256_add_epi32(v0,v1);
    else
      return _mm256_add_epi64(v0,v1);
  }
}

#endif
