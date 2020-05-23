//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_FNMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_FNMS_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/function/fms.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> fnms_(EVE_SUPPORTS(avx2_),
                                         wide<T, N, sse_> const &a,
                                         wide<T, N, sse_> const &b,
                                         wide<T, N, sse_> const &c) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm_nmacc_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm_nmacc_ps(a, b, c);
      }
      else
        return fms(-a, b, c);
    }
    else
    {
      if constexpr( supports_xop )
      {
        if constexpr( std::is_integral_v<T> && sizeof(T) == 2 )
          return _mm_nmacc_epi16(a, b, c);
        else if constexpr( std::is_integral_v<T> && sizeof(T) == 4 )
          return _mm_nmacc_epi32(a, b, c);
        else
          return fms(-a, b, c);
      }
      else
        return fms(-a, b, c);
    }
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> fnms_(EVE_SUPPORTS(avx2_),
                                         wide<T, N, avx_> const &a,
                                         wide<T, N, avx_> const &b,
                                         wide<T, N, avx_> const &c) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm256_nmacc_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm256_nmacc_ps(a, b, c);
      }
      else
        return fms(-a, b, c);
    }
    else
      return fms(-a, b, c);
  }

  /////////////////////////////////////////////////////////////////////////////////
  /// pedantic_ numeric_
  template<decorator D, real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> fnms_(EVE_SUPPORTS(avx2_),
                                         D const &,
                                         wide<T, N, sse_> const &a,
                                         wide<T, N, sse_> const &b,
                                         wide<T, N, sse_> const &c) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm_nmacc_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm_nmacc_ps(a, b, c);
      }
      else
        return D()(fms)(-a, b, c);
    }
    else
    {
      if constexpr( supports_xop )
      {
        if constexpr( std::is_integral_v<T> && sizeof(T) == 2 )
          return _mm_nmacc_epi16(a, b, c);
        else if constexpr( std::is_integral_v<T> && sizeof(T) == 4 )
          return _mm_nmacc_epi32(a, b, c);
        else
          return D()(fms)(-a, b, c);
      }
      else
        return D()(fms)(-a, b, c);
    }
  }

  template<decorator D, real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> fnms_(EVE_SUPPORTS(avx2_),
                                         D const &               deco,
                                         wide<T, N, avx_> const &a,
                                         wide<T, N, avx_> const &b,
                                         wide<T, N, avx_> const &c) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm256_nmacc_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm256_nmacc_ps(a, b, c);
      }
      else
        return D()(fms)(-a, b, c);
    }
    else
      return D()(fms)(-a, b, c);
  }

}

#endif
