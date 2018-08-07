//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_STORE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename N>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(sse2_)
                              , pack<double,N,sse_> const& value, double* ptr
                              ) noexcept
  {
    if constexpr(N::value == 2) _mm_storeu_pd(ptr,value);
    else                        apply<1>( [&](auto... I) { ((*ptr++ = value[I]), ...); } );
  }

  template<typename N, std::size_t A>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(sse2_)
                              , pack<double,N,sse_> const& value, aligned_ptr<double,A> ptr
                              ) noexcept
  {
    static constexpr auto  alg = pack<double,N,sse_>::static_alignment;
    if constexpr(N::value == 2 && A >= alg) _mm_store_pd(ptr,value);
    else                                    store(value,ptr.get());
  }

  // -----------------------------------------------------------------------------------------------
  // float
  template<typename N>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(sse2_)
                              , pack<float,N,sse_> const& value, float* ptr
                              ) noexcept
  {
    if constexpr(N::value == 4) _mm_storeu_ps(ptr,value);
    else                        apply<N::value>( [&](auto... I) { ((*ptr++ = value[I]), ...); } );
  }

  template<typename N, std::size_t A>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(sse2_)
                              , pack<float,N,sse_> const& value, aligned_ptr<float,A> ptr
                              ) noexcept
  {
    static constexpr auto  alg = pack<float,N,sse_>::static_alignment;
    if constexpr(N::value == 4 && A >= alg) _mm_store_ps(ptr,value);
    else                                    store(value,ptr.get());
  }

  // -----------------------------------------------------------------------------------------------
  // integers
  template< typename T, typename N
          , typename = std::enable_if_t<std::is_integral_v<T>>
          >
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(sse2_)
                              , pack<T,N,sse_> const& value, T* ptr
                              ) noexcept
  {
    if constexpr(N::value*sizeof(T) == limits<sse2_>::bytes)
      _mm_storeu_si128((__m128i*)(ptr), value);
    else
      apply<N::value>( [&](auto... I) { ((*ptr++ = value[I]), ...); } );
  }

  template< typename T, typename N,std::size_t A
          , typename = std::enable_if_t<std::is_integral_v<T>>
          >
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(sse2_)
                              , pack<T,N,sse_> const& value, aligned_ptr<T,A> ptr
                              ) noexcept
  {
    static constexpr auto  alg = pack<T,N,sse_>::static_alignment;
    if constexpr(N::value*sizeof(T) == limits<sse2_>::bytes && A >= alg)
      _mm_store_si128((__m128i*)(ptr.get()), value);
    else
      store(value,ptr.get());
  }
} }

#endif
