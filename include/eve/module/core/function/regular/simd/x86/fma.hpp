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

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_> fma_(EVE_SUPPORTS(avx2_),
                                        wide<T, N, x86_128_> const &a,
                                        wide<T, N, x86_128_> const &b,
                                        wide<T, N, x86_128_> const &c) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma3 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm_fmadd_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm_fmadd_ps(a, b, c);
      }
      else if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm_macc_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm_macc_ps(a, b, c);
      }
      else
        return fma_(EVE_RETARGET(cpu_), a, b, c);
    }
    else if constexpr( std::is_integral_v<T> )
    {
      if constexpr( supports_xop )
      {
        if constexpr( sizeof(T) == 2 )
          return _mm_macc_epi16(a, b, c);
        else if constexpr( sizeof(T) == 4 )
          return _mm_macc_epi32(a, b, c);
        else
          return fma_(EVE_RETARGET(cpu_), a, b, c);
      }
      else
        return fma_(EVE_RETARGET(cpu_), a, b, c);
    }
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_256_> fma_(EVE_SUPPORTS(avx2_),
                                        wide<T, N, x86_256_> const &a,
                                        wide<T, N, x86_256_> const &b,
                                        wide<T, N, x86_256_> const &c) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma3 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm256_fmadd_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm256_fmadd_ps(a, b, c);
      }
      else if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm256_macc_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm256_macc_ps(a, b, c);
      }
      else
        return fma_(EVE_RETARGET(cpu_), a, b, c);
    }
    else
      return fma_(EVE_RETARGET(cpu_), a, b, c);
  }
}
