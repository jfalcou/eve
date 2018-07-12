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
  // double
  template< typename N
          , typename = std::enable_if_t<N::value==2>
          >
  EVE_FORCEINLINE auto combine( avx_ const&
                              , pack<double,N,sse_> const& l, pack<double,N,sse_> const& h
                              ) noexcept
  {
    using that_t = pack<double,typename N::combined_type>;
    that_t that = _mm256_castpd128_pd256(l);
    return _mm256_insertf128_pd(that, h, 1);
  }

  // -----------------------------------------------------------------------------------------------
  // float
  template< typename N
          , typename = std::enable_if_t<N::value==4>
          >
  EVE_FORCEINLINE auto combine( avx_ const&
                              , pack<float,N,sse_> const& l, pack<float,N,sse_> const& h
                              ) noexcept
  {
    using that_t = pack<float,typename N::combined_type>;
    that_t that = _mm256_castps128_ps256(l);
    return _mm256_insertf128_ps(that, h, 1);
  }

  // -----------------------------------------------------------------------------------------------
  // integers
  template< typename T,typename N
          , typename = std::enable_if_t<std::is_integral_v<T> && (N::value*sizeof(T)==16)>
          >
  EVE_FORCEINLINE auto combine( avx_ const&
                              , pack<T,N,sse_> const& l, pack<T,N,sse_> const& h
                              ) noexcept
  {
    using that_t = pack<T,typename N::combined_type>;
    that_t that = _mm256_castsi128_si256(l);
    return _mm256_insertf128_si256(that, h, 1);
  }
} }

#endif
