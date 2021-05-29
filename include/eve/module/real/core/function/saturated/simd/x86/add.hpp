//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/concepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/saturated.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> add_(EVE_SUPPORTS(sse2_),
    saturated_type const &  st, wide<T, N> v0, wide<T, N> v1) noexcept
    requires x86_abi<abi_t<T, N>>
  {
         if constexpr ( std::floating_point<T>                                    ) return add(v0, v1);
    else if constexpr ( sizeof(T) > 2                                             ) return add_(EVE_RETARGET(cpu_), st, v0, v1);
    else if constexpr ( std::same_as<abi_t<T, N>, x86_256_> && current_api == avx ) return add_(EVE_RETARGET(cpu_), st, v0, v1);
    else if constexpr ( std::signed_integral<T> && sizeof(T) == 1 )
    {
           if constexpr ( std::same_as<abi_t<T, N>, x86_512_> ) return _mm512_adds_epi8(v0, v1);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_256_> ) return _mm256_adds_epi8(v0, v1);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_128_> ) return _mm_adds_epi8   (v0, v1);
    }
    else if constexpr ( std::signed_integral<T> && sizeof(T) == 2 )
    {
           if constexpr ( std::same_as<abi_t<T, N>, x86_512_> ) return _mm512_adds_epi16(v0, v1);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_256_> ) return _mm256_adds_epi16(v0, v1);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_128_> ) return _mm_adds_epi16   (v0, v1);
    }
    else if constexpr ( std::unsigned_integral<T> && sizeof(T) == 1 )
    {
           if constexpr ( std::same_as<abi_t<T, N>, x86_512_> ) return _mm512_adds_epu8(v0, v1);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_256_> ) return _mm256_adds_epu8(v0, v1);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_128_> ) return _mm_adds_epu8   (v0, v1);
    }
    else if constexpr ( std::unsigned_integral<T> && sizeof(T) == 2 )
    {
           if constexpr ( std::same_as<abi_t<T, N>, x86_512_> ) return _mm512_adds_epu16(v0, v1);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_256_> ) return _mm256_adds_epu16(v0, v1);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_128_> ) return _mm_adds_epu16   (v0, v1);
    }
  }
}
