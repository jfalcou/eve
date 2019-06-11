//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SIMD_X86_AVX2_SQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SIMD_X86_AVX2_SQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> sqrt_( EVE_SUPPORTS(avx2_),
                                        wide<T, N, avx_> const & a0
                                      ) noexcept
  {
    if constexpr( std::is_same_v<T, float>)
      return _mm256_sqrt_ps(a0);
    else if constexpr( std::is_same_v<T, double>)
      return  _mm256_sqrt_pd(a0);
    else
      return map(eve::sqrt, a0); 
  }
}

#endif
