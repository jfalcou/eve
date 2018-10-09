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
  template<typename T, typename N>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(sse2_)
                              , pack<T,N,sse_> const& value, T* ptr
                              , typename std::enable_if_t<std::is_arithmetic_v<T>>* = 0
                              ) noexcept
  {
    if constexpr(N::value*sizeof(T) == limits<sse2_>::bytes)
    {
      if constexpr( std::is_same_v<T,double>  ) _mm_storeu_pd(ptr,value);
      if constexpr( std::is_same_v<T,float>   ) _mm_storeu_ps(ptr,value);
      if constexpr( std::is_integral_v<T>     ) _mm_storeu_si128((__m128i*)(ptr), value);
    }
    else
    {
      apply<N::value>( [&](auto... I) { ((*ptr++ = value[I]), ...); } );
    }
  }

  template<typename T, typename N, std::size_t A>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(sse2_)
                              , pack<T,N,sse_> const& value
                              , aligned_ptr<T,A> ptr
                              , typename std::enable_if_t<std::is_arithmetic_v<T>>* = 0
                              ) noexcept
  {
    static constexpr auto  alg = pack<T,N,sse_>::static_alignment;

    if constexpr(N::value*sizeof(T) == limits<sse2_>::bytes && A >= alg)
    {
      if constexpr( std::is_same_v<T,double>  ) _mm_store_pd(ptr.get(),value);
      if constexpr( std::is_same_v<T,float>   ) _mm_store_ps(ptr.get(),value);
      if constexpr( std::is_integral_v<T>     ) _mm_store_si128((__m128i*)(ptr.get()), value);
    }
    else
    {
      store(value,ptr.get());
    }
  }
} }

#endif
