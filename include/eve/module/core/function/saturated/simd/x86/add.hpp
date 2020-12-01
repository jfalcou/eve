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

#include <eve/detail/concepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/saturated.hpp>

namespace eve::detail
{
  //================================================================================================
  // 128 bits saturated implementation
  //================================================================================================
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_> add_(EVE_SUPPORTS(sse2_),
                                        saturated_type const &  st,
                                        wide<T, N, x86_128_> const &v0,
                                        wide<T, N, x86_128_> const &v1) noexcept
  {
    if constexpr( std::floating_point<T> )
    {
      return add(v0, v1);
    }
    else
    {
      if constexpr( std::signed_integral<T> )
      {
        if constexpr( sizeof(T) == 1 )
        {
          return _mm_adds_epi8(v0, v1);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          return _mm_adds_epi16(v0, v1);
        }
        else
        {
          return add_(EVE_RETARGET(cpu_), st, v0, v1);
        }
      }
      else if constexpr( std::unsigned_integral<T> )
      {
        if constexpr( sizeof(T) == 1 )
        {
          return _mm_adds_epu8(v0, v1);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          return _mm_adds_epu16(v0, v1);
        }
        else
        {
          return add_(EVE_RETARGET(cpu_), st, v0, v1);
        }
      }
    }
  }

  //================================================================================================
  // 256 bits saturated implementation
  //================================================================================================
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_256_> add_(EVE_SUPPORTS(avx2_),
                                        saturated_type const &  st,
                                        wide<T, N, x86_256_> const &v0,
                                        wide<T, N, x86_256_> const &v1) noexcept
  {
    if constexpr( std::floating_point<T> )
    {
      return add(v0, v1);
    }
    else if constexpr( current_api >= avx2 )
    {
      if constexpr( std::signed_integral<T> )
      {
        if constexpr( sizeof(T) == 1 )
        {
          return _mm256_adds_epi8(v0, v1);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          return _mm256_adds_epi16(v0, v1);
        }
        else
        {
          return add_(EVE_RETARGET(cpu_), st, v0, v1);
        }
      }
      else if constexpr( std::unsigned_integral<T> )
      {
        if constexpr( sizeof(T) == 1 )
        {
          return _mm256_adds_epu8(v0, v1);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          return _mm256_adds_epu16(v0, v1);
        }
        else
        {
          return add_(EVE_RETARGET(cpu_), st, v0, v1);
        }
      }
    }
    else
    {
      return add_(EVE_RETARGET(cpu_), st, v0, v1);
    }
  }
}
