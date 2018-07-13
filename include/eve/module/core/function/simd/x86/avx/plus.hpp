//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_PLUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_PLUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename N>
  EVE_FORCEINLINE pack<double,N,avx_> plus_ ( EVE_SUPPORTS(avx_)
                                            , pack<double,N,avx_> const& v0
                                            , pack<double,N,avx_> const& v1
                                            ) noexcept
  {
    return _mm256_add_pd(v0,v1);
  }

  // -----------------------------------------------------------------------------------------------
  // float
  template<typename N>
  EVE_FORCEINLINE pack<float,N,avx_> plus_( EVE_SUPPORTS(avx_)
                                          , pack<float,N,avx_> const& v0
                                          , pack<float,N,avx_> const& v1
                                          ) noexcept
  {
    return _mm256_add_ps(v0,v1);
  }

  // -----------------------------------------------------------------------------------------------
  // integers
  template< typename T, typename N
          , typename = std::enable_if_t<std::is_integral_v<T>>
          >
  EVE_FORCEINLINE pack<T,N,avx_> plus_( EVE_SUPPORTS(avx_)
                                      , pack<T,N,avx_> const& v0
                                      , pack<T,N,avx_> const& v1
                                      ) noexcept
  {
    using that_t = pack<T,N,avx_>;

    auto[l0,h0] = v0.slice();
    auto[l1,h1] = v1.slice();

    return that_t( l0+l1, h0+h1 );
  }
} }

#endif
