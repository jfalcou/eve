//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_WIDE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_WIDE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  //================================================================================================
  // 128 bits <-> 128 bits
  template<typename In, typename N, typename Out>
  EVE_FORCEINLINE wide<Out,N> wide_cast_( EVE_SUPPORTS(sse2_),
                                          wide<In, N, sse_> const & v0, as_<Out> const& tgt
                                        ) noexcept
  {
    // Idempotent call
    if constexpr(std::is_same_v<In, Out>) return v0;

    // Convert to double
    if constexpr( std::is_same_v<Out, double> )
    {
      if constexpr( std::is_same_v<In,float> && (N::value<=2))
      {
        return _mm_cvtps_pd(v0);
      }
      else if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) && (N::value<=2))
      {
        return _mm_cvtepi32_pd(v0);
      }
      else
      {
        return wide_cast_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    // Convert to float
    else if constexpr( std::is_same_v<Out, float> )
    {
      if constexpr( std::is_same_v<In,double> && (N::value<=2))
      {
        return _mm_cvtpd_ps(v0);
      }
      else if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) && (N::value<=2))
      {
        return _mm_cvtepi32_ps(v0);
      }
      else
      {
        return wide_cast_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    // Convert to 32 bits integer
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 4) )
    {
      if constexpr( std::is_same_v<In,float> )
      {
        return _mm_cvttps_epi32(v0);
      }
      else if constexpr( std::is_same_v<In,double> && (N::value<=2) )
      {
        return _mm_cvttpd_epi32(v0);
      }
      // SSE 4+ has more integral conversion
      else if constexpr(current_api >= sse4_1)
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) && (N::value<=4) )
        {
          if constexpr( std::is_signed_v<In> ) return _mm_cvtepi16_epi32(v0);
          else                                 return _mm_cvtepu16_epi32(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) && (N::value<=4) )
        {
          if constexpr( std::is_signed_v<In> ) return _mm_cvtepi8_epi32(v0);
          else                                 return _mm_cvtepu8_epi32(v0);
        }
        else
        {
          return wide_cast_(EVE_RETARGET(simd_), v0, tgt);
        }
      }
      else
      {
        return wide_cast_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    // SSE 4+ has more integral conversion
    else if constexpr(current_api >= sse4_1)
    {
      // Convert to 16 bits integer
      if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 2) )
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) && (N::value<=8) )
        {
          if constexpr( std::is_signed_v<In> ) return _mm_cvtepi8_epi16(v0);
          else                                 return _mm_cvtepu8_epi16(v0);
        }
        else
        {
          return wide_cast_(EVE_RETARGET(simd_), v0, tgt);
        }
      }
      // Convert to 64 bits integer
      if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 8) )
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) && (N::value<=2) )
        {
          if constexpr( std::is_signed_v<In> ) return _mm_cvtepi8_epi64(v0);
          else                                 return _mm_cvtepu8_epi64(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) && (N::value<=2) )
        {
          if constexpr( std::is_signed_v<In> ) return _mm_cvtepi16_epi64(v0);
          else                                 return _mm_cvtepu16_epi64(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) && (N::value<=2) )
        {
          if constexpr( std::is_signed_v<In> ) return _mm_cvtepi32_epi64(v0);
          else                                 return _mm_cvtepu32_epi64(v0);
        }
        else
        {
          return wide_cast_(EVE_RETARGET(simd_), v0, tgt);
        }
      }
      else
      {
        return wide_cast_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    else
    {
      return wide_cast_(EVE_RETARGET(simd_), v0, tgt);
    }
  }

  //================================================================================================
  // 256 bits <-> 256 bits
  template<typename In, typename N, typename Out>
  EVE_FORCEINLINE wide<Out,N> wide_cast_( EVE_SUPPORTS(avx_),
                                          wide<In, N, avx_> const & v0, as_<Out> const& tgt
                                        ) noexcept
  {
    // Idempotent call
    if constexpr(std::is_same_v<In, Out>) return v0;

    // Convert to float
    if constexpr( std::is_same_v<Out, float> )
    {
      if constexpr( std::is_same_v<In,double> && (N::value==4))
      {
        return  _mm256_cvtpd_ps(v0);
      }
      else if constexpr(  std::is_integral_v<In> && (sizeof(In) == 4)  && (N::value==4))
      {
        return _mm256_cvtepi32_ps(v0);
      }
      else
      {
        return wide_cast_(EVE_RETARGET(sse2_), v0, tgt);
      }
    }
    // Convert to 32 bits integer
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 4)  && (N::value==4))
    {
      if constexpr( std::is_same_v<In,double>)
      {
        return  _mm256_cvttpd_epi32(v0);
      }
      else if constexpr( std::is_same_v<In,float> && (N::value==8) )
      {
        return  _mm256_cvttps_epi32(v0);
      }
      else
      {
        return wide_cast_(EVE_RETARGET(sse2_), v0, tgt);
      }
    }
    else
    {
      return wide_cast_(EVE_RETARGET(sse2_), v0, tgt);
    }
  }

  //================================================================================================
  // 256 bits <-> 128 bits
  template<typename In, typename N, typename Out>
  EVE_FORCEINLINE wide<Out,N> wide_cast_( EVE_SUPPORTS(avx_),
                                          wide<In, N, sse_> const & v0, as_<Out> const& tgt
                                        ) noexcept
  {
    // Idempotent call
    if constexpr(std::is_same_v<In, Out>) return v0;

    // Convert to double
    if constexpr( std::is_same_v<Out, double> )
    {
      if constexpr( std::is_same_v<In,float> && (N::value==4))
      {
        return  _mm256_cvtps_pd(v0);
      }
      else if constexpr(  std::is_integral_v<In> && (sizeof(In) == 4) && (N::value == 4) )
      {
        return _mm256_cvtepi32_pd(v0);
      }
      else
      {
        return wide_cast_(EVE_RETARGET(sse2_), v0, tgt);
      }
    }
    else if constexpr (current_api >= avx2)
    {
      // Convert to 16 bits integer
      if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 2) )
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) && (N::value == 16))
        {
          if constexpr( std::is_signed_v<In> ) return _mm256_cvtepi8_epi16(v0);
          else                                 return _mm256_cvtepu8_epi16(v0);
        }
        else
        {
          return wide_cast_(EVE_RETARGET(sse2_), v0, tgt);
        }
      }
      // Convert to 32 bits integer
      else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 4) )
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) && (N::value==8))
        {
          if constexpr( std::is_signed_v<In> ) return _mm256_cvtepi8_epi32(v0);
          else                                 return _mm256_cvtepu8_epi32(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) && (N::value==8))
        {
          if constexpr( std::is_signed_v<In> ) return _mm256_cvtepi16_epi32(v0);
          else                                 return _mm256_cvtepu16_epi32(v0);
        }
        else
        {
          return wide_cast_(EVE_RETARGET(sse2_), v0, tgt);
        }
      }
      // Convert to 64 bits integer
      else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 8) )
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) && (N::value==4))
        {
          if constexpr( std::is_signed_v<In> ) return _mm256_cvtepi8_epi64(v0);
          else                                 return _mm256_cvtepu8_epi64(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) && (N::value==4))
        {
          if constexpr( std::is_signed_v<In> ) return _mm256_cvtepi16_epi64(v0);
          else                                 return _mm256_cvtepu16_epi64(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) && (N::value==4))
        {
          if constexpr( std::is_signed_v<In> ) return _mm256_cvtepi32_epi64(v0);
          else                                 return _mm256_cvtepu32_epi64(v0);
        }
        else
        {
          return wide_cast_(EVE_RETARGET(sse2_), v0, tgt);
        }
      }
      else
      {
        return wide_cast_(EVE_RETARGET(sse2_), v0, tgt);
      }
    }
    else
    {
      return wide_cast_(EVE_RETARGET(sse2_), v0, tgt);
    }
  }
}

#endif
