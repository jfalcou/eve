//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_AVX_SLICE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_AVX_SLICE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template< typename N
          , typename = std::enable_if_t<(N::value>1)>
          >
  EVE_FORCEINLINE auto slice( pack<double,N,avx_> const& a ) noexcept
  {
    std::array<pack<double,typename N::split_type>,2> that{ _mm256_extractf128_pd(a,0)
                                                          , _mm256_extractf128_pd(a,1)
                                                          };
    return that;
  }

  // -----------------------------------------------------------------------------------------------
  // float
  template< typename N
          , typename = std::enable_if_t<(N::value>1)>
          >
  EVE_FORCEINLINE auto slice( pack<float,N,avx_> const& a ) noexcept
  {
    std::array<pack<float,typename N::split_type>,2> that { _mm256_extractf128_ps(a,0)
                                                          , _mm256_extractf128_ps(a,1)
                                                          };
    return that;
  }

  // -----------------------------------------------------------------------------------------------
  // integers
  template< typename T,typename N
          , typename = std::enable_if_t <   std::is_integral_v<T>
                                        &&  (N::value>1)
                                        >
          >
  EVE_FORCEINLINE auto slice( pack<T,N,avx_> const& a ) noexcept
  {
    std::array<pack<T,typename N::split_type>,2> that { _mm256_extractf128_si256(a,0)
                                                      , _mm256_extractf128_si256(a,1)
                                                      };
    return that;
  }
} }

#endif
