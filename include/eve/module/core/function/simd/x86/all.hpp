//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_ALL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_ALL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/forward.hpp>
#include <eve/wide.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE bool  all_(EVE_SUPPORTS(sse2_)
                            , logical<wide<T, N, sse_>> const &v) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>)
      {
        using i8_t = wide<int8_t, fixed<16> , sse_>;
        using t_t  = wide<T, N, sse_>; 
        static constexpr int mask = 0xF >> (4-N::value); 
        if constexpr(N::value*sizeof(T) != 16) // "small" wide types
        {
          static constexpr int sv = N::value*sizeof(T); 
          auto z = _mm_bslli_si128(bitwise_cast<i8_t>(v.mask()), sv); 
          i8_t z1= _mm_bsrli_si128(z, sv);
          return _mm_movemask_ps(bitwise_cast<t_t>(z1)) == mask;
        }
        else  return _mm_movemask_ps(v.mask()) == mask;
      }
      if constexpr(std::is_same_v<T, double>)
      {
        using i8_t = wide<int8_t, fixed<16> , sse_>;
        using t_t  = wide<T, N, sse_>; 
        static constexpr int mask = 0x3 >> (2-N::value);
        if constexpr(N::value*sizeof(T) != 16) // "small" wide types
        {
          static constexpr int sv = N::value*sizeof(T); 
          auto z = _mm_bslli_si128(bitwise_cast<i8_t>(v.mask()), sv); 
          i8_t z1= _mm_bsrli_si128(z, sv);
          return _mm_movemask_pd(bitwise_cast<t_t>(z1)) == mask;
        }
        else return _mm_movemask_pd(v.mask()) == mask;
      }
    }  
    else
    {
      static constexpr int mask = 0xFFFF >> (16-sizeof(T)*N::value); 
      if constexpr(sizeof(T) == 1)
      {
        static constexpr int sv = N::value; 
        if constexpr(N::value*sizeof(T) != 16) // "small" wide types
        {
          auto z = _mm_bslli_si128(v.mask(), sv); 
          auto z1= _mm_bsrli_si128(z, sv);
          return _mm_movemask_epi8(z1) == mask;
        }
        else return _mm_movemask_epi8(v.mask()) == mask;
      }
      else
      {
       using i8_t = wide<int8_t, fixed<16> , sse_>;
       static constexpr int sv = N::value*sizeof(T); 
       if constexpr(N::value*sizeof(T) != 16) // "small" wide types
        {         
          auto z = _mm_bslli_si128(bitwise_cast<i8_t >(v.mask()), sv); 
          auto z1= _mm_bsrli_si128(z, sv);
          return _mm_movemask_epi8(z1) == mask;
        }
        else return _mm_movemask_epi8(bitwise_cast<i8_t >(v.mask())) == mask;
      }
    }
  }
  
  
  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(avx_)
                           , logical<wide<T, N, avx_>> const &v) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>)
      {
        return _mm256_movemask_ps(v.mask()) == int(0xFF);
      }
      if constexpr(std::is_same_v<T, double>)
      {
        return _mm256_movemask_pd(v.mask()) ==int( 0xF);
      } 
      
    }  
    else
    {
      if constexpr(current_api >= avx2)
      {
        if constexpr(sizeof(T) == 1)
        {
          return _mm256_movemask_epi8(v.mask()) == int(0xFFFFFFFF);
        }
        else
        {
          using i8_t = wide<int8_t, fixed<32> , avx_>; 
          return _mm256_movemask_epi8(bitwise_cast<i8_t >(v.mask())) == int(0xFFFFFFFF);
        }
      }     
      else
      {
        auto [ sl, sh] = v.slice(); 
        return all(sl) && all(sh);
      }
      
    }
  }
}

#endif
