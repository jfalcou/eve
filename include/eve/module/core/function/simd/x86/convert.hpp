//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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

// pour convertir ss -> us
// wide<std::uint64_t> vv = _mm_cvtepi8_epi64(vu);
// std::cout << std::dec << (vv & 0x00000000000000FFULL) << "\n";
// 21 h 39
// wide<std::uint8_t> vu(243);
//  std::cout << vu << "\n";
// wide<std::uint64_t> vv = _mm_cvtepi8_epi64(vu);
// std::cout << std::dec << (vv & 0x00000000000000FFULL) << "\n";

namespace eve::detail
{
  //================================================================================================
  // 128 bits <-> 128 bits
  template<typename In, typename N, typename Out>
  EVE_FORCEINLINE wide<Out,N> convert_( EVE_SUPPORTS(sse2_),
                                        wide<In, N, sse_> const & v0, as_<Out> const& tgt
                                      ) noexcept
  {
    std::cout << "128 bits <-> 128 bits" << std::endl; 
    // Idempotent call
    if constexpr(std::is_same_v<In, Out>) return v0;
    std::cout <<  "sse 0" << std::endl; 
    
    // Convert to double
    if constexpr( std::is_same_v<Out, double> )
    {
      std::cout <<  "sse 1" << std::endl; 
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
      std::cout <<  "sse 2" << std::endl; 
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
      std::cout <<  "sse 3" << std::endl; 
      if constexpr( std::is_same_v<In,float> )
      {
        std::cout <<  "sse 3.1" << std::endl;
        if constexpr(std::is_signed_v<Out>)
          return _mm_cvttps_epi32(v0);
        else
          return _mm_cvttps_epi32(v0);
      }
      else if constexpr( std::is_same_v<In,double> && (N::value<=2) )
      {
        std::cout <<  "sse 3.2" << std::endl; 
        if constexpr(std::is_signed_v<Out>)
        {
          return _mm_cvttpd_epi32(v0);
        }
        else
        {
          std::cout <<  "sse 3.3" << std::endl; 
          return convert_(EVE_RETARGET(simd_), v0, tgt);
        }         
      }
      // SSE 4+ has more integral conversion
      else if constexpr(current_api >= sse4_1)
      {
        std::cout <<  "sse 4" << std::endl; 
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
          std::cout <<  "sse 5" << std::endl; 
          return convert_(EVE_RETARGET(simd_), v0, tgt);
        }
      }
      else
      {
        std::cout <<  "sse 6" << std::endl; 
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    // SSE 4+ has more integral conversion
    else if constexpr(current_api >= sse4_1)
    {
      std::cout <<  "sse 7" << std::endl; 
      // Convert to 16 bits integer
      if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 2) )
      {
        std::cout <<  "sse 8" << std::endl; 
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
        std::cout <<  "sse 9" << std::endl; 
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) && (N::value<=2) )
        {
          std::cout <<  "sse 9.1" << std::endl; 
          if constexpr( std::is_signed_v<In> ) return _mm_cvtepi8_epi64(v0);
          else                                 return _mm_cvtepu8_epi64(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) && (N::value<=2) )
        {
          std::cout <<  "sse 9.2" << std::endl; 
          if constexpr( std::is_signed_v<In>) return _mm_cvtepi16_epi64(v0);
          else                                return _mm_cvtepu16_epi64(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) && (N::value<=2) )
        {
          std::cout <<  "sse 9.3" << std::endl; 
          if constexpr( std::is_signed_v<In> ) return _mm_cvtepi32_epi64(v0);
          else                                 return _mm_cvtepu32_epi64(v0);
        }
        else
        {
        std::cout <<  "sse 9.4" << std::endl; 
          return convert_(EVE_RETARGET(simd_), v0, tgt);
        }
      }
      else
      {
        std::cout <<  "sse 9.5" << std::endl; 
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    else
    {
      std::cout <<  "sse 10" << std::endl; 
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
    std::cout << "256 bits <-> 256 bits" << std::endl; 
    // Idempotent call
    if constexpr(std::is_same_v<In, Out>) return v0;
     std::cout <<  "avx2 -0" << std::endl;   
    // Convert to double
    if constexpr( std::is_same_v<Out, double> )
    {
      std::cout <<  "avx2 -1" << std::endl; 
      if constexpr( std::is_same_v<In,float> && (N::value<=4))
      {
      std::cout <<  "avx2 -2" << std::endl; 
        return _mm256_cvtps_pd(v0);
      }
      else if constexpr( std::is_same_v<In, std::int32_t> && (N::value<=4) )
      {
       std::cout <<  "avx2 -3" << std::endl; 
       return _mm256_cvtepi32_pd(v0);
      }
      else
      {
       std::cout <<  "avx2 -4" << std::endl; 
       return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    // Convert to float
    else if constexpr( std::is_same_v<Out, float> )
    {
       std::cout <<  "avx2 -5" << std::endl; 
      if constexpr( std::is_same_v<In,double> && (N::value==4))
      {
       std::cout <<  "avx2 -6" << std::endl; 
        return  _mm256_cvtpd_ps(v0);
      }
      else if constexpr(   std::is_same_v<In, std::int32_t> && (N::value==4))
      {
       std::cout <<  "avx2 -7" << std::endl; 
        return _mm256_cvtepi32_ps(v0);
      }
      else
      {
       std::cout <<  "avx2 -8" << std::endl; 
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    // Convert to 32 bits integer
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 4)  && (N::value==4))
    {
        std::cout <<  "avx2 -9" << std::endl; 
     if constexpr( std::is_same_v<In,double>)
      {
       std::cout <<  "avx2 -10" << std::endl;
       if (std::is_signed_v<Out>)
         return  _mm256_cvttpd_epi32(v0);
       else
         return  _mm256_cvttpd_epi32(v0);  //max(v0, Zero<Out>()));
      }
      else if constexpr( std::is_same_v<In,float> && (N::value==8) )
      {
        std::cout <<  "avx2 -11" << std::endl; 
        if constexpr(std::is_signed_v<Out>)
        {
          std::cout <<  "avx2 -12" << std::endl; 
          return  _mm256_cvttps_epi32(v0);
        }
        else
        {
          std::cout <<  "avx2 -13" << std::endl; 
          return convert_(EVE_RETARGET(simd_), v0, tgt);
        }                
      }
      else
      {
          std::cout <<  "avx2 -14" << std::endl; 
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    else
    {
           std::cout <<  "avx2 -15" << std::endl; 
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
    std::cout << "256 bits <-> 128 bits" << std::endl; 
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
        std::cout <<  "avx2 1" << std::endl; 
      // Convert to 16 bits integer
      if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 2) )
      {
        std::cout <<  "avx2 2" << std::endl; 
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) && (N::value == 16))
        {
          if constexpr( std::is_signed_v<In> ) return _mm256_cvtepi8_epi16(v0);
          else                                 return _mm256_cvtepu8_epi16(v0);
        }
        else
        {
          std::cout <<  "avx2 3" << std::endl; 
          return convert_(EVE_RETARGET(sse2_), v0, tgt);
        }
      }
      // Convert to 32 bits integer
      else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 4) )
      {
        std::cout <<  "avx2 4" << std::endl; 
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
          std::cout <<  "avx2 6" << std::endl; 
          return convert_(EVE_RETARGET(sse2_), v0, tgt);
        }
      }
      // Convert to 64 bits integer
      else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 8) )
      {
          std::cout <<  "avx2 7" << std::endl; 
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) && (N::value==4))
        {
          if constexpr( std::is_signed_v<In> ) return _mm256_cvtepi8_epi64(v0);
          else                                 return _mm256_cvtepu8_epi64(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) && (N::value==4))
        {
          std::cout <<  "avx2 8" << std::endl; 
          if constexpr( std::is_signed_v<In> ) return _mm256_cvtepi16_epi64(v0);
          else                                 return _mm256_cvtepu16_epi64(v0);
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) && (N::value==4))
        {
          std::cout <<  "avx2 9" << std::endl; 
          if constexpr( std::is_signed_v<In> ) return _mm256_cvtepi32_epi64(v0);
          else                                 return _mm256_cvtepu32_epi64(v0);
        }
        else
        {
         std::cout <<  "avx2 10" << std::endl; 
          return convert_(EVE_RETARGET(sse2_), v0, tgt);
        }
      }
      else
      {
         std::cout <<  "avx2 11" << std::endl; 
         return convert_(EVE_RETARGET(sse2_), v0, tgt);
      }
    }
    else
    {
         std::cout <<  "avx2 12" << std::endl; 
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
      else if constexpr(N::value <= 8)
      {
        return _mm_packs_epi16(v0, v0);
      }
    }
    else if constexpr( std::is_same_v<In,int32_t> && std::is_same_v<Out,int16_t> && (N::value <= 8))
    {
      if constexpr(N::value == 8)
      {
        auto [ low, high ] = v0.slice();
        return _mm_packs_epi32(low, high);
      }
      else if constexpr(N::value <= 4)
      {
        return _mm_packs_epi32(v0, v0);
      }       
    }
    else if constexpr( std::is_same_v<In,int16_t> && std::is_same_v<Out,uint8_t> && (N::value <= 16))
    {
      if constexpr(N::value == 16)
      {
        auto [ low, high ] = v0.slice();
        return _mm_packus_epi16(low, high);
      }
      else if constexpr(N::value <= 8)
      {
        return _mm_packus_epi16(v0, v0);
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
      else if constexpr(N::value <= 8)
      {
        return _mm256_packs_epi32(v0, v0);
      }
    }
    else if constexpr( std::is_same_v<In,int16_t> && std::is_same_v<Out,uint8_t> && (N::value <= 32))
    {
      if constexpr(N::value == 32)
      {
        auto [ low, high ] = v0.slice();
        return _mm256_packus_epi16(low, high);
      }
      else if constexpr(N::value <= 16)
      {
        return _mm256_packus_epi16(v0, v0);
      }
    }
    else if constexpr( std::is_same_v<In,int32_t> && std::is_same_v<Out,uint16_t> && (N::value <= 16))
    {
      if constexpr(N::value == 16)
      {
        auto [ low, high ] = v0.slice();
        return _mm256_packus_epi32(low, high);
      }
      else if constexpr(N::value <= 8)
      {
        return _mm256_packus_epi16(v0, v0);
      }
    }
    else
    {
      return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt);
    }
  }  
}

#endif
