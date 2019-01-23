//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_SUB_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_SUB_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename N>
  EVE_FORCEINLINE wide<double,N,avx_> sub_( EVE_SUPPORTS(avx_)
                                          , wide<double,N,avx_> const& v0
                                          , wide<double,N,avx_> const& v1
                                          ) noexcept
  {
    return _mm256_sub_pd(v0,v1);
  }

  // -----------------------------------------------------------------------------------------------
  // float
  template<typename N>
  EVE_FORCEINLINE wide<float,N,avx_> sub_ ( EVE_SUPPORTS(avx_)
                                          , wide<float,N,avx_> const& v0
                                          , wide<float,N,avx_> const& v1
                                          ) noexcept
  {
    return _mm256_sub_ps(v0,v1);
  }

  // -----------------------------------------------------------------------------------------------
  // integers
  template< typename T, typename N
          , typename = std::enable_if_t<std::is_integral_v<T>>
          >
  EVE_FORCEINLINE auto  sub_( EVE_SUPPORTS(avx_)
                            , wide<T,N,avx_> const& v0, wide<T,N,avx_> const& v1
                            ) noexcept
  {
    return aggregate( eve::sub, v0, v1 );
  }
}

#endif
