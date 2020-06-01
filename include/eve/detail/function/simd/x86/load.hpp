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
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::detail
{
  //================================================================================================
  // 128 bits loads
  //================================================================================================
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto load(as_<wide<T, N>> const &, eve::sse_ const &, T const* p)
  {
    if constexpr( std::is_same_v<T, double> )
    {
      return _mm_loadu_pd(p);
    }
    else if constexpr( std::is_same_v<T, float> )
    {
      return _mm_loadu_ps(p);
    }
    else if constexpr( std::is_integral_v<T> )
    {
      return _mm_loadu_si128((__m128i *)p);
    }
  }

  template<real_scalar_value T, typename N, std::size_t A>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &tgt, eve::sse_ const &mode, aligned_ptr<T const, A> p) noexcept
  {
    if constexpr( A >= 16 )
    {
      if constexpr( std::is_same_v<T, double> )
      {
        return _mm_load_pd(p.get());
      }
      else if constexpr( std::is_same_v<T, float> )
      {
        return _mm_load_ps(p.get());
      }
      else if constexpr( std::is_integral_v<T> )
      {
        return _mm_load_si128((__m128i *)p.get());
      }
    }
    else
    {
      return load(tgt, mode, p.get());
    }
  }

  template<real_scalar_value T, typename N, std::size_t A>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &tgt, eve::sse_ const & mode, aligned_ptr<T, A> p) noexcept
  {
    return load(tgt,mode, aligned_ptr<T const, A>(p));
  }

  //------------------------------------------------------------------------------------------------
  // 256 bits loads
  //================================================================================================
  // 256 bits loads
  //================================================================================================
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto load(as_<wide<T, N>> const &, eve::avx_ const &, T const* p) noexcept
  {
    if constexpr( std::is_same_v<T, double> )
    {
      return _mm256_loadu_pd(p);
    }
    else if constexpr( std::is_same_v<T, float> )
    {
      return _mm256_loadu_ps(p);
    }
    else if constexpr( std::is_integral_v<T> )
    {
      return _mm256_loadu_si256((__m256i *)p);
    }
  }

  template<real_scalar_value T, typename N, std::size_t A>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &tgt, eve::avx_ const &mode, aligned_ptr<T const, A> p) noexcept
  {
    if constexpr( A >= 16 )
    {
      if constexpr( std::is_same_v<T, double> )
      {
        return _mm256_load_pd(p.get());
      }
      else if constexpr( std::is_same_v<T, float> )
      {
        return _mm256_load_ps(p.get());
      }
      else if constexpr( std::is_integral_v<T> )
      {
        return _mm256_load_si256((__m256i *)p.get());
      }
    }
    else
    {
      return load(tgt, mode, p.get());
    }
  }

  template<real_scalar_value T, typename N, std::size_t A>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &tgt, eve::avx_ const & mode, aligned_ptr<T, A> p) noexcept
  {
    return load(tgt, mode, aligned_ptr<T const, A>(p));
  }

}

