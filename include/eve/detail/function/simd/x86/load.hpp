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
#include <eve/detail/function/to_logical.hpp>

namespace eve::detail
{
  //================================================================================================
  // Regular loads
  //================================================================================================
  template<typename T, typename N, x86_abi ABI, simd_compatible_ptr<wide<T,N,ABI>> Ptr >
  EVE_FORCEINLINE auto load(eve::as_<wide<T, N, ABI>> const &, Ptr p)
  requires( std::same_as<T, std::remove_cvref_t<decltype(*p)>> )
  {
    constexpr auto cat = categorize<wide<T, N>>();
    constexpr bool isfull512 = N::value*sizeof(T) == x86_512_::bytes;
    constexpr bool isfull256 = N::value*sizeof(T) == x86_256_::bytes;
    constexpr bool isfull128 = N::value*sizeof(T) == x86_128_::bytes;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      if constexpr( isfull512 )
      {
              if constexpr( cat == category::float64x8 )   return _mm512_load_pd(p.get());
        else  if constexpr( cat == category::float32x16 )  return _mm512_load_ps(p.get());
        else return _mm512_load_si512((__m512i *)p.get());
      }
      else if constexpr( isfull256 )
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
      if constexpr( isfull512 )
      {
              if constexpr( cat == category::float64x8 )   return _mm512_loadu_pd(p);
        else  if constexpr( cat == category::float32x16 )  return _mm512_loadu_ps(p);
        else return _mm512_loadu_si512((__m512i *)p);
      }
      else if constexpr( isfull256 )
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

  //================================================================================================
  // logical loads require some specific setup
  //================================================================================================
  template<typename T, typename N, typename Ptr, x86_abi ABI>
  EVE_FORCEINLINE
  auto load([[maybe_unused]] eve::as_<logical<wide<T, N, ABI>>> const& tgt, Ptr p)
  requires( std::same_as<logical<T>, std::remove_cvref_t<decltype(*p)>> )
  {
    auto block = [&]() -> wide<T, N, ABI>
    {
      using wtg = eve::as_<wide<T, N, ABI>>;
      if constexpr( !std::is_pointer_v<Ptr> )
      {
        using ptr_t = typename Ptr::template rebind<T const>;
        return load(wtg{}, ptr_t( (T const*)(p.get())) );
      }
      else
      {
        return load(wtg{}, (T const*)(p));
      }
    }();

    if constexpr( current_api >= avx512 ) return to_logical(block).storage();
    else                                  return bit_cast(block, tgt);
  }

  template<typename Iterator, typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto load ( eve::as_<logical<wide<T, N, ABI>>> const &
                            , Iterator b, Iterator e
                            ) noexcept
  {
    auto block = [&]() -> wide<T, N, ABI>
    {
      using tgt = eve::as_<wide<T, N, ABI>>;
      return load(tgt(), b, e);
    }();

    return to_logical(block).storage();
  }
}
