//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_AVX_COMBINE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_AVX_COMBINE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // All AVX types
  template<typename T, typename N>
  EVE_FORCEINLINE auto combine( avx_ const&
                              , pack<T,N,avx_> const& l, pack<T,N,avx_> const& h
                              ) noexcept
  {
    using that_t = pack<T,typename N::combined_type>;
    return that_t( typename that_t::storage_type{l,h} );
  }

  // -----------------------------------------------------------------------------------------------
  // All SSE types
  template<typename T,typename N>
  EVE_FORCEINLINE auto  combine ( avx_ const&
                                , pack<T,N,sse_> const& l, pack<T,N,sse_> const& h
                                ) noexcept
                        requires( pack<T,typename N::combined_type>, If<(N::value*sizeof(T)==16)>)
  {
    if constexpr( std::is_same_v<T,double> )
      return _mm256_insertf128_pd(_mm256_castpd128_pd256(l), h, 1);

    if constexpr( std::is_same_v<T,float> )
      return _mm256_insertf128_ps(_mm256_castps128_ps256(l), h, 1);

    if constexpr( std::is_integral_v<T> )
      return _mm256_insertf128_si256(_mm256_castsi128_si256(l), h, 1);
  }
} }

#endif
