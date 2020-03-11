//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_CONVERT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_CONVERT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/add.hpp>
#include <eve/function/max.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  //================================================================================================
  // 128 bits <-> 128 bits
  template<typename In, typename N, typename Out>
  EVE_FORCEINLINE wide<Out,N> convert_( EVE_SUPPORTS(sse2_),
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
      else if constexpr( std::is_same_v<In, std::int32_t> && (N::value<=2) )
      {
        return _mm_cvtepi32_pd(v0);
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    // Convert to float
    else if constexpr( std::is_same_v<Out, float> )
    {
      if constexpr( std::is_same_v<In,double> && (N::value<=2))
      {
        return _mm_cvtpd_ps(v0);
      }
      else if constexpr( std::is_same_v<In, std::int32_t> && (N::value<=2))
      {
        return _mm_cvtepi32_ps(v0);
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    // Convert to 32 bits integer
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 4) )
    {
      if constexpr( std::is_same_v<In,float> )
      {
        if constexpr(std::is_signed_v<Out>)
          return _mm_cvttps_epi32(v0);
        else
          return _mm_cvttps_epi32(v0);
      }
      else if constexpr( std::is_same_v<In,double> && (N::value<=2) )
      {
        if constexpr(std::is_signed_v<Out>)
        {
          return _mm_cvttpd_epi32(v0);
        }
        else
        {
          return convert_(EVE_RETARGET(simd_), v0, tgt);
        }         
      }
      // SSE 4+ has more integral conversion
      else if constexpr(current_api >= sse4_1)
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) && (N::value<=4) )
        {
          if constexpr( std::is_signed_v<In>)  return _mm_cvtepi16_epi32(v0);
          else                                 return _mm_cvtepu16_epi32(v0);  
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) && (N::value<=4) )
        {
          if constexpr( std::is_signed_v<In> ) return _mm_cvtepi8_epi32(v0);
          else                                 return _mm_cvtepu8_epi32(v0);
        }
        else
        {
          return convert_(EVE_RETARGET(simd_), v0, tgt);
        }
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
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
          return convert_(EVE_RETARGET(simd_), v0, tgt);
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
          if constexpr( std::is_signed_v<In>) return _mm_cvtepi16_epi64(v0);
          else                                return _mm_cvtepu16_epi64(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) && (N::value<=2) )
        {
          if constexpr( std::is_signed_v<In> ) return _mm_cvtepi32_epi64(v0);
          else                                 return _mm_cvtepu32_epi64(v0);
        }
        else
        {
          return convert_(EVE_RETARGET(simd_), v0, tgt);
        }
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    else
    {
     return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
  }
  
  //================================================================================================
  // 256 bits <-> 256 bits
  template<typename In, typename N, typename Out>
  EVE_FORCEINLINE wide<Out,N> convert_( EVE_SUPPORTS(avx_),
                                        wide<In, N, avx_> const & v0, as_<Out> const& tgt
                                      ) noexcept
  {
    // Idempotent call
    if constexpr(std::is_same_v<In, Out>) return v0;
    // Convert to double
    if constexpr( std::is_same_v<Out, double> )
    {
      if constexpr( std::is_same_v<In,float> && (N::value<=4))
      {
        return _mm256_cvtps_pd(v0);
      }
      else if constexpr( std::is_same_v<In, std::int32_t> && (N::value<=4) )
      {
       return _mm256_cvtepi32_pd(v0);
      }
      else
      {
       return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    // Convert to float
    else if constexpr( std::is_same_v<Out, float> )
    {
      if constexpr( std::is_same_v<In,double> && (N::value==4))
      {
        return  _mm256_cvtpd_ps(v0);
      }
      else if constexpr(   std::is_same_v<In, std::int32_t> && (N::value==4))
      {
        return _mm256_cvtepi32_ps(v0);
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    // Convert to 32 bits integer
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 4)  && (N::value==4))
    {
     if constexpr( std::is_same_v<In,double>)
      {
       if (std::is_signed_v<Out>)
         return  _mm256_cvttpd_epi32(v0);
       else
         return  _mm256_cvttpd_epi32(v0);  //max(v0, Zero<Out>()));
      }
      else if constexpr( std::is_same_v<In,float> && (N::value==8) )
      {
        if constexpr(std::is_signed_v<Out>)
        {
          return  _mm256_cvttps_epi32(v0);
        }
        else
        {
          return convert_(EVE_RETARGET(simd_), v0, tgt);
        }                
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    else
    {
     return convert_(EVE_RETARGET(sse4_2_), v0, tgt);
    }
  }
  
  //================================================================================================
  // 256 bits <-> 128 bits
  template<typename In, typename N, typename Out>
  EVE_FORCEINLINE wide<Out,N> convert_( EVE_SUPPORTS(avx_),
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
      else if constexpr(  std::is_same_v<In, std::int32_t> && (N::value == 4) )
      {
        return _mm256_cvtepi32_pd(v0);
      }
      else
      {
        return convert_(EVE_RETARGET(sse2_), v0, tgt);
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
          return convert_(EVE_RETARGET(sse2_), v0, tgt);
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
          if constexpr( std::is_signed_v<In>) return _mm256_cvtepi16_epi32(v0);
          else                                return _mm256_cvtepu16_epi32(v0); ;
        }
        else
        {
          return convert_(EVE_RETARGET(sse2_), v0, tgt);
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
          return convert_(EVE_RETARGET(sse2_), v0, tgt);
        }
      }
      else
      {
         return convert_(EVE_RETARGET(sse2_), v0, tgt);
      }
    }
    else
    {
      return convert_(EVE_RETARGET(sse2_), v0, tgt);
    }
  }
  
  /////////////////////////////////////////////////////////////////////////////////////
  // saturated conversions
  //////////////////////////////////////////////////////////////////////////////////////
  //====================================================================================
  // 128 bits <-> 128 bits
  template<typename In, typename N, typename Out>
  EVE_FORCEINLINE wide<Out,N> convert_( EVE_SUPPORTS(sse2_)
                                      , saturated_type const & sat_
                                      , wide<In, N> const & v0, as_<Out> const& tgt
                                      ) noexcept
  {
    // Idempotent call
    if constexpr(std::is_same_v<In, Out>) return v0;
    
    if constexpr( std::is_same_v<In,int16_t> && std::is_same_v<Out,int8_t> && (N::value <= 16))
    {
      if constexpr(N::value == 16)
      {
        auto [ low, high ] = v0.slice();
        return _mm_packs_epi16(low, high);
      }
      else if constexpr(N::value == 8)
      {
        wide<Out, fixed<2*N::value>> tmp = _mm_packs_epi16(v0, v0);
        auto [low, hi] = tmp.slice();
        return low; 
      }
      else if constexpr(N::value <= 8)
      {
        return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt);
      }
    }
    else if constexpr( std::is_same_v<In,int32_t> && std::is_same_v<Out,int16_t> && (N::value <= 8))
    {
      if constexpr(N::value == 8)
      {
        auto [ low, high ] = v0.slice();
        return _mm_packs_epi32(low, high);
      }
      else if constexpr(N::value == 4)
      {
        wide<Out, fixed<2*N::value>> tmp = _mm_packs_epi16(v0, v0);
        auto [low, hi] = tmp.slice();
        return low; 
      }
      else if constexpr(N::value <= 4)
      {
        return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt);
      }       
    }
    else if constexpr( std::is_same_v<In,int16_t> && std::is_same_v<Out,uint8_t> && (N::value <= 16))
    {
      if constexpr(N::value == 16)
      {
        auto [ low, high ] = v0.slice();
        return _mm_packus_epi16(low, high);
      }
      else if constexpr(N::value == 8)
      {
        wide<Out, fixed<2*N::value>> tmp = _mm_packus_epi16(v0, v0);
        auto [low, hi] = tmp.slice();
        return low; 
      }
      else if constexpr(N::value <= 8)
      {
        return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt);
      }
    }
    else
    {
      return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt);
    }
  }
  
  //================================================================================================
  // 256 bits <-> 256 bits
  template<typename In, typename N, typename Out>
  EVE_FORCEINLINE wide<Out,N> convert_( EVE_SUPPORTS(avx2_)
                                      , saturated_type const & sat_
                                      , wide<In, N> const & v0, as_<Out> const& tgt
                                      ) noexcept
  {
    // Idempotent call
    if constexpr(std::is_same_v<In, Out>) return v0;
    
    if constexpr( std::is_same_v<In,int16_t> && std::is_same_v<In,int8_t> && (N::value <= 32))
    {
      if constexpr(N::value == 32)
      {
        auto [ low, high ] = v0.slice();
        return _mm256_packs_epi16(low, high);
      }
      else if constexpr(N::value <= 16)
      {
        return _mm256_packs_epi16(v0, v0);
      }
    }
    else if constexpr( std::is_same_v<In,int32_t> && std::is_same_v<Out,int16_t> && (N::value <= 16))
    {
      if constexpr(N::value == 16)
      {
        auto [ low, high ] = v0.slice();
        return _mm256_packs_epi32(low, high);
      }
      else if constexpr(N::value == 8)
      {
        wide<Out, fixed<2*N::value>> tmp = _mm256_packs_epi32(v0, v0);
        auto [low, hi] = tmp.slice();
        return low; 
      }
      else if constexpr(N::value <= 8)
      {
        return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt);
      }
    }
    else if constexpr( std::is_same_v<In,int16_t> && std::is_same_v<Out,uint8_t> && (N::value <= 32))
    {
      if constexpr(N::value == 32)
      {
        auto [ low, high ] = v0.slice();
        return _mm256_packus_epi16(low, high);
      }
       else if constexpr(N::value == 16)
      {
        wide<Out, fixed<2*N::value>> tmp = _mm256_packus_epi16(v0, v0);
        auto [low, hi] = tmp.slice();
        return low; 
      }
      else if constexpr(N::value <= 16)
      {
         return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt);
      }
    }
    else if constexpr( std::is_same_v<In,int32_t> && std::is_same_v<Out,uint16_t> && (N::value <= 16))
    {
      if constexpr(N::value == 16)
      {
        auto [ low, high ] = v0.slice();
        return _mm256_packus_epi32(low, high);
      }
      else if constexpr(N::value == 8)
      {
        wide<Out, fixed<2*N::value>> tmp = _mm256_packus_epi32(v0, v0);
        auto [low, hi] = tmp.slice();
        return low;
      }
      else if constexpr(N::value <= 8)
      {
        return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt);
      }
    }
    else
    {
      return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt);
    }
  }  
}

#endif
