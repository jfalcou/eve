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

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(sse2_), wide<T, N, x86_128_> const &value, T *ptr) noexcept
  {
    if constexpr(N::value * sizeof(T) == x86_128_::bytes)
    {
      if constexpr(std::is_same_v<T, double>)
        _mm_storeu_pd(ptr, value);
      else if constexpr(std::is_same_v<T, float>)
        _mm_storeu_ps(ptr, value);
      else if constexpr(std::is_integral_v<T>)
        _mm_storeu_si128((__m128i *)(ptr), value);
    }
    else
    {
      apply<N::value>([&](auto... I) { ((*ptr++ = value[ I ]), ...); });
    }
  }

  template<typename T, typename N, std::size_t A>
  EVE_FORCEINLINE auto
  store_(EVE_SUPPORTS(sse2_), wide<T, N, x86_128_> const &value, aligned_ptr<T, A> ptr) noexcept
  {
    static constexpr auto alg = wide<T, N, x86_128_>::static_alignment;

    if constexpr(N::value * sizeof(T) == x86_128_::bytes && A >= alg)
    {
      if constexpr(std::is_same_v<T, double>)
        _mm_store_pd(ptr.get(), value);
      else if constexpr(std::is_same_v<T, float>)
        _mm_store_ps(ptr.get(), value);
      else if constexpr(std::is_integral_v<T>)
        _mm_store_si128((__m128i *)(ptr.get()), value);
    }
    else
    {
      store(value, ptr.get());
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(avx_), wide<T, N, x86_256_> const &value, T *ptr) noexcept
  {
    if constexpr(N::value * sizeof(T) == x86_256_::bytes)
    {
      if constexpr(std::is_same_v<T, double>)
        _mm256_storeu_pd(ptr, value);
      else if constexpr(std::is_same_v<T, float>)
        _mm256_storeu_ps(ptr, value);
      else if constexpr(std::is_integral_v<T>)
        _mm256_storeu_si256((__m256i *)(ptr), value);
    }
    else
    {
      apply<N::value>([&](auto... I) { ((*ptr++ = value[ I ]), ...); });
    }
  }

  template<typename T, typename N, std::size_t A>
  EVE_FORCEINLINE auto
  store_(EVE_SUPPORTS(avx_), wide<T, N, x86_256_> const &value, aligned_ptr<T, A> ptr) noexcept
  {
    static constexpr auto alg = wide<T, N, x86_256_>::static_alignment;

    if constexpr(N::value * sizeof(T) == x86_256_::bytes && A >= alg)
    {
      if constexpr(std::is_same_v<T, double>)
        _mm256_store_pd(ptr.get(), value);
      else if constexpr(std::is_same_v<T, float>)
        _mm256_store_ps(ptr.get(), value);
      else if constexpr(std::is_integral_v<T>)
        _mm256_store_si256((__m256i *)(ptr.get()), value);
    }
    else
    {
      store(value, ptr.get());
    }
  }

}
