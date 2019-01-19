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

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Single slice
  template<typename N, typename Slice>
  EVE_FORCEINLINE auto  slice( wide<double,N,avx_> const& a, Slice const& ) noexcept
                        requires( wide<double,typename N::split_type>, If<(N::value>1)> )
  {
    using wide_t = wide<double,typename N::split_type>;
    return wide_t(_mm256_extractf128_pd(a,Slice::value));
  }

  template<typename N, typename Slice>
  EVE_FORCEINLINE auto  slice( wide<float,N,avx_> const& a, Slice const& ) noexcept
                        requires( wide<float,typename N::split_type>, If<(N::value>1)> )
  {
    using wide_t = wide<float,typename N::split_type>;
    return wide_t(_mm256_extractf128_ps(a,Slice::value));
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto  slice( wide<T,N,avx_> const& a, Slice const& ) noexcept
                        requires( wide<T,typename N::split_type>
                                , If<(N::value>1)>
                                , Integral<T>
                                )
  {
    using wide_t = wide<T,typename N::split_type>;
    return wide_t(_mm256_extractf128_si256(a,Slice::value));
  }

  // -----------------------------------------------------------------------------------------------
  // Both slice
  template<typename T,typename N>
  EVE_FORCEINLINE auto slice( wide<T,N,avx_> const& a ) noexcept
                        requires( std::array<wide<T,typename N::split_type>,2>, If<(N::value>1)> )
  {
    std::array<wide<T,typename N::split_type>,2> that{slice(a,lower_), slice(a,upper_)};
    return that;
  }
}

#endif
