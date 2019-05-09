//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_STORE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(avx_),
                              wide<T, N, avx_> const &value,
                              T *                     ptr) noexcept requires(void, Arithmetic<T>)
  {
    if constexpr(N::value * sizeof(T) == limits<avx_>::bytes)
    {
      if constexpr(std::is_same_v<T, double>) _mm256_storeu_pd(ptr, value);
      if constexpr(std::is_same_v<T, float>) _mm256_storeu_ps(ptr, value);
      if constexpr(std::is_integral_v<T>) _mm256_storeu_si256((__m256i *)(ptr), value);
    }
    else
    {
      apply<N::value>([&](auto... I) { ((*ptr++ = value[ I ]), ...); });
    }
  }

  template<typename T, typename N, std::size_t A>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(avx_),
                              wide<T, N, avx_> const &value,
                              aligned_ptr<T, A>       ptr) noexcept requires(void, Arithmetic<T>)
  {
    static constexpr auto alg = wide<T, N, avx_>::static_alignment;

    if constexpr(N::value * sizeof(T) == limits<avx_>::bytes && A >= alg)
    {
      if constexpr(std::is_same_v<T, double>) _mm256_store_pd(ptr.get(), value);
      if constexpr(std::is_same_v<T, float>) _mm256_store_ps(ptr.get(), value);
      if constexpr(std::is_integral_v<T>) _mm256_store_si256((__m256i *)(ptr.get()), value);
    }
    else
    {
      store(value, ptr.get());
    }
  }
}

#endif
