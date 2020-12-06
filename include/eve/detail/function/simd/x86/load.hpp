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
#include <eve/concept/memory.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>

namespace eve::detail
{
  //================================================================================================
  // Regular loads
  //================================================================================================
  template<typename T, typename N, x86_abi ABI, simd_compatible_ptr<wide<T,N,ABI>> Ptr >
  EVE_FORCEINLINE auto load(eve::as_<wide<T, N, ABI>> const &, ABI const &, Ptr p)
  requires( std::same_as<T, std::remove_cvref_t<decltype(*p)>> )
  {
    constexpr auto cat = categorize<wide<T, N>>();
    constexpr bool isfull256 = N::value*sizeof(T) == x86_256_::bytes;
    constexpr bool isfull128 = N::value*sizeof(T) == x86_128_::bytes;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      if constexpr( isfull256 )
      {
              if constexpr( cat == category::float64x4 )  return _mm256_load_pd(p.get());
        else  if constexpr( cat == category::float32x8 )  return _mm256_load_ps(p.get());
        else return _mm256_load_si256((__m256i *)p.get());
      }
      else if constexpr( isfull128 )
      {
              if constexpr( cat == category::float64x2 )  return _mm_load_pd(p.get());
        else  if constexpr( cat == category::float32x4 )  return _mm_load_ps(p.get());
        else  return _mm_load_si128((__m128i *)p.get());
      }
      else
      {
        typename wide<T, N>::storage_type that;
        std::memcpy(&that, p.get(), N::value * sizeof(T));
        return that;
      }
    }
    else
    {
      if constexpr( isfull256 )
      {
              if constexpr( cat == category::float64x4 )  return _mm256_loadu_pd(p);
        else  if constexpr( cat == category::float32x8 )  return _mm256_loadu_ps(p);
        else return _mm256_loadu_si256((__m256i *)p);
      }
      else if constexpr( isfull128 )
      {
              if constexpr( cat == category::float64x2 )  return _mm_loadu_pd(p);
        else  if constexpr( cat == category::float32x4 )  return _mm_loadu_ps(p);
        else  return _mm_loadu_si128((__m128i *)p);
      }
      else
      {
        typename wide<T, N>::storage_type that;
        std::memcpy(&that, p, N::value * sizeof(T));
        return that;
      }
    }
  }
}
