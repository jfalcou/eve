//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_ADD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_ADD_HPP_INCLUDED

#include <eve/concept/stdconcepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  //================================================================================================
  // 128/256 bits implementation
  //================================================================================================
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(sse2_), wide<T, N, ABI> v0, wide<T, N, ABI> const &v1) noexcept
  {
    return v0 += v1;
  }

  //================================================================================================
  // 128 bits saturated_ implementation
  //================================================================================================
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> add_(EVE_SUPPORTS(sse2_),
                                        saturated_type const &  st,
                                        wide<T, N, sse_> const &v0,
                                        wide<T, N, sse_> const &v1) noexcept
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
    else
    {
      return add_(EVE_RETARGET(cpu_), st, v0, v1);
    }
  }

  //================================================================================================
  // 256 bits saturated_ implementation
  //================================================================================================
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> add_(EVE_SUPPORTS(avx2_),
                                        saturated_type const &  st,
                                        wide<T, N, avx_> const &v0,
                                        wide<T, N, avx_> const &v1) noexcept
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

#endif
