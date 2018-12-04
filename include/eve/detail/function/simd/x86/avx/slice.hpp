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
  // Single slice
  template<typename N, typename Slice>
  EVE_FORCEINLINE auto  slice( pack<double,N,avx_> const& a, Slice const& ) noexcept
                        requires( pack<double,typename N::split_type>, If<(N::value>1)> )
  {
    using pack_t = pack<double,typename N::split_type>;
    return pack_t(_mm256_extractf128_pd(a,Slice::value));
  }

  template<typename N, typename Slice>
  EVE_FORCEINLINE auto  slice( pack<float,N,avx_> const& a, Slice const& ) noexcept
                        requires( pack<float,typename N::split_type>, If<(N::value>1)> )
  {
    using pack_t = pack<float,typename N::split_type>;
    return pack_t(_mm256_extractf128_ps(a,Slice::value));
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto  slice( pack<T,N,avx_> const& a, Slice const& ) noexcept
                        requires( pack<T,typename N::split_type>
                                , If<(N::value>1)>
                                , Integral<T>
                                )
  {
    using pack_t = pack<T,typename N::split_type>;
    return pack_t(_mm256_extractf128_si256(a,Slice::value));
  }

  // -----------------------------------------------------------------------------------------------
  // Both slice
  template<typename T,typename N>
  EVE_FORCEINLINE auto slice( pack<T,N,avx_> const& a ) noexcept
                        requires( std::array<pack<T,typename N::split_type>,2>, If<(N::value>1)> )
  {
    std::array<pack<T,typename N::split_type>,2> that{slice(a,lower_), slice(a,upper_)};
    return that;
  }
} }

#endif
