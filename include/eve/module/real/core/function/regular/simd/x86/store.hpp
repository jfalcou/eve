//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/memory.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template< scalar_value T, typename N, x86_abi ABI
          , simd_compatible_ptr<wide<T, N, ABI>> Ptr
          >
  EVE_FORCEINLINE void store_(EVE_SUPPORTS(sse2_), wide<T, N, ABI> const &value, Ptr ptr) noexcept
  {
    if constexpr( !std::is_pointer_v<Ptr> )
    {
      if constexpr(N::value * sizeof(T) == x86_512_::bytes)
      {
              if constexpr(std::is_same_v<T, double>) _mm512_store_pd(ptr.get(), value);
        else  if constexpr(std::is_same_v<T, float> ) _mm512_store_ps(ptr.get(), value);
        else  if constexpr(std::is_integral_v<T>    ) _mm512_store_si512((__m512i *)(ptr.get()), value);
      }
      else if constexpr(N::value * sizeof(T) == x86_256_::bytes)
      {
              if constexpr(std::is_same_v<T, double>) _mm256_store_pd(ptr.get(), value);
        else  if constexpr(std::is_same_v<T, float> ) _mm256_store_ps(ptr.get(), value);
        else  if constexpr(std::is_integral_v<T>    ) _mm256_store_si256((__m256i *)(ptr.get()), value);
      }
      else if constexpr(N::value * sizeof(T) == x86_128_::bytes)
      {
              if constexpr(std::is_same_v<T, double>) _mm_store_pd(ptr.get(), value);
        else  if constexpr(std::is_same_v<T, float> ) _mm_store_ps(ptr.get(), value);
        else  if constexpr(std::is_integral_v<T>    ) _mm_store_si128((__m128i *)(ptr.get()), value);
      }
      else
      {
        memcpy(ptr.get(), (T const*)(&value), N::value * sizeof(T));
      }
    }
    else  if constexpr(N::value * sizeof(T) == x86_512_::bytes)
    {
            if constexpr(std::is_same_v<T, double>) _mm512_storeu_pd(ptr, value);
      else  if constexpr(std::is_same_v<T, float> ) _mm512_storeu_ps(ptr, value);
      else  if constexpr(std::is_integral_v<T>    ) _mm512_storeu_si512((__m512i *)(ptr), value);
    }
    else if constexpr(N::value * sizeof(T) == x86_256_::bytes)
    {
            if constexpr(std::is_same_v<T, double>) _mm256_storeu_pd(ptr, value);
      else  if constexpr(std::is_same_v<T, float> ) _mm256_storeu_ps(ptr, value);
      else  if constexpr(std::is_integral_v<T>    ) _mm256_storeu_si256((__m256i *)(ptr), value);
    }
    else if constexpr(N::value * sizeof(T) == x86_128_::bytes)
    {
            if constexpr(std::is_same_v<T, double>) _mm_storeu_pd(ptr, value);
      else  if constexpr(std::is_same_v<T, float> ) _mm_storeu_ps(ptr, value);
      else  if constexpr(std::is_integral_v<T>    ) _mm_storeu_si128((__m128i *)(ptr), value);
    }
    else
    {
      memcpy(ptr, (T const*)(&value), N::value * sizeof(T));
    }
  }

  template< scalar_value T, typename N, x86_abi ABI
          , simd_compatible_ptr<logical<wide<T, N, ABI>>> Ptr
          >
  EVE_FORCEINLINE void store_(EVE_SUPPORTS(sse2_), logical<wide<T,N,ABI>> const &value, Ptr ptr) noexcept
  {
    if constexpr( !ABI::is_wide_logical )
    {
      auto[l,h] = value.mask().slice();

      if constexpr( !std::is_pointer_v<Ptr> )
      {
        store(l, aligned_ptr<T,Ptr::alignment()/2>((T*)ptr.get())             );
        store(h, aligned_ptr<T,Ptr::alignment()/2>((T*)(ptr.get()+N::value/2)));
      }
      else
      {
        store(l, (T*)ptr);
        store(h, (T*)(ptr+N::value/2));
      }
    }
    else
    {
      store_(EVE_RETARGET(cpu_), value, ptr) ;
    }
  }
}
