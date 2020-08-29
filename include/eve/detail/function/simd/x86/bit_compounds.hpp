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

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <concepts>
#include <eve/detail/function/bit_cast.hpp>

namespace eve::detail
{
  //================================================================================================
  // &=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitand(wide<T, N, sse_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, sse_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, sse_>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitand(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});
      if constexpr( std::same_as<T, float> )
      {
        self = _mm_and_ps(self, bit_other);
      }
      else if constexpr( std::same_as<T, double> )
      {
        self = _mm_and_pd(self, bit_other);
      }
      else if constexpr( std::integral<T> )
      {
        self = _mm_and_si128(self, bit_other);
      }

      return self;
    }
  }

  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitand(wide<T, N, avx_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, avx_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, avx_>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitand(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});
      if constexpr( std::same_as<T, float> )
      {
        self = _mm256_and_ps(self, bit_other);
      }
      else if constexpr( std::same_as<T, double> )
      {
        self = _mm256_and_pd(self, bit_other);
      }
      else if constexpr( integral_value<T> )
      {
        if constexpr( current_api >= avx2 )
        {
          self = _mm256_and_si256(self, bit_other);
        }
        else
        {
          self = _mm256_castps_si256(
              _mm256_and_ps(_mm256_castsi256_ps(self), _mm256_castsi256_ps(bit_other)));
        }
      }

      return self;
    }
  }

  //================================================================================================
  // |=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitor(wide<T, N, sse_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, sse_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, sse_>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});

      if constexpr( std::same_as<T, float> )
      {
        self = _mm_or_ps(self, bit_other);
      }
      else if constexpr( std::same_as<T, double> )
      {
        self = _mm_or_pd(self, bit_other);
      }
      else if constexpr( std::integral<T> )
      {
        self = _mm_or_si128(self, bit_other);
      }
      return self;
    }
  }

  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitor(wide<T, N, avx_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, avx_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, avx_>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});

      if constexpr( std::same_as<T, float> )
      {
        self = _mm256_or_ps(self, bit_other);
      }
      else if constexpr( std::same_as<T, double> )
      {
        self = _mm256_or_pd(self, bit_other);
      }
      else if constexpr( integral_value<T> )
      {
        if constexpr( current_api >= avx2 )
        {
          self = _mm256_or_si256(self, bit_other);
        }
        else
        {
          self = _mm256_castps_si256(
              _mm256_or_ps(_mm256_castsi256_ps(self), _mm256_castsi256_ps(bit_other)));
        }
      }

      return self;
    }
  }

  //================================================================================================
  // ^=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitxor(wide<T, N, sse_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, sse_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, sse_>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitxor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});
      if constexpr( std::same_as<T, float> )
      {
        self = _mm_xor_ps(self, bit_other);
      }
      else if constexpr( std::same_as<T, double> )
      {
        self = _mm_xor_pd(self, bit_other);
      }
      else if constexpr( std::integral<T> )
      {
        self = _mm_xor_si128(self, bit_other);
      }

      return self;
    }
  }

  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitxor(wide<T, N, avx_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, avx_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, avx_>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitxor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});
      if constexpr( std::same_as<T, float> )
      {
        self = _mm256_xor_ps(self, bit_other);
      }
      else if constexpr( std::same_as<T, double> )
      {
        self = _mm256_xor_pd(self, bit_other);
      }
      else if constexpr( integral_value<T> )
      {
        if constexpr( current_api >= avx2 )
        {
          self = _mm256_xor_si256(self, bit_other);
        }
        else
        {
          self = _mm256_castps_si256(
              _mm256_xor_ps(_mm256_castsi256_ps(self), _mm256_castsi256_ps(bit_other)));
        }
      }

      return self;
    }
  }
}

