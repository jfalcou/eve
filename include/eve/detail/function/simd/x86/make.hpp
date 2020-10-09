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

#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/meta.hpp>

namespace eve::detail
{
  //================================================================================================
  // 128 bits make
  //================================================================================================
  template<real_scalar_value T, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<T> const &, eve::x86_128_ const &, Vs... vs) noexcept
  {
    static_assert(sizeof...(Vs) <= x86_128_::bytes / sizeof(T),
                  "[eve::make sse] - Invalid number of arguments");

    if constexpr( std::is_same_v<T, double> )
    {
      return _mm_setr_pd(static_cast<double>(vs)...);
    }
    else if constexpr( std::is_same_v<T, float> )
    {
      if constexpr( sizeof...(vs) == 4 )
      {
        return _mm_setr_ps(static_cast<float>(vs)...);
      }
      if constexpr( sizeof...(vs) == 2 )
      {
        return _mm_setr_ps(static_cast<float>(vs)..., 0.f, 0.f);
      }
    }
    else
    {
      if constexpr( sizeof(T) == 8 )
      {
        __m128i that = {};

        T *ptr = reinterpret_cast<detail::alias_t<T> *>(&that);
        T  d[] = {static_cast<T>(vs)...};
        ptr[0] = d[0];
        ptr[1] = d[1];

        return that;
      }

      if constexpr( sizeof...(vs) == 4 && sizeof(T) == 4 )
      {
        return _mm_setr_epi32(static_cast<int>(vs)...);
      }
      else if constexpr( sizeof...(vs) == 2 && sizeof(T) == 4 )
      {
        return _mm_setr_epi32(static_cast<T>(vs)..., 0, 0);
      }
      else if constexpr( sizeof...(vs) == 8 && sizeof(T) == 2 )
      {
        return _mm_setr_epi16(static_cast<T>(vs)...);
      }
      else if constexpr( sizeof...(vs) == 4 && sizeof(T) == 2 )
      {
        return _mm_setr_epi16(static_cast<T>(vs)..., 0, 0, 0, 0);
      }
      else if constexpr( sizeof...(vs) == 2 && sizeof(T) == 2 )
      {
        return _mm_setr_epi16(static_cast<T>(vs)..., 0, 0, 0, 0, 0, 0);
      }
      else if constexpr( sizeof...(vs) == 16 && sizeof(T) == 1 )
      {
        return _mm_setr_epi8(static_cast<T>(vs)...);
      }
      else if constexpr( sizeof...(vs) == 8 && sizeof(T) == 1 )
      {
        return _mm_setr_epi8(static_cast<T>(vs)..., 0, 0, 0, 0, 0, 0, 0, 0);
      }
      else if constexpr( sizeof...(vs) == 4 && sizeof(T) == 1 )
      {
        return _mm_setr_epi8(static_cast<T>(vs)..., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      }
      else if constexpr( sizeof...(vs) == 2 && sizeof(T) == 1 )
      {
        return _mm_setr_epi8(static_cast<T>(vs)..., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      }
    }
  }

  template<real_scalar_value T, typename V>
  EVE_FORCEINLINE auto make(eve::as_<T> const &, eve::x86_128_ const &, V v) noexcept
  {
    if constexpr( std::is_same_v<T, double> )
    {
      return _mm_set1_pd(static_cast<double>(v));
    }
    else if constexpr( std::is_same_v<T, float> )
    {
      return _mm_set1_ps(static_cast<float>(v));
    }
    else
    {
      if constexpr( sizeof(T) == 8 )
      {
        __m128i that = {};

        T *ptr = reinterpret_cast<detail::alias_t<T> *>(&that);
        ptr[0] = ptr[1] = static_cast<T>(v);

        return that;
      }
      else if constexpr( sizeof(T) == 4 )
      {
        return _mm_set1_epi32(static_cast<T>(v));
      }
      else if constexpr( sizeof(T) == 2 )
      {
        return _mm_set1_epi16(static_cast<T>(v));
      }
      else if constexpr( sizeof(T) == 1 )
      {
        return _mm_set1_epi8(static_cast<T>(v));
      }
    }
  }

  //================================================================================================
  // 256 bits make
  //================================================================================================
  template<real_scalar_value T, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<T> const &, eve::x86_256_ const &, Vs... vs) noexcept
  {
    static_assert(sizeof...(Vs) <= x86_256_::bytes / sizeof(T),
                  "[eve::make avx] - Invalid number of arguments");

    if constexpr( std::is_same_v<T, double> )
    {
      return _mm256_setr_pd(vs...);
    }
    else if constexpr( std::is_same_v<T, float> )
    {
      return _mm256_setr_ps(vs...);
    }
    else
    {
      if constexpr( sizeof...(vs) == 4 && sizeof(T) == 8 )
      {
        return _mm256_setr_epi64x(vs...);
      }
      else if constexpr( sizeof...(vs) == 8 && sizeof(T) == 4 )
      {
        return _mm256_setr_epi32(vs...);
      }
      else if constexpr( sizeof...(vs) == 16 && sizeof(T) == 2 )
      {
        return _mm256_setr_epi16(vs...);
      }
      else if constexpr( sizeof...(vs) == 32 && sizeof(T) == 1 )
      {
        return _mm256_setr_epi8(vs...);
      }
    }
  }

  template<real_scalar_value T, typename V>
  EVE_FORCEINLINE auto make(eve::as_<T> const &, eve::x86_256_ const &, V v) noexcept
  {
    if constexpr( std::is_same_v<T, double> )
    {
      return _mm256_set1_pd(v);
    }
    else if constexpr( std::is_same_v<T, float> )
    {
      return _mm256_set1_ps(v);
    }
    else
    {
      if constexpr( sizeof(T) == 8 )
      {
        return _mm256_set1_epi64x(static_cast<T>(v));
      }
      else if constexpr( sizeof(T) == 4 )
      {
        return _mm256_set1_epi32(static_cast<T>(v));
      }
      else if constexpr( sizeof(T) == 2 )
      {
        return _mm256_set1_epi16(static_cast<T>(v));
      }
      else if constexpr( sizeof(T) == 1 )
      {
        return _mm256_set1_epi8(static_cast<T>(v));
      }
    }
  }

  //================================================================================================
  // logical cases
  //================================================================================================
  template<real_scalar_value T, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<logical<T>> const &, eve::x86_128_ const &, Vs... vs) noexcept
  {
    return make(eve::as_<T> {}, eve::x86_128_ {}, logical<T>(vs).mask()...);
  }

  template<real_scalar_value T, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<logical<T>> const &, eve::x86_256_ const &, Vs... vs) noexcept
  {
    return make(eve::as_<T> {}, eve::x86_256_ {}, logical<T>(vs).mask()...);
  }
}
