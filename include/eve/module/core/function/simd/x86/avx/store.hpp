//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_STORE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename N>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(avx_)
                              , pack<double,N,avx_> const& value, double* ptr
                              ) noexcept
  {
    _mm256_storeu_pd(ptr,value);
  }

  template<typename N, std::size_t A>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(avx_)
                              , pack<double,N,avx_> const& value, aligned_ptr<double,A> ptr
                              ) noexcept
  {
    static constexpr auto   alg = pack<double,N,avx_>::static_alignment;
    if constexpr(A >= alg)  _mm256_store_pd(ptr,value);
    else                    store(value,ptr.get());
  }

  // -----------------------------------------------------------------------------------------------
  // float
  template<typename N>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(avx_)
                              , pack<float,N,avx_> const& value, float* ptr
                              ) noexcept
  {
    _mm256_storeu_ps(ptr,value);
  }

  template<typename N, std::size_t A>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(avx_)
                              , pack<float,N,avx_> const& value, aligned_ptr<float,A> ptr
                              ) noexcept
  {
    static constexpr auto   alg = pack<float,N,avx_>::static_alignment;
    if constexpr(A >= alg)  _mm256_store_ps(ptr,value);
    else                    store(value,ptr.get());
  }

  // -----------------------------------------------------------------------------------------------
  // integers
  template< typename T, typename N
          , typename = std::enable_if_t<std::is_integral_v<T>>
          >
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(avx_)
                              , pack<T,N,avx_> const& value, T* ptr
                              ) noexcept
  {
    _mm256_storeu_si256((__m256i*)(ptr), value);
  }

  template< typename T, typename N,std::size_t A
          , typename = std::enable_if_t<std::is_integral_v<T>>
          >
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(avx_)
                              , pack<T,N,avx_> const& value, aligned_ptr<T,A> ptr
                              ) noexcept
  {
    static constexpr auto   alg = pack<T,N,avx_>::static_alignment;
    if constexpr(A >= alg)  _mm256_store_si256((__m256i*)(ptr.get()), value);
    else                    store(value,ptr.get());
  }
} }

#endif
