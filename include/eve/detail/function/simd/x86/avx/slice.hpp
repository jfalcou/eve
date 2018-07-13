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
#include <eve/forward.hpp>
#include <type_traits>
#include <cstddef>

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template< typename N, typename Slice
          , typename = std::enable_if_t<(N::value>1)>
          >
  EVE_FORCEINLINE auto slice( pack<double,N,avx_> const& a, Slice const& ) noexcept
  {
    return pack<double,typename N::split_type>(_mm256_extractf128_pd(a,Slice::value));
  }

  // -----------------------------------------------------------------------------------------------
  // float
  template< typename N, typename Slice
          , typename = std::enable_if_t<(N::value>1)>
          >
  EVE_FORCEINLINE auto slice( pack<float,N,avx_> const& a, Slice const& ) noexcept
  {
    return pack<float,typename N::split_type>(_mm256_extractf128_ps(a,Slice::value));
  }

  // -----------------------------------------------------------------------------------------------
  // integers
  template< typename T,typename N, typename Slice
          , typename = std::enable_if_t <   std::is_integral_v<T>
                                        &&  (N::value>1)
                                        >
          >
  EVE_FORCEINLINE auto slice( pack<T,N,avx_> const& a, Slice const& ) noexcept
  {
    return pack<T,typename N::split_type>(_mm256_extractf128_si256(a,Slice::value));
  }

  // -----------------------------------------------------------------------------------------------
  // Both slice
  template< typename T,typename N
          , typename = std::enable_if_t <(N::value>1)>
          >
  EVE_FORCEINLINE auto slice( pack<T,N,avx_> const& a ) noexcept
  {
    std::array<pack<T,typename N::split_type>,2> that{slice(a,lower_), slice(a,upper_)};
    return that;
  }
} }

#endif
